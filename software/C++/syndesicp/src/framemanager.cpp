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
    cout << "FrameManager : sending request" << endl;
    network->request(frame);
}

void FrameManager::response(Frame& frame) {
    cout << "FrameManager response" << endl;
    network->response(frame);
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