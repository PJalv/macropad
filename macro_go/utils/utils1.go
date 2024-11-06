package utils

import (
	"fmt"
	"go.bug.st/serial"
	"log"
	"strings"
)

// ConnectToDevice is an exported function that can be used by other packages.
func ConnectToDevice(baudRate int) (serial.Port, error) {
	var targetPort string
	log.Println("Baudrate", baudRate)
	mode := &serial.Mode{
		BaudRate: baudRate,
	}

	ports, err := serial.GetPortsList()
	if err != nil {
		return nil, err
	}

	for _, port := range ports {
		fmt.Printf("Found port: %v\n", port)
		if strings.Contains(port, "/dev/ttyACM") {
			targetPort = port
			break
		}
	}

	port, err := serial.Open(targetPort, mode)
	if err != nil {
		log.Println(err)
		return nil, err
	}
	return port, nil
}
