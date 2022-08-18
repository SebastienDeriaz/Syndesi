# Syndesi Project

The goal of the Syndesi project is to provide a system capable of easily interfacing test and measurement devices with a host controller.

## Objective

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
- Datalogging

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

- Device driver to manage the low-level communication with the module
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

## Project structure
```
syndesi
│   README.md                        this file
│   TODO.md                          todo list
│
├───doc                              documentation
│   ├───communication                frame format
│   └───software                     communication protocol structure
│       
└───software
    ├───C++                          C++ code
    │ ­   ├───syndesicp               Syndesi communication protocol C++
    │    └───syndesi                 Syndesi host C++
    │
    ├───Python                       Python code
    │ ­   ├───syndesicp               Syndesi communication protocol Python
    │    └───syndesi                 Syndesi host Python
    │    
    └───Scripts                      Various scripts and declarations
```
