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
            cout << "IPController" << endl;
            frame.getID()->setIPPort(_port);
            _ipController->request_or_response(frame._buffer, *frame.getID());
            break;
#endif // USE_IP_CONTROLLER
    }
    // Add the ID to the pendingConfirmList
    // pendingConfirm.push_front(frame.getID());
}

void Network::response(Frame& frame) {
    _ipController->request_or_response(frame._buffer, *frame.getID());
}
/*
 * Lower layer
 */
#ifdef USE_IP_CONTROLLER
void Network::IP_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                       unique_ptr<SyndesiID>& masterID) {
                                        
    Frame frame(buffer, masterID);

    cout << "Frame command ID : " << frame.getCommand() << endl;

#if defined(DEVICE_MODE)
    cout << "indication" << endl;
    _frameManager->indication(frame);
#elif defined(HOST_MODE)
    cout << "confirm" << endl;
    _frameManager->confirm(frame);
#endif
}
#endif

void Network::UART_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                         unique_ptr<SyndesiID>& masterID) {}

void Network::RS485_indication_or_confirm(unique_ptr<Buffer>& buffer,
                                          unique_ptr<SyndesiID>& masterID) {}

}  // namespace syndesi
