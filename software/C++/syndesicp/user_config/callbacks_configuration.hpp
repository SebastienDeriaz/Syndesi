/* Please edit this file to configure which callbacks must be used
*  
* Disabled callback :
* //#define USE_REGISTER_READ_16_REQUEST_CALLBACK
* Enabled callback
* #define USE_REGISTER_READ_16_REQUEST_CALLBACK
*
* The user must then implement it (following the prototype in callbacks.hpp)
*
* Each request callback follows the format :
*   command_request_callback(request, reply);
* The reply, passed as a pointer, must be editer by the user in the callback
*
* Each reply callback follows the format :
*   command_reply_callback(reply);
* No response to the device will be made
*
* This file has been generated automatically by the script generate_commands.py
* date : 22-08-14 08:09:50
*/


/*
* Request callbacks (to be used in device code)
*/
//#define USE_ERROR_REPLY_CALLBACK
//#define USE_DEVICE_DISCOVER_REQUEST_CALLBACK
//#define USE_DEVICE_DISCOVER_REPLY_CALLBACK
//#define USE_REGISTER_READ_16_REQUEST_CALLBACK
//#define USE_REGISTER_READ_16_REPLY_CALLBACK
//#define USE_REGISTER_WRITE_16_REQUEST_CALLBACK
//#define USE_REGISTER_WRITE_16_REPLY_CALLBACK
//#define USE_SPI_READ_WRITE_REQUEST_CALLBACK
//#define USE_SPI_READ_WRITE_REPLY_CALLBACK
//#define USE_SPI_WRITE_ONLY_REQUEST_CALLBACK
//#define USE_SPI_WRITE_ONLY_REPLY_CALLBACK
//#define USE_I2C_READ_REQUEST_CALLBACK
//#define USE_I2C_READ_REPLY_CALLBACK
//#define USE_I2C_WRITE_REQUEST_CALLBACK
//#define USE_I2C_WRITE_REPLY_CALLBACK



/*
* Reply callbacks (to be used in host code)
*/
//#define USE_ERROR_REPLY_CALLBACK
//#define USE_DEVICE_DISCOVER_REQUEST_CALLBACK
//#define USE_DEVICE_DISCOVER_REPLY_CALLBACK
//#define USE_REGISTER_READ_16_REQUEST_CALLBACK
//#define USE_REGISTER_READ_16_REPLY_CALLBACK
//#define USE_REGISTER_WRITE_16_REQUEST_CALLBACK
//#define USE_REGISTER_WRITE_16_REPLY_CALLBACK
//#define USE_SPI_READ_WRITE_REQUEST_CALLBACK
//#define USE_SPI_READ_WRITE_REPLY_CALLBACK
//#define USE_SPI_WRITE_ONLY_REQUEST_CALLBACK
//#define USE_SPI_WRITE_ONLY_REPLY_CALLBACK
//#define USE_I2C_READ_REQUEST_CALLBACK
//#define USE_I2C_READ_REPLY_CALLBACK
//#define USE_I2C_WRITE_REQUEST_CALLBACK
//#define USE_I2C_WRITE_REPLY_CALLBACK

