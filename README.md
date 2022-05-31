# Syndesi
Universal interfacing project


This is a WIP project, as of today it is only an idea. If you've got any ideas and/or want to contribute, don't hesitate to contact me via email at sebastien.deriaz1@gmail.com


## The idea

The goal is to create software/hardware project that allows people to interface software **easily** with hardware. Basically the Arduino of interfacing.

For example, you want to control 3.3V or 5V pins from your software (or control relays, mosfet, whatever). This could be fairly easily implemented with

- An Ethernet connected board
  - Ethernet, not USB, because Ethernet is universal, the hardware is common and there's no "oh the COM port changed" stuff + it's cross-platform
- A Python script
  - Because python is, in my opinion, well suited to this usage

### Example of Python code

Each interface would be referenced through either its IP address (if it has a static one) or a unique code
A broadcast packet would be used to discover interfaces and ask "can i get interface with code AABBCCDD ?"

```python
from syndesi import interface

my_interface = interface('AABBCCDD')

my_interface.digitalWrite(3, 'HIGH') # Or 1 instead of 'HIGH'

my_interface.digitalRead(4)

# etc...
```

### Usages

- School labs
- Prototyping
- Automation (?)

### Interfaces

The Interfaces could be anything basically

- "Arduino" like board
- I2C / SPI / UART board
- Measurement card
  - This would be a "low-end" measurement card but still useful
- Logic analyser card
- RF module (produce I and Q modulation)
- DAC / ADC
- State space regulation card
- GPIB interface board (to replace the costly USB-GPIB interfaces)
- Logic test card (X output, Y inputs) for a DUT, basically a hardware testbench

They all have a unique ID that provides :

- Their function
- Their unique identifier code

A Driver can be associated by knowing this code

## drivers

There are two types of drivers :

- Device driver in C++ to manage how to communication with each device
  - static variables can be used to have greater control over the device's behavior
  - ctypes seems to be the perfect fit
- High-level (HL) driver to manage what's connected to the device in Python or another high-level language (depends on which language is used)

A High-level driver is stacked over a device driver to provide more functionnalities. For example a driver for a SPI sensor (after an SPI device)

Example of using a high-level driver in python:

```python
from syndesi import device

my_device = device('AABBCCDD')
# using device(ID) calls interface(ID) in the background
```

## Ethernet

Each interface has an ip address with either :

- DHCP
- zeroconf (ip address when there's no network)
- static

An led could be used to tell the user how the interface is configured (and a button to reset it)

Possiblity to use W5500 chip that provides 10/100 Mbps Ethernet and SPI communication

## Devices naming convention

| SDI       | - | A           | - | 1AB     | - | xxx      | - | 000     |
|-----------|---|-------------|---|---------|---|----------|---|---------|
| Base name |   | Form factor |   | Options |   | modifier |   | Version |

### Form factor

- A : Arduino-like
- B : Compact ?
- C : ... ?
- D : Din rail boxes ?
- ...
- Z :

### Options

0000'0000'0000'0000'0000'0000

- 0 : SPI
- 1 : I2C
- 2 : UART / USART
- 3 : Digital in
- 4 : Digital out
- 5 : Analog in
- 6 : Analog out
- 7 : One wire
- 8 : CanBus
- 9 :
- 10 :
- 11 :
- 12 :
- 13 :
- 14 :
- 15 :
- 16 :
- 17 :
- 18 :
- 19 :
- 20 :
- 21 :
- 22 :
- 23 : synchronisation