/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <cstdarg>

namespace System
{

enum class LogLevel : int
{
    INFO,
    WARN,
    CRIT,
    FATAL
};

[[gnu::format(printf, 2, 3)]] void log(LogLevel component, const char* str, ...);

}

// Thanks Serenity :^)
#define log_if(flag, component, fmt, ...)              \
    do                                                 \
    {                                                  \
        if constexpr (flag)                            \
            System::log(level, fmt, ##__VA_ARGS__); \
    } while (0)

using System::LogLevel;
