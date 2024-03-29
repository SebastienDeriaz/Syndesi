/**
 * @file core.hpp
 *
 * @brief Syndesi core
 *
 * @author Sébastien Deriaz
 * @date 09.08.2022
 */

#ifndef CORE_H
#define CORE_H

#include "frame.hpp"
#include "callbacks.hpp"
#include "framemanager.hpp"
#include "network.hpp"

namespace syndesi {

class Core {
   private:

    void factory_init();

    /*
    * Layers
    */
   Callbacks callbacks;
   FrameManager frameManager;
   
   public:

    Network network;

    void sendRequest(Payload& payload, SyndesiID& id);

    void init();

    Core() {factory_init();};
    ~Core(){};
};

}  // namespace syndesi

#endif  // CORE_H