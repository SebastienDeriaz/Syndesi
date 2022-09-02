/**
 * @file framemanager.cpp
 *
 * @brief Management of frames
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#include "framemanager.hpp"

namespace syndesi {
/*
 * Upper layer
 */
void FrameManager::request(Frame& frame) {
    network->request(frame);
}

void FrameManager::response(Frame& frame) {
    network->response(frame);
}

}  // namespace syndesi