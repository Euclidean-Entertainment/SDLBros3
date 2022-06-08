/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <memory>
#include <system/Window.h>

namespace Engine {

class Game
{
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
};


}
