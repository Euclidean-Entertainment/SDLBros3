/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <system/Window.h>
#include <engine/State.h>
#include <memory>
#include <stack>

namespace Engine {

class State;
class Game
{
    static constexpr uint32_t MILLISECONDS_PER_SECOND = 1000u;

public:
    static std::unique_ptr<Game> try_create();

    Game();
    ~Game();

    Game(Game const& game) = delete;
    Game(Game&& game) = delete;

    void start();

private:
    bool init();
    void shutdown();

    void loop();

    void update();
    void render();
    void handle_input();

private:
    std::unique_ptr<Window> m_window { nullptr };
    bool m_running { false };
    uint32_t m_delta_time { 0ul };
    uint32_t m_last_time { 0ul };
    uint32_t m_accumulated_time { 0ul };
    uint32_t m_frames { 0ul };

    std::stack<State*> m_states;
};


}
