# Syndesi communication protocol

The communication protocol, written in C++, allows the device to manage incomming Syndesi frames and their corresponding actions

- Syndesi communication protocol must be a single library, included with ``#include <syndesicp>``
- A method is called whenever a new packet is received (via Ethernet interface)
- A method is also called whenever an interrupt arises on the interface side (configured via Syndesi)
- Syndesi provides a "command received" method that is called in the main loop. Whenever a new valid command is received, this function provides an object reference with the command ID and data
- The user is free to implement the behavior of each command
- A Syndesi Core is instanciated to manage everything
