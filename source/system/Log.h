/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <cstdarg>

namespace System {

enum class LogLevel : int
{
    INFO,
    WARN,
    CRIT,
    FATAL
};

[[gnu::format(printf, 2, 3)]] void log(LogLevel component, char const* str, ...);

} // namespace System

// Thanks Serenity :^)
#define log_if(flag, level, fmt, ...)               \
    do                                              \
    {                                               \
        if constexpr (flag)                         \
            System::log(level, fmt, ##__VA_ARGS__); \
    } while (0)

using System::LogLevel;
