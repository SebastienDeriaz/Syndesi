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
    _network->request(frame);
}

void FrameManager::response(Frame& frame) {
    _network->request(frame);
}
/*
 * Lower layer
 */
void FrameManager::indication(Frame& frame) {
    _callbacks->indication(frame);
}
void FrameManager::confirm(Frame& frame) {
    _callbacks->confirm(frame);
}

}  // namespace syndesi