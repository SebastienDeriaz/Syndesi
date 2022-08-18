/**
 * @file framemanager.hpp
 *
 * @brief Management of frames
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H

#include <functional>

#include "callbacks.hpp"
#include "syndesi_types.hpp"
#include <iostream>

using namespace std;


namespace syndesi {

/**
 * @brief Class to manage frames after they've been parsed by the network
 * interface
 *
 */
class FrameManager : SAP::IFrameManager_bottom, SAP::IFrameManager_top {
    friend class Core;

    

   public:

    FrameManager() {};
    ~FrameManager() {};

   private:
    /*
     * Upper layer
     */
    SAP::ICallbacks_bottom* _callbacks = nullptr;
    void registerCallbacks(SAP::ICallbacks_bottom* callbacks) {
        _callbacks = callbacks;
    };
    void response(Frame& frame);
    // From core
    void request(Frame& frame);
    /*
     * Lower layer
     */
    SAP::INetwork_top* network = nullptr;
    void registerNetwork(SAP::INetwork_top* _network) { network = _network;};
    void indication(Frame& frame);
    void confirm(Frame& frame);
};

}  // namespace syndesi

#endif  // FRAME_MANAGER_H
