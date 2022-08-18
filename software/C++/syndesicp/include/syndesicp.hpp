/**
 * @file syndesicp.hpp
 * @author Sébastien Deriaz
 * @brief Public header file
 * @version 0.1
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SYNDESICP_H
#define SYNDESICP_H

#include "callbacks.hpp"
#include "core.hpp"
#include "general_config.hpp"
#include "payloads.hpp"


#if !defined(HOST_MODE) && !defined(DEVICE_MODE)
    #error "MODE unspecified"
#endif


#endif  // SYNDESICP_H