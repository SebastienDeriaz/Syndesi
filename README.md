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

Each "module" would be referenced through either it's IP address (if it has a static one) or a unique code
A broadcast packet would be used to discover modules and ask "can i get module with code AABBCCDD ?"

```python
from syndesi import device

my_device = device('AABBCCDD')

my_device.digitalWrite(3, 'HIGH') # Or 1 instead of 'HIGH'

my_device.digitalRead(4)

# etc...
```

### Usages

- School labs
- Prototyping
- Automation (?)

### Modules

The "modules" could be anything basically

- "Arduino" like board
- I2C / SPI / UART board
- Measurement card
  - This would be a "low-end" measurement card but still useful
- Logic analyser card
- RF module (produce I and Q modulation)
- DAC / ADC
- State space regulation card

They all have a unique ID that provides :

- Their function
- Their unique identifier code

A Driver can be associated by knowing this code


## Ethernet

Each module has an ip address with either :

- DHCP
- zeroconf (ip address when there's no network)
- static

An led could be used to tell the user how the module is configured (and a button to reset it)
