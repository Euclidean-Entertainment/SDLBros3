/*
 * Copyright (c) 2022
 * Jesse Buhagiar <jooster669@gmail.com>, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <engine/Timer.h>
#include <gfx/FontRenderer.h>
#include <memory>
#include <vector>

namespace Engine {

class Game;
class State
{
public:
    State(Game& game, SDL_Renderer* renderer);
    State(State const& rhs) = delete;
    State(State&&) = delete;
    virtual ~State() {}

    virtual void handle_input(SDL_Event const& event) = 0;
    virtual void tick_timers();
    virtual void update() = 0;
    virtual void render() = 0;

    std::shared_ptr<Timer> create_timer(uint32_t ticks, TimerType type = TimerType::ONE_SHOT);
    std::shared_ptr<Timer> create_timer(std::function<void()> callback, uint32_t ticks, TimerType type = TimerType::ONE_SHOT);

protected:
    Game& m_game;
    SDL_Renderer* m_renderer;
    GFX::FontRenderer m_font_renderer;
    std::vector<std::shared_ptr<Timer>> m_timers;
};

} // namespace Engine

using Engine::State;
