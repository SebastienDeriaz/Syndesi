/**
 * @file rs485controller.hpp
 *
 * @brief RS485 controller
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef RS485_CONTROLLER_H
#define RS485_CONTROLLER_H

#include "interfaces.hpp"

namespace syndesi {

class RS485Controller : public SAP::IController_top{
    friend class Core;

   private:
    SAP::INetwork_bottom* _network;
    void registerNetwork(SAP::INetwork_bottom* network) { _network = network; };

    void request_or_response(unique_ptr<Buffer>& buffer, SyndesiID& masterID);

    public:
    RS485Controller() {};
    ~RS485Controller() {};
};

}  // namespace syndesi

#endif  // RS485_CONTROLLER_H