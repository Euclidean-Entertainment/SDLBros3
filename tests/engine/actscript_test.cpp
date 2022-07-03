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

    CHECK(test_queue.load_from_file("./test_data/asf/test.asf") == true);
    CHECK(test_queue.count() == EXPECTED_EVENT_COUNT);

    uint16_t expected_delay = 4u;
    uint16_t expected_command = 0u;
    size_t count = test_queue.count();
    for (auto i = 0u; i < count; i++)
    {
        auto event = test_queue.dequeue();
        CHECK(event.delay == expected_delay);
        CHECK(event.command == expected_command);

        expected_delay <<= 1u;
        expected_command++;
    }

    CHECK(test_queue.count() == 0u);
}

TEST_CASE("Test ASF bad magic")
{
    Engine::ActScript::Queue test_queue;

    CHECK(test_queue.load_from_file("./test_data/asf/bad_magic.asf") == false);
    CHECK(test_queue.count() == 0u);
}

TEST_CASE("Test ASF corrupt file")
{
    Engine::ActScript::Queue test_queue;

    CHECK(test_queue.load_from_file("./test_data/asf/corrupt_file.asf") == false);
    CHECK(test_queue.count() == 0u);
}

TEST_CASE("Test ASF corrupt size")
{
    Engine::ActScript::Queue test_queue;

    CHECK(test_queue.load_from_file("./test_data/asf/corrupt_size.asf") == false);
    CHECK(test_queue.count() == 0u);
}
