DEFAULT_PORT = /dev/ttyUSB0
FULLY_QUALIFIED_BOARD_NAME = arduino:avr:uno
FQBN = $(FULLY_QUALIFIED_BOARD_NAME)
PORT=$(DEFAULT_PORT)

.PHONY: all clean very-clean install compile upload

all: upload

clean: uninstall

very-clean: clean
	rm ~/.local/bin/arduino-cli

init:
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/.local/bin sh
	arduino-cli config init

lib:
	arduino-cli lib install RTClib@2.1.4
	arduino-cli lib install SD@1.3.0

core:
	arduino-cli core install arduino:avr

install: core lib

uninstall:
	arduino-cli core uninstall arduino:avr
	arduino-cli lib uninstall RTClib
	arduino-cli lib uninstall SD

compile: install
	arduino-cli compile --fqbn $(FQBN) .

upload: compile
	arduino-cli upload --port $(PORT) --fqbn $(FQBN)
