/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <engine/Timer.h>
#include <gfx/FontRenderer.h>

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

    Timer* create_timer(unsigned int ticks, TimerType type = TimerType::ONE_SHOT);
    Timer* create_timer(std::function<void()> callback, unsigned int ticks, TimerType type = TimerType::ONE_SHOT);

protected:
    Game& m_game;
    SDL_Renderer* m_renderer;
    GFX::FontRenderer m_font_renderer;
    std::vector<std::unique_ptr<Timer>> m_timers;
};

};

using Engine::State;
