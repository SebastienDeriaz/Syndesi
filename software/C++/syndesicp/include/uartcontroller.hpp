/**
 * @file uartcontroller.hpp
 *
 * @brief UART controller
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef UART_CONTROLLER_H
#define UART_CONTROLLER_H

#include "interfaces.hpp"

namespace syndesi {

class UARTController : public SAP::IController_top {
    friend class Core;

   private:
    SAP::INetwork_bottom* _network;
    void registerNetwork(SAP::INetwork_bottom* network) { _network = network; };

    void request_or_response(unique_ptr<Buffer>& buffer, SyndesiID& masterID);

   public:
    UARTController() {};
    ~UARTController() {};
};

}  // namespace syndesi

#endif  // UART_CONTROLLER_H