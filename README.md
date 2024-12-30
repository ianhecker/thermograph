# Thermograph

A temperature logger for Arduino

## Makefile

You will need to install the `arduino-cli`, run

```bash
make init
```

> This will install the `arduino-cli` binary into `~/.local/bin`, although you
can place the binary anywhere you choose, so long as it is within your `PATH`
variable

### Run

Install libraries, compile, & upload

```bash
make clean
```

### Installing Libraries

Install libraries

```bash
make install
```

Remove libraries

```bash
make clean
```

### Compiling & Uploading

Compile sketch

```bash
make compile
```

Upload sketch

```bash
make upload
```

## Arduino CLI

Install this to run the make

### Install

Download latest version

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

> Move binary to a folder within your PATH, if the installer does not

Initialize a `arduino-cli.yaml` config (if you have not already)

```bash
arduino-cli config init
```

Install R3 Uno Core

```bash
arduino-cli core update-index
arduino-cli core install arduino:avr
```

Verify Installation

```bash
arduino-cli core list
```

## Compile & Upload

Plug your board into the computer


Check the ports for connected board

```bash
arduino-cli board list
```

> Port for linux & mac should look like /dev/ttyACM0

Specify your board and the port

```bash
arduino-cli board attach --board arduino:avr:uno --port <YOUR_PORT_HERE>
```

Compile sketch

> You'll need to be in the root directory of the thermograph repo

```bash
arduino-cli compile --fqbn arduino:avr:uno
```

Upload the sketch

```bash
arduino-cli upload --port <YOUR_PORT_HERE> --fqbn arduino:avr:uno
```
