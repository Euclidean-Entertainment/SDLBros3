/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <SDL2/SDL.h>
#include <engine/Game.h>
#include <states/Title.h>
#include <system/Log.h>

namespace Engine {

static bool g_initialized = false;

std::unique_ptr<Game> Game::try_create()
{
    auto game = std::unique_ptr<Game>(new Game());
    if (game == nullptr)
    {
        log(LogLevel::FATAL, "Failed to create Game instance!");
    }

    return game;
}

bool Game::init()
{
    // Initialise SDL
    auto sdl_rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    if (sdl_rc != 0)
    {
        log(LogLevel::FATAL, "Failed to intialise SDL!");
        return false;
    }

    // Create our window
    auto real_x_resolution = static_cast<int>(X_RESOLUTION * RENDER_SCALE);
    auto real_y_resolution = static_cast<int>(Y_RESOLUTION * RENDER_SCALE);
    m_window = Window::try_create(real_x_resolution, real_y_resolution, "Super Mario Bros. 3");
    if (m_window == nullptr)
    {
        return false;
    }

    m_window->set_render_scale(RENDER_SCALE);
    m_window->set_clear_color(0, 0, 0);

    // Create the first state (title state)
    m_states.push(new States::TitleState(*this, m_window->renderer()));
    g_initialized = true;
    return true;
}

void Game::start()
{
    log(LogLevel::INFO, "Starting Engine...");
    auto init_ok = init();

    if (init_ok == false)
    {
        return;
    }

    m_running = true;
    loop();
    shutdown();
}

void Game::shutdown()
{
    // TODO: Cleanup!
}

void Game::handle_input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    auto current = m_states.top();
    current->tick_timers();
    current->update();
}

void Game::render()
{
    m_states.top()->render();
}

void Game::loop()
{
    while (m_running)
    {
        m_window->clear();
        auto const now = SDL_GetTicks();

        handle_input();
        update();
        render();

        m_frames++;
        m_delta_time = SDL_GetTicks() - now;
        m_accumulated_frame_time += m_delta_time;
        m_last_time = now;

        if (TARGET_FRAME_TIME > m_delta_time)
        {
            SDL_Delay(TARGET_FRAME_TIME - m_delta_time);
        }

        m_accumulated_time += SDL_GetTicks() - now;
        if (m_accumulated_time >= 1000u)
        {
            log(LogLevel::INFO, "Tick, frames: %u", m_frames);
            m_accumulated_time = 0u;
            m_frames = 0u;
        }

        // Flip the render buffer to the screen
        m_window->present();
    }
}

} // namespace Engine
