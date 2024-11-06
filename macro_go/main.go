package main

import (
	"flag"
	"fmt"
	"log"
	"macro_go/utils"
	"os/exec"
	"regexp"
	"strings"
	"time"

	"go.bug.st/serial"
)

func main() {

	brPtr := flag.Int("baudrate", 9600, "Baudrate")
	// portPtr := flag.String("port", "", "Serial Port")
	flag.Parse()
	var port serial.Port
	port, err := utils.ConnectToDevice(*brPtr)
	if err != nil {
		log.Fatal(err)
	}

	_, err = port.Write([]byte("10,20,30\n\r"))
	if err != nil {
		log.Fatal(err)
	}

	buff := make([]byte, 200)
	totalCommand := []string{"", ""}
	for {
		n, err := port.Read(buff)
		if err != nil {
			for {
				log.Println(err)
				log.Println("Attempting Reconnection")
				time.Sleep(1 * time.Second)

				port, err = utils.ConnectToDevice(*brPtr)
				if err == nil {
					break
				} else {
					log.Println(err)
				}
			}
		}
		if n == 0 {
			fmt.Println("\nEOF")
		}

		message := string(buff[:n])
		log.Println(message)

		patterns := []string{`\[Volume\]: (\d+)`, `\[Increase\]: (\d+)`, `\[Decrease\]: (\d+)`, `\[Toggle\]: (\d+)`, `\[exec\]:\s*#(.+)$`, `(.+?)@`}
		for _, pat := range patterns {
			regex := regexp.MustCompile(pat)
			matches := regex.FindStringSubmatch(message)
			if len(matches) < 2 {
				continue
			} else {
				filter := matches[1]
				// log.Println("Filter is:", filter)
				var app string
				switch filter {
				case "1":
					app = ".spotify-wrapped"
				case "2":
					app = "chromium"
				}

				switch pat {
				case patterns[0]:
					go exec.Command("pactl", "--", "set-sink-volume", "0", filter+"%").Run()
				case patterns[1]:
					if app != "" {
						cmd := exec.Command("bash", "-c", `pactl list sink-inputs | grep -A 27 "application.process.binary = \"`+app+`\"" | grep serial | grep -oE '[0-9]+' | while read -r serial; do pactl set-sink-input-volume "$serial" +1.5%; done`)
						cmd.Run()
					}
					break
				case patterns[2]:
					cmd := exec.Command("bash", "-c", `pactl list sink-inputs | grep -A 27 "application.process.binary = \"`+app+`\"" | grep serial | grep -oE '[0-9]+' | while read -r serial; do pactl set-sink-input-volume "$serial" -1.5%; done`)
					cmd.Run()
					break
				case patterns[3]:
					cmd := exec.Command("bash", "-c", `pactl list sink-inputs | grep -A 27 "application.process.binary = \"`+app+`\"" | grep serial | grep -oE '"[0-9]+"' | while read -r serial; do pactl set-sink-input-mute "$(echo "$serial" | tr -d '"')" toggle; done`)
					cmd.Run()
					break
				case patterns[4]:
					if filter[len(filter)-1] == '@' {
						//add logic to remove the last character from the varioable filter
						filter = filter[:len(filter)-1]
						cmd := exec.Command("bash", "-c", filter)
						err := cmd.Run()
						if err != nil {
							log.Println(err)
						}
					} else {
						totalCommand[0] = filter
						log.Println(totalCommand)
					}
					break
				case patterns[5]:
					regex := regexp.MustCompile(`\[exec\]:\s*#(.+)$`)
					matches := regex.FindStringSubmatch(filter)
					if matches != nil {
						cmd := exec.Command("bash", "-c", matches[1])
						err := cmd.Run()
						if err != nil {
							log.Println(err)
						}
						break
					}
					totalCommand[1] = filter
					log.Println(strings.Join(totalCommand, ""))
					cmd := exec.Command("bash", "-c", strings.Join(totalCommand, ""))
					err := cmd.Run()
					if err != nil {
						log.Println(err)
					}
					break
				}
			}
		}
	}
}
