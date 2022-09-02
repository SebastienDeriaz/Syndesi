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

void Network::setCustomPort(unsigned short port) {
    _port = port;
}

void Network::setDefaultPort() {
    _port = syndesi_port;
}

unsigned short Network::port() {
    return _port;
}

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
#ifdef USE_IP_CONTROLLER
        case SyndesiID::address_type_t::IPV4:
        case SyndesiID::address_type_t::IPV6:
            frame.getID()->setIPPort(_port);
            IPHost->request(frame.getID(), frame._buffer);
            break;
#endif // USE_IP_CONTROLLER
    }
    // Add the ID to the pendingConfirmList
    // pendingConfirm.push_front(frame.getID());
}

void Network::response(Frame& frame) {
    IPDevice->response(frame.getID(), frame._buffer);
}
/*
 * Lower layer
 */
void Network::indication(unique_ptr<SyndesiID>& id, unique_ptr<Buffer>& buffer) {
                                        
    Frame frame(buffer, id);
    _frameManager->indication(frame);    
}

void Network::confirm(unique_ptr<SyndesiID>& id, unique_ptr<Buffer>& buffer) {
    Frame frame(buffer, id);
    _frameManager->confirm(frame);
}

void Network::init() {
    if(IPDevice != nullptr) IPDevice->init();
    if(IPHost != nullptr) IPHost->init();
}

}  // namespace syndesi
