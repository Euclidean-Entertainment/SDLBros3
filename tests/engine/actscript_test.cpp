/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <engine/actscript/Queue.h>

static constexpr size_t EXPECTED_EVENT_COUNT = 4u;

TEST_CASE("Test ASF queue load and pump")
{
    Engine::ActScript::Queue test_queue;

    CHECK(test_queue.load_from_file("./test_data/evt/test.evt") == true);
    CHECK(test_queue.count() == EXPECTED_EVENT_COUNT);

    uint16_t expected_delay = 10u;
    uint16_t expected_command = 1u;
    size_t count = test_queue.count();
    for (auto i = 0u; i < count; i++)
    {
        auto event = test_queue.dequeue();
        CHECK(event.delay == expected_delay);
        CHECK(event.command_id == expected_command);

        expected_delay += 10;
        expected_command++;
    }

    CHECK(test_queue.count() == 0u);
}

TEST_CASE("Test ActionScript Queue enque events")
{
    Engine::ActScript::Queue test_queue;

    test_queue.enqueue_event(Engine::ActScript::Queue::Event(0x1234u, 0x5678u, "event"));
    test_queue.enqueue_event(0xabcdu, 0x12abu, "event2");

    auto event1 = test_queue.dequeue();
    CHECK(event1.delay == 0x1234u);
    CHECK(event1.command_id == 0x5678u);
    CHECK(event1.name == "event");

    auto event2 = test_queue.dequeue();
    CHECK(event2.delay == 0xabcdu);
    CHECK(event2.command_id == 0x12abu);
    CHECK(event2.name == "event2");

    CHECK(test_queue.count() == 0u);
}
