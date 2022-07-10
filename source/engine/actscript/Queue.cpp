/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <cstring>
#include <engine/actscript/Queue.h>
#include <system/Log.h>
#include <system/JSONFile.h>

namespace Engine::ActScript {

// Free-floating function to allow `json::get<>` to work with our
// event struct
void from_json(nlohmann::json const& j, Queue::Event& event)
{
    j.at("delay").get_to(event.delay);
    j.at("command_id").get_to(event.command_id);
    j.at("name").get_to(event.name);
}

void Queue::enqueue_event(Queue::Event const& event)
{
    m_queue.push(event);
}

void Queue::enqueue_event(uint32_t delay, uint16_t command, std::string const& name)
{
    m_queue.emplace(delay, command, name);
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

    // Get all events from the JSON File
    JSONFile file(path);
    if (file.loaded() == false)
        return false;

    for (auto const& event : file.json().at("events"))
        m_queue.push(event.get<Queue::Event>());

    return true;
}

} // namespace Engine::ActScript
