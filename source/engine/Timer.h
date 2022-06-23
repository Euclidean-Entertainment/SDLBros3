/*
 * Copyright (c) 2022, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <functional>

namespace Engine
{

enum class TimerType : int
{
    ONE_SHOT,
    REPEAT
};

class Timer
{
public:
    Timer(uint32_t intervalInTicks, TimerType type = TimerType::ONE_SHOT);
    Timer(std::function<void()> callback, uint32_t intervalInTicks, TimerType type);

    void tick();

    void reset() 
    {
        m_ticks = 0; 
    }

    void start()
    {
        m_running = true;
    }
    void pause()
    {
        m_running = false;
    }
    void stop()
    {
        m_running = false;
        m_ticks = 0;
    }

    void set_callback(std::function<void()> callback)
    {
        m_callback = callback;
    }
    std::function<void()> get_callback() const
    {
        return m_callback;
    }

    void set_interval(uint32_t interval)
    {
        m_interval = interval;
    }
    uint32_t get_interval() const
    {
        return m_interval;
    }

    void set_type(TimerType type)
    {
        m_type = type;
    }
    TimerType get_type() const
    {
        return m_type;
    }

    bool is_running() const
    {
        return m_running;
    }
    uint32_t get_ticks() const
    {
        return m_ticks;
    }

private:
    std::function<void()> m_callback;
    unsigned int m_interval { 60 };
    TimerType m_type { TimerType::ONE_SHOT };

    unsigned int m_ticks { 0 };
    bool m_running { false };
};

};

using Engine::Timer;
using Engine::TimerType;
