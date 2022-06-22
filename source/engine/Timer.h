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
    Timer(std::function<void()> callback, unsigned int intervalInTicks, TimerType type);

    void set_callback(std::function<void()> callback);
    const std::function<void()>& get_callback() const;

    void set_interval(unsigned int interval);
    const unsigned int& get_interval() const;

    void set_type(TimerType type);
    const TimerType& get_type() const;

    bool is_running() const;
    const unsigned int& get_ticks() const;

    void reset();

    void start();
    void pause();
    void stop();

    void tick();

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
