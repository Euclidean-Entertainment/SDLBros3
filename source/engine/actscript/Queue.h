/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <cstdint>
#include <queue>
#include <string>
#include <nlohmann/json.hpp>

namespace Engine::ActScript {

class Queue final
{
public:
    struct Event
    {
        Event() = default;
        Event(uint32_t delay, uint16_t command_id, std::string const& name)
            : delay(delay), command_id(command_id), name(name){}
        uint32_t delay;
        uint16_t command_id;
        std::string name;
    };

public:
    Queue() = default;
    ~Queue() = default;

    bool load_from_file(std::string const& path);
    void enqueue_event(Event const& event);
    void enqueue_event(uint32_t delay, uint16_t command, std::string const& name);
    void flush();

    Event dequeue();
    Event const& front() const { return m_queue.front(); };
    std::vector<Event>::size_type count() const { return m_queue.size(); }

private:
    std::queue<Event> m_queue;
};

} // namespace Engine::ActScript

using ActionScriptEvent = Engine::ActScript::Queue::Event;
using ActionScriptQueue = Engine::ActScript::Queue;
