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
    init_animations();
}

void TitleState::init_resources()
{
    // Load the background images
    (void)m_floor.load(m_game.resource_loader(), "./data/backgrounds/title/floor.png", "floor");
    m_floor.set_y(m_game.window_height() - m_floor.height());

    (void)m_curtain.load(m_game.resource_loader(), "./data/backgrounds/title/curtain.png", "curtain");
}

void TitleState::init_animations() 
{
    // Create a timer for the curtain animation to begin after 70 ticks.
    m_curtain_timer = std::make_unique<Timer>(Timer(70, TimerType::ONE_SHOT));
    m_curtain_timer->start();
}

void TitleState::handle_input(SDL_Event const&)
{

}

void TitleState::update()
{
    // Curtain up animation.
    m_curtain_timer->tick();
    if (m_curtain_timer->is_running())
    {
        return;
    }
    m_curtain.set_y(m_curtain.y() - 2);
}

void TitleState::render()
{
    m_floor.draw(m_renderer);
    m_curtain.draw(m_renderer);
}


};
