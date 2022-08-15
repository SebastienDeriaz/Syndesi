/**
 * @file networkinterface.hpp
 *
 * @brief Interfacing with the communication protocols (IP, UART, RS 485, ...)
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <stdint.h>

#include "framemanager.hpp"

namespace syndesi {
class NetworkInterface {
    /**
     * @brief Network frame instance
     * @note contains a network header and a payload. The payload is forwarded
     * to the FrameManager
     */

    friend class Core;

    class Packet {
       public:
        /**
         * @brief Construct a new Network Frame object from a buffer
         *
         * @param buffer
         */
        NetworkFrame(Buffer& buffer);

       private:
        union NetworkHeader {
            struct {
                unsigned char
                    routing : 1;  // Frame must be re-routed to another device,
                                  // this means it contains a sdid after the
                                  // network header
                unsigned char request_nReply : 1;  // Request (1) or reply (0)
                unsigned char reserved : 7;
            } fields;
            uint8_t value;
        }
// Check if the NetworkHeader struct has been declared correctly
// This way the sizeof(NetworkHeader) can be used safely
#if sizeof(NetworkHeader) != 2
#error NetworkHeader is ill-defined
#endif

    }

    /*
     * Protocols
     */
    // IP
    /**
     * @brief IP frame received
     *
     */
    void
    IP_onReceive();

    /**
     * @brief send IP frame
     * @note must be implemented by the IP
     */
    void IP_send();

    // UART
    /**
     * @brief UART frame received
     *
     */
    void UART_onReceive();

    /**
     * @brief send UART frame
     * @note must be implemented by the UART
     */
    void UART_send();

    // RS-485
    /**
     * @brief RS-485 frame received
     *
     */
    void RS485_onReceive();

    /**
     * @brief send RS-485 frame
     * @note must be implemented by the RS-485
     */
};

}  // namespace syndesi

#endif  // NETWORK_INTERFACE_H