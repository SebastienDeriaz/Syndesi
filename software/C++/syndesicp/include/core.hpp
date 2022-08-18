/**
 * @file core.hpp
 *
 * @brief Syndesi core
 *
 * @author Sébastien Deriaz
 * @date 09.08.2022
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>

#include "frame.hpp"
#include "syndesi_types.hpp"
#include "callbacks.hpp"
#include "framemanager.hpp"
#include "network.hpp"
#include "ipcontroller.hpp"
#include "uartcontroller.hpp"
#include "rs485controller.hpp"

namespace syndesi {

class Core {
   private:

    void factory_init();

    /*
    * Layers
    */
   Callbacks callbacks;
   FrameManager frameManager;
   Network network;
   public:
#ifdef USE_IP_CONTROLLER
    IPController ipController;
#endif
#ifdef USE_UART_CONTROLLER
    UARTController uartController;        
#endif
#ifdef USE_RS485_CONTROLLER
    RS485Controller rs485Controller;
#endif

    //TODO : Find a good place for this
    void sendRequest(Payload& payload, SyndesiID& id);
    void sendRequest(Payload& payload, unique_ptr<SyndesiID>& id);

    Core() {factory_init();};
    ~Core(){};
};

}  // namespace syndesi

#endif  // CORE_H