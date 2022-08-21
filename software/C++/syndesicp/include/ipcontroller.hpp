/**
 * @file ipcontroller.hpp
 *
 * @brief IP controller
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef IP_CONTROLLER_H
#define IP_CONTROLLER_H

#include "interfaces.hpp"

#ifdef USE_IP_CONTROLLER 
#include "buffer.hpp"
#include <cstddef>

namespace syndesi {

class IPController : public SAP::IController_top {
    friend class Core;
    private:
    SAP::INetwork_bottom* _network;
    void registerNetwork(SAP::INetwork_bottom* network) {_network = network;};

    Buffer inputBuffer;
    public:
        IPController() {};
        ~IPController() {};

        /*
        * Higher layer
        */
        void request_or_response(unique_ptr<Buffer>& buffer, SyndesiID& masterID);

        // Integration with user space

        // Easy
        void IP_receive(char* data, size_t length, SyndesiID& id);
        // Efficient
        void IP_receive(char* data, size_t length, unique_ptr<SyndesiID>& id);

        void IP_send(char* data, size_t length, SyndesiID& id);
};


}

#endif // USE_IP_CONTROLLER

#endif // IP_CONTROLLER_H