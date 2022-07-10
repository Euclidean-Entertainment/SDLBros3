/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <states/Title.h>
#include <system/Log.h>

namespace States {

TitleState::TitleState(Engine::Game& game, SDL_Renderer* renderer)
: State(game, renderer)
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
    m_curtain_timer = create_timer(std::bind(&TitleState::raise_curtain, this), CURTAIN_TIMER_DELAY_TICKS, TimerType::ONE_SHOT);
    m_curtain_timer->start();
}

void TitleState::raise_curtain()
{
    m_should_raise_curtain = true;
}

void TitleState::handle_input(SDL_Event const&)
{
    // TODO: Handle input here
}

void TitleState::update()
{
    if (m_should_raise_curtain)
    {
        if ((m_curtain.y() + m_curtain.height()) > 0)
        {
            m_curtain.set_y(m_curtain.y() - 2);
        }
        else
        {
            m_should_raise_curtain = false;
        }
    }
}

void TitleState::render()
{
    m_floor.draw(m_renderer);
    m_curtain.draw(m_renderer);
}

} // namespace States
