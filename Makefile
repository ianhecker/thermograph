CONFIG_FILE = ./arduino-cli.yaml
DEFAULT_PORT = /dev/ttyUSB0
FULLY_QUALIFIED_BOARD_NAME = arduino:avr:uno
FQBN = $(FULLY_QUALIFIED_BOARD_NAME)
PORT=$(DEFAULT_PORT)

.PHONY: all clean very-clean install compile upload

all: upload

clean:
	rm -r data
	rm -r downloads
	rm -r libraries

very-clean: clean
	rm ~/.local/bin/arduino-cli

init:
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/.local/bin sh

install:
	arduino-cli --config-file $(CONFIG_FILE) lib install RTClib@2.1.4
	arduino-cli --config-file $(CONFIG_FILE) lib install SD@1.3.0

compile: install
	arduino-cli --config-file $(CONFIG_FILE) compile --fqbn $(FQBN)

upload: compile
	arduino-cli --config-file $(CONFIG_FILE) upload --port $(PORT) --fqbn $(FQBN)
