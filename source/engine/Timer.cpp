/*
 * Copyright (c) 2022, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "Timer.h"

using namespace Engine;

Timer::Timer(unsigned int intervalInTicks, TimerType type) : Timer(nullptr, intervalInTicks, type)
{
}

Timer::Timer(std::function<void()> callback, unsigned int interval, TimerType type) :
    m_callback(callback),
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
