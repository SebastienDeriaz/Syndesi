/**
 * @file interfaces.hpp
 *
 * @brief Interfaces between layers.
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include "buffer.hpp"
#include "frame.hpp"
#include "protocols_config.hpp"

namespace syndesi {
namespace SAP {

class ICallbacks_bottom {
   public:
    // From bottom layer
    virtual void indication(Frame& payload) = 0;
    virtual void confirm(Frame& payload) = 0;
};

class IFrameManager_top {
   public:
    // From top layer
    virtual void response(Frame& payload) = 0;
};

class IFrameManager_bottom {
   public:
    // From bottom layer
    virtual void indication(Frame& frame) = 0;
    virtual void confirm(Frame& frame) = 0;
};

class INetwork_top {
   public:
    // From top layer
    virtual void request(Frame& frame) = 0;
    virtual void response(Frame& frame) = 0;
};

class INetwork_bottom {
   public:
#ifdef USE_IP_CONTROLLER
    // From bottom layer (IP)
    virtual void IP_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID) = 0;
#endif

#ifdef USE_UART_CONTROLLER
    // From bottom layer (UART)
    virtual void UART_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID) = 0;
#endif

#ifdef USE_RS485_CONTROLLER
    // From bottom layer (RS485)
    virtual void RS485_indication_or_confirm(unique_ptr<Buffer>& buffer, unique_ptr<SyndesiID>& masterID) = 0;
#endif
};

class IController_top {
   public:
    // From top layer
    virtual void request_or_response(unique_ptr<Buffer>& buffer, SyndesiID& masterID) = 0;
    // From bottom layer
};

/*class IController_bottom {
    public:
    virtual void indication(Buffer& buffer) = 0;
    virtual void confirm(Buffer& buffer) = 0;
}*/

}  // namespace SAP
}  // namespace syndesi

#endif  // INTERFACES_H
