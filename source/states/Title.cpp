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
    // Create a timer for the curtain animation to begin.
    const auto& toggle_curtain_up = [this]() {
        m_curtain_up = !m_curtain_up;
    };
    m_curtain_timer = std::make_unique<Timer>(
        Timer(toggle_curtain_up, 70, TimerType::ONE_SHOT)
    );
    m_curtain_timer->start();
}

void TitleState::handle_input(SDL_Event const&)
{

}

void TitleState::update()
{
    if (!m_curtain_up)
    {
        m_curtain_timer->tick();
        return;
    }
    else 
    {
        m_curtain.set_y(m_curtain.y() - 2);
    }

}

void TitleState::render()
{
    m_floor.draw(m_renderer);
    m_curtain.draw(m_renderer);
}


};
