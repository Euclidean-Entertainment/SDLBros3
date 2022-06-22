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

void Timer::start()
{
    m_running = true;
}

void Timer::pause()
{
    m_running = false;
}

void Timer::stop()
{
    m_running = false;
    m_ticks = 0;
}

void Timer::reset()
{
    m_ticks = 0;
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

void Timer::set_callback(std::function<void()> callback)
{
    m_callback = callback;
}

const std::function<void()>& Timer::get_callback() const
{
    return m_callback;
}

void Timer::set_interval(unsigned int interval)
{
    m_interval = interval;
}

const unsigned int& Timer::get_interval() const
{
    return m_interval;
}

void Timer::set_type(TimerType type)
{
    m_type = type;
}

const TimerType& Timer::get_type() const
{
    return m_type;
}

bool Timer::is_running() const 
{
    return m_running;
}

const unsigned int& Timer::get_ticks() const 
{
    return m_ticks;
}
