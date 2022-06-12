/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <engine/Game.h>
#include <system/Log.h>
#include <SDL2/SDL.h>

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

Game::Game()
{

}

Game::~Game()
{

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
    m_window = Window::try_create(640, 480, "Test");
    if (m_window == nullptr)
    {
        return false;
    }

    m_window->set_clear_color(255, 255, 255);
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

}

void Game::handle_input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
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
    if (m_last_time == 0u)
    {
        return;
    }

    auto dt [[maybe_unused]] = static_cast<float>(m_delta_time / MILLISECONDS_PER_SECOND);
    SDL_Delay(16);
}

void Game::render()
{
}

void Game::loop()
{
    while (m_running)
    {
        m_window->clear();
        const auto now = SDL_GetTicks();

        handle_input();
        update();
        render();

        m_frames++;
        m_delta_time = SDL_GetTicks() - now;
        m_accumulated_time += m_delta_time;
        m_last_time = now;
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

}
