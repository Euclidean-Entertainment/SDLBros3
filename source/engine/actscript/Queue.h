/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <cstdint>
#include <queue>
#include <system/File.h>

namespace Engine::ActScript {

class Queue final
{
private:
    struct [[gnu::packed]] asf_header
    {
        static constexpr char const* MAGIC = "SMB3ASF\0";
        char magic[8];
        uint16_t number_of_events;
        uint8_t major_version;
        uint8_t minor_version;
        uint8_t reserved[4];
    };

public:
    struct Event
    {
        Event(uint16_t command, uint16_t delay)
        : command(command), delay(delay) {}
        Event(Event const& event)
        : command(event.command), delay(event.delay) {}

        uint16_t command;
        uint16_t delay;
    };

public:
    Queue() = default;
    ~Queue() = default;

    bool load_from_file(std::string const& path);
    void enqueue_event(Event const& event);
    void enqueue_event(uint16_t command, uint16_t delay);
    void flush();

    Event dequeue();
    Event const& front() const { return m_queue.front(); };
    std::vector<Event>::size_type count() const { return m_queue.size(); }

private:
    std::queue<Event> m_queue;
};

using ActionScriptEvent = Queue::Event;

} // namespace Engine::ActScript
