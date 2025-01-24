BOARD = arduino:avr:micro
PORT = /dev/ttyACM0
SKETCH = macro_pad.ino

.PHONY: all build upload clean

all: build upload

build:
	arduino-cli compile --fqbn $(BOARD) .

upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) .

clean:
	rm -f *.hex *.bin
