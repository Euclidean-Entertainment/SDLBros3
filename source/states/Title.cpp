/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <states/Title.h>

namespace States {

TitleState::TitleState(Engine::Game& game, SDL_Renderer* renderer) : State(game, renderer)
{
    init_resources();
}

void TitleState::init_resources()
{
    // Load the background images
    (void)m_floor.load(m_game.resource_loader(), "./data/backgrounds/title/floor.png", "floor");
    m_floor.set_y(m_game.window_height() - m_floor.height());

    (void)m_curtain.load(m_game.resource_loader(), "./data/backgrounds/title/curtain.png", "curtain");
}

void TitleState::handle_input(SDL_Event const&)
{

}

void TitleState::update()
{
    // Wait for just over a second
    if (m_ticks < 70)
    {
        m_ticks++;
        return;
    }

    m_curtain.set_y(m_curtain.y() - 2);
    m_ticks++;
}

void TitleState::render()
{
    m_floor.draw(m_renderer);
    m_curtain.draw(m_renderer);
}


};
