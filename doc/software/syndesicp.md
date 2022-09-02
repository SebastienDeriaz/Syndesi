# Syndesicp library


## Controllers interface

Each controller is implemented by the user (or by a driver in the future).

To use a controller, the user needs to implement and then register all of the callbacks necessary for the operation
Some methods can be called by the user directly and are implemented in the Network layer

Each controller has operation modes that configure how it's going to gather the data (wait, callback, IRQ, etc...) 

### List of all controller methods

Common callbacks (device or host)

- ``void* init();``
- ``bool send_data(SyndesiID& dest, );`` 

Device callbacks

- ``bool wait_for_connection(); (HOST_CONNECTION_MODE : WAIT)``
- ``bool wait_for_read(); (READ_MODE : WAIT)``


Host callbacks

- ``bool connect(SyndesiID& dest);``

Common methods (device or host)

- ``void received_data();``

Device methods

- 

Host methods

- 
