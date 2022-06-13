/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include "engine/Game.h"

namespace Engine {

class Game;
class State
{
public:
    State(Game& game, SDL_Renderer* renderer) : m_game(game), m_renderer(renderer) {}
    State(State const& rhs) = delete;
    State(State&&) = delete;
    virtual ~State() {}

    virtual void handle_input(SDL_Event const& event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    Game& m_game;
    SDL_Renderer* m_renderer;
};

};

using Engine::State;
