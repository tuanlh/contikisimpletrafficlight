# This is an example simple traffic light based on blink led and rime broadcast on Contiki-OS
# Requirement
- ContikiOS 2.6 Instant
- 2 Telosb (mote Sky)
# How to use
## Simulation with Cooja
Import file `simpletrafficlight.csc` into Cooja
## Upload to Telosb
### Step 1. Plug in Telosb into Computer through USB port
### Step 2. Chmod device
```
$ sudo chmod 666 /dev/ttyUSB0
```
**ttyUSB0** can replace with **ttyUSB1**, **ttyUSB2**,...

Tips: to view list mote, you can type:
```make motelist```

### Step 3. Create a folder simpletrafficlight in ~/contiki/examples and put all code within
### Step 4. On Telosb 1 (master) upload master.c
```
$ make TARGET=sky master.upload
```
### Step 5. On Telosb 2 (slave) upload slave.c
```
$ make TARGET=sky slave.upload
```
# Author: Le Hoang Tuan