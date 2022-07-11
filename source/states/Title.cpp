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

    // Load the title
    (void)m_title.load(m_game.resource_loader(), "./data/backgrounds/title/title.png", "smb3_title");
    (void)m_three_sheet.load(m_game.resource_loader(), "./data/sheets/title/threes.png", "three");
    m_three_animation.load("./data/agf/title/three_glow.agf");
    m_three_animation.set_current_animation_index(0u);
    m_three_sheet.set_xsize(42);
    m_three_sheet.set_ysize(41);

    // FIXME: Do something better than this fucking trash
    m_title.set_y(28 - 0xD0);
    m_three_x_position = (m_game.window_width() / 2) - (m_three_sheet.xsize() / 2);
    m_three_y_position = ((28 + m_title.height()) - 0xD0);

    // Load the background
    (void)m_bg.load(m_game.resource_loader(), "./data/backgrounds/title/bg.png", "background");
    m_bg.set_alpha(0);
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
            m_should_drop_title = true;
        }
    }

    if (m_should_drop_title)
    {
        m_title_drop_vertical_count -= 5;
        m_title.set_y(m_title.y() + 5);
        m_three_y_position += 5;

        if (m_title_drop_vertical_count <= 0)
        {
            m_should_shake = true;
            m_should_drop_title = false;
        }
    }

    if (m_should_shake)
    {
        if ((m_shake_counter % 2u) == 0u)
        {
            // Shake up
            m_title.set_y(m_title.y() + 2);
            m_three_y_position += 2;
        }
        else
        {
            // Shake down
            m_title.set_y(m_title.y() - 2);
            m_three_y_position -= 2;
        }

        m_shake_counter--;
        if (m_shake_counter == 0u)
        {
            m_should_shake = false;
            m_should_fade_in = true;
        }
    }

    if (m_should_fade_in)
    {
        if (static_cast<uint16_t>(m_bg_alpha + 16u) >= 256u)
        {
            m_bg_alpha = 255u;
            m_should_fade_in = false;
            m_should_glow = true;
        }
        else
        {
            m_bg_alpha += 16u;
        }

        m_bg.set_alpha(m_bg_alpha);
    }

    if (m_should_glow)
    {
        m_three_animation.current_animation().tick();
    }
}

void TitleState::render()
{
    m_floor.draw(m_renderer);
    m_bg.draw(m_renderer);
    m_title.draw(m_renderer);
    m_three_sheet.draw(m_renderer, m_three_x_position, m_three_y_position,
                       m_three_animation.current_animation().current_frame().sheet_rect.x,
                       m_three_animation.current_animation().current_frame().sheet_rect.y);
    m_curtain.draw(m_renderer);
}

} // namespace States
