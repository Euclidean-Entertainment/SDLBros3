/*
 * Copyright (c) 2022, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "Timer.h"

namespace Engine {

Timer::Timer(uint32_t intervalInTicks, TimerType type)
    : Timer(nullptr, intervalInTicks, type)
{
}

Timer::Timer(std::function<void()> callback, uint32_t interval, TimerType type)
    : m_callback(callback),
      m_interval(interval),
      m_type(type)
{
}

void Timer::tick()
{
    if (m_running)
    {
        m_ticks++;
    }

    if (m_ticks >= m_interval)
    {
        if (m_callback)
        {
            m_callback();
        }

        m_ticks = 0;

        if (m_type == TimerType::ONE_SHOT)
        {
            m_running = false;
        }
    }
}

} // namespace Engine
