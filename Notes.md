# Notes

## Communication protocol to use

- Raw data over TCP/IP
  - Allows for more complex commands
  - Multiple commands in one frame
- Ethercat
  - Costly (cheapest IC starts at ~ 10 USD)
  - Need Npcap to run on Windows (at least)
- Modbus TCP
  - Simple
  - Register by register
  - Possibility to describe the function with a json file


### Chosen option (05.06.2022)

Raw data over TCP/IP Because the "make this at time T" option requires more arguments than what Modbus TCP can offer



## Frames specifications

- Simple commands
  - SPI Write
  - SPI Read
  - Register write / read
- Timed commands
  - Make a command at a specified time
- Interrupt ?
  - The device sends a packet to the host directly (requires a server on the host)
  - Could also be an answer-based system. The host requests the device to send an answer when an event occurs or when the event timeouts


The last 4 bits are configuration for each command (to select between multiple SPIs for example)
### Required frames

- SPI read / write with SPI index (0-7). 8 SPI interfaces possible.
- Register read / write with index (0-15) for I/O. 16xN bits with N the number of bits for the registers. 8, 16 or 32 bits specific to each device
- Discover frame (UDP Broadcast)
- I2C read / write with I2C index (0-7). 8 I2C interfaces possible.
- UART read / write with I2C index (0-7). 8 UART interfaces possible.