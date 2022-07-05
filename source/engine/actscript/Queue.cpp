/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <cstring>
#include <engine/actscript/Queue.h>
#include <system/Log.h>

namespace Engine::ActScript {

void Queue::enqueue_event(Queue::Event const& event)
{
    m_queue.push(event);
}

void Queue::enqueue_event(uint16_t command, uint16_t delay)
{
    m_queue.emplace(command, delay);
}

void Queue::flush()
{
    while (m_queue.size() > 0)
        m_queue.pop();
}

Queue::Event Queue::dequeue()
{
    ActionScriptEvent event(m_queue.front()); // Invoke copy constructor
    m_queue.pop();

    return event;
}

bool Queue::load_from_file(std::string const& path)
{
    // Purge the queue
    flush();

    DiskFile asf_file;
    if (asf_file.open(path) == false)
        return false;

    asf_header header;
    auto bytes_read = asf_file.read(&header, sizeof(header));
    if (bytes_read != sizeof(header))
    {
        log(LogLevel::WARN, "Didn't read enough bytes for ASF header (is the file corrupt?)!");
        return false;
    }

    if (strncmp(header.magic, asf_header::MAGIC, sizeof(asf_header::magic)) != 0u)
    {
        log(LogLevel::WARN, "Bad ASF header magic! Got %s", header.magic);
        return false;
    }

    if (header.number_of_events == 0u)
    {
        log(LogLevel::WARN, "Bad number of events in ASF header!");
        return false;
    }

    for (auto i = 0u; i < header.number_of_events; i++)
    {
        uint32_t value;
        bytes_read = asf_file.read(&value, sizeof(uint32_t));
        if (bytes_read != sizeof(uint32_t))
        {
            // Flush whatever is already in the queue
            flush();
            log(LogLevel::WARN, "Didn't read enough bytes for event!");

            return false;
        }

        uint16_t command = static_cast<uint16_t>((value >> 16U) & 0xFFFFU);
        uint16_t delay = static_cast<uint16_t>(value & 0xFFFFu);

        m_queue.push(Event(command, delay));
    }

    return true;
}

} // namespace Engine::ActScript
