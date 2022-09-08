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

void Network::setCustomPort(unsigned short port) { _port = port; }

void Network::setDefaultPort() { _port = syndesi_port; }

unsigned short Network::port() { return _port; }

/*
 * From upper layer
 */
void Network::request(Frame& frame) {
    Frame::NetworkHeader networkHeader;
    networkHeader.fields.routing = frame.getID().reroutes() > 0 ? true : false;
    networkHeader.fields.request_nReply = true;
    networkHeader.fields.reserved = 0;

    // Determine which controller to use based on address
    switch (frame._id->getAddressType()) {
#ifdef USE_IP_CONTROLLER
        case SyndesiID::address_type_t::IPV4:
        case SyndesiID::address_type_t::IPV6:
            frame.getID().setIPPort(_port);
            IPController->write(frame.getID(), frame._buffer->data(),
                                frame._buffer->length());

            // The controllerDataAvailable method will take care of the confirm

            readFrame(IPController);
            break;
#endif  // USE_IP_CONTROLLER
    }
    // Add the ID to the pendingConfirmList
    // pendingConfirm.push_front(frame.getID());
}

void Network::response(Frame& frame) {
    // IPController->response(&frame.getID(), frame._buffer);
}

/*
 * Lower layer
 */
void Network::readFrame(SAP::IController* controller) {
    // Start by reading the first few bytes of the frame to know the length,
    // then read the rest of it. If multiple frames are present in the buffer,
    // they will be treated separately
    controller->read()


}

void Network::controllerDataAvailable(SAP::IController* controller) {
    readFrame(controller);

}

void Network::init() {
    if (IPController != nullptr) IPController->init();
}

}  // namespace syndesi
