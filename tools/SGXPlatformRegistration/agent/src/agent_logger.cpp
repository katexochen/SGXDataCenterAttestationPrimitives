/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * File: agent_logger.cpp
 *  
 * Description: Implements the logger functionality for the MP agent.  
 *
 */
#include "agent_logger.h"
#include <stdarg.h>
#include <stdio.h>

extern LogLevel glog_level;

#ifndef _WIN32

void agent_log_message(LogLevel level, const char *format, ...) {
    va_list myargs;
    va_start(myargs, format);

    if (glog_level < level) {
        va_end(myargs);
        return;
    }

    if (log_message_aux) {
        log_message_aux(level, format, myargs);
    } else {
        switch (level) {
            case MP_REG_LOG_LEVEL_ERROR:
                printf("%s", "ERROR: ");
                break;
            case MP_REG_LOG_LEVEL_INFO:
                printf("%s", "INFO: ");
                break;
            default:
                break;
        }
        vprintf(format, myargs);
    }
    va_end(myargs);
}

#else

void default_agent_log_message(LogLevel level, const char *format, ...) {
    va_list myargs;
    va_start(myargs, format);

    if (glog_level < level) {
        va_end(myargs);
        return;
    }

    switch (level) {
        case MP_REG_LOG_LEVEL_ERROR:
            printf("%s", "ERROR: ");
            break;
        case MP_REG_LOG_LEVEL_INFO:
            printf("%s", "INFO: ");
            break;
        default:
            break;
    }
    vprintf(format, myargs);
    va_end(myargs);
}

#endif
