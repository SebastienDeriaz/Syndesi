/**
 * @file network.hpp
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
#include "interfaces.hpp"
#include "frame.hpp"
#include "sdid.hpp"
#include <list>

namespace syndesi {
class Network : SAP::INetwork_bottom, SAP::INetwork_top{
    /**
     * @brief Network frame instance
     * @note contains a network header and a payload. The payload is forwarded
     * to the FrameManager
     */
    friend class Core;

    private:

        // List of pendingConfirm IDs
        std::list<unique_ptr<SyndesiID>> pendingConfirm;

        /**
         * @brief Look in the pendingConfirm list and determine wether or not the received ID is for a confirm 
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool inPendingConfirm(SyndesiID& id);


    /*
    * Upper layer
    */
    SAP::IFrameManager_bottom* _frameManager;
    void registerFrameManager(SAP::IFrameManager_bottom* frameManager) {_frameManager = frameManager;};
    // <-frameManager
    void request(Frame& frame);
    // <-frameManager
    void response(Frame& frame);


    /*
    * Lower layer
    */
    SAP::IController_top* _ipController;
    void registerIPController(SAP::IController_top* controller) {_ipController = controller;};
    // from protocol
    void IP_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID);

    SAP::IController_top* _uartController;
    void registerUARTController(SAP::IController_top* controller) {_uartController = controller;};
    // from protocol
    void UART_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID);

    SAP::IController_top* _rs485Controller;
    void registerRS485Controller(SAP::IController_top* controller) {_rs485Controller = controller;};
    // from protocol
    void RS485_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID);
};

}  // namespace syndesi

#endif  // NETWORK_INTERFACE_H