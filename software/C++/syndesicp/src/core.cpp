/**
 * @file syndesi.cpp
 *
 * @brief Syndesi device library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 09.06.2022
 */

#include "core.hpp"

namespace syndesi {

void Core::factory_init() {
    // register interfaces (connect layers together)
    // Callbacks class
    callbacks.registerFrameManager(&frameManager);
    // FrameManager class
    frameManager.registerCallbacks(&callbacks);
    frameManager.registerNetwork(&network);
    // Network class
    network.registerFrameManager(&frameManager);
    // IP Controller class (if used)
#ifdef USE_IP_CONTROLLER
    network.registerIPController(&ipController);
    ipController.registerNetwork(&network);
#endif
#ifdef USE_UART_CONTROLLER
    network.registerUARTController(&uartController);
    uartController.registerNetwork(&network);
#endif
#ifdef USE_RS485_CONTROLLER
    network.registerRS485Controller(&rs485Controller);
    rs485Controller.registerNetwork(&network);
#endif    
}


void Core::sendRequest(Payload& payload, SyndesiID& id) {
    // This version is easier but requires a copy of the SyndesiID argument
    
    unique_ptr<SyndesiID> uid = make_unique<SyndesiID>(id);
    Frame frame(payload, uid);
    frameManager.request(frame);
}

void Core::sendRequest(Payload& payload, unique_ptr<SyndesiID>& id) {
    // This version is easier but requires a copy of the SyndesiID argument
    Frame frame(payload, id);
    frameManager.request(frame);
}
}  // namespace syndesi