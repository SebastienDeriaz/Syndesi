/**
 * @file network.cpp
 *
 * @brief Interfacing with the communication protocols (IP, UART, RS 485, ...)
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#include "network.hpp"
#include "general_config.hpp"

namespace syndesi {
/*
 * From upper layer
 */
void Network::request(Frame& frame) {
    Frame::NetworkHeader networkHeader;
    networkHeader.fields.routing =
        frame._id.get()->reroutes() > 0 ? true : false;
    networkHeader.fields.request_nReply = true;
    networkHeader.fields.reserved = 0;

    // Determine which controller to use based on address
    switch (frame._id->getAddressType()) {
        case SyndesiID::address_type_t::IPV4:
        case SyndesiID::address_type_t::IPV6:
            _ipController->request_or_response(frame._buffer, *frame.getID());

            break;
    }
    // Add the ID to the pendingConfirmList
    // pendingConfirm.push_front(frame.getID());
}

void Network::response(Frame& frame) {}

/*
 * Lower layer
 */
void Network::IP_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                       unique_ptr<SyndesiID>& masterID) {
    
    Frame frame(buffer, masterID);
#if defined(HOST_MODE)
    _frameManager->indication(frame);
#elif defined(DEVICE_MODE)
    _frameManager->confirm(frame);
#else
#endif
}

void Network::UART_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                         unique_ptr<SyndesiID>& masterID) {}

void Network::RS485_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                          unique_ptr<SyndesiID>& masterID) {}

}  // namespace syndesi
