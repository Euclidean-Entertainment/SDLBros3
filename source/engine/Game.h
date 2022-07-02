/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <engine/ResourceLoader.h>
#include <engine/State.h>
#include <memory>
#include <stack>
#include <system/Window.h>

namespace Engine {

class State;
class Game
{
    friend class ResourceLoader;

    static constexpr uint32_t MILLISECONDS_PER_SECOND = 1000u;
    static constexpr uint32_t TARGET_FRAMERATE = 60u;
    static constexpr uint32_t TARGET_FRAME_TIME = MILLISECONDS_PER_SECOND / TARGET_FRAMERATE;

    static constexpr int X_RESOLUTION_NTSC = 256;
    static constexpr int Y_RESOLUTION_NTSC = 224;
    static constexpr int Y_RESOLUTION_PAL  = 240;

    static constexpr int X_RESOLUTION = 256;
    static constexpr int Y_RESOLUTION = Y_RESOLUTION_NTSC;
    static constexpr float RENDER_SCALE = 3.0f;

public:
    static std::unique_ptr<Game> try_create();

    Game();
    ~Game();

    Game(Game const& game) = delete;
    Game(Game&& game) = delete;

    void start();

    constexpr int window_width() const { return static_cast<int>(X_RESOLUTION); }
    constexpr int window_height() const { return static_cast<int>(Y_RESOLUTION); }

    ResourceLoader& resource_loader() { return m_resource_loader; }

private:
    bool init();
    void shutdown();

    void loop();

    void update();
    void render();
    void handle_input();

    SDL_Renderer* renderer() { return m_window->renderer(); }

private:
    std::unique_ptr<Window> m_window { nullptr };
    bool m_running { false };
    uint32_t m_delta_time { 0ul };
    uint32_t m_last_time { 0ul };
    uint32_t m_accumulated_frame_time { 0ul };
    uint32_t m_accumulated_time { 0ul };
    uint32_t m_frames { 0ul };

    std::stack<State*> m_states;

    ResourceLoader m_resource_loader { *this };
};

} // namespace Engine
