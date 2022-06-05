/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <cstdarg>
#include <cstdio>
#include <system/Log.h>

namespace System
{

static constexpr bool USE_COLORED_LOGGING = true;

void log(LogLevel level, const char* str, ...)
{
    std::va_list args;

    const char* label = "";
    switch (level)
    {
        case LogLevel::INFO:
        {
            if constexpr (USE_COLORED_LOGGING)
                label = "\033[96;1;1m[info]\033[0m ";
            else
                label = "[info] ";
            break;
        }

        case LogLevel::WARN:
        {
            if constexpr (USE_COLORED_LOGGING)
                label = "\033[93;1;1m[warn]\033[0m ";
            else
                label = "[warn] ";
            break;
        }

        case LogLevel::CRIT:
        {
            if constexpr (USE_COLORED_LOGGING)
                label = "\033[91;1;1m[crit]\033[0m ";
            else
                label = "[crit] ";
            break;
        }

        case LogLevel::FATAL:
        {
            if constexpr (USE_COLORED_LOGGING)
                label = "\033[91;5;1m[fatal]\033[0m ";
            else
                label = "[fatal]";
            break;
        }
    }

    va_start(args, str);
    // Print to stderr
    // TODO: This should be configurable at compile time (or runtime?!)
    if (std::fputs(label, stderr) < 0 || std::vfprintf(stderr, str, args) < 0)
    {
        std::fprintf(stderr, "Unable to write to flush info log!");
    }
    else
    {
        std::fputc('\n', stderr);
    }
    va_end(args);
}

}
