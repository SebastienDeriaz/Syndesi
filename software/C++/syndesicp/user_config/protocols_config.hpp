/**
 * @file protocols.hpp
 *
 * @brief Protocols settings
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */


#include "settings.hpp"

/*
* Configure what controllers are used (uncomment to enable)
*/

// IP Controller
#define USE_IP_CONTROLLER
// Controller MODE
// CONTROLLER_MODE_POLL : Poll for received data
// CONTROLLER_MODE_WAIT : Wait for received data
// CONTROLLER_MODE_IRQ : Interrupt call when data is received
#define IP_CONTROLLER_MODE CONTROLLER_MODE_POLL


// UART Controller
#define USE_UART_CONTROLLER
// Controller MODE
// CONTROLLER_MODE_POLL : Poll for received data
// CONTROLLER_MODE_WAIT : Wait for received data
// CONTROLLER_MODE_IRQ : Interrupt call when data is received
//#define UART_CONTROLLER_MODE

// RS485 Controller
#define USE_RS485_CONTROLLER
// Controller MODE
// CONTROLLER_MODE_POLL : Poll for received data
// CONTROLLER_MODE_WAIT : Wait for received data
// CONTROLLER_MODE_IRQ : Interrupt call when data is received
//#define RS485_CONTROLLER_MODE