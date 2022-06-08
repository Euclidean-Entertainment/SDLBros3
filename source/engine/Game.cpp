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

}

void Game::render()
{
}

void Game::loop()
{
    while (m_running)
    {
        handle_input();
        update();
        render();

        // Flip the render buffer to the screen
        m_window->renderer()->clear();
        m_window->renderer()->present();
    }
}

}
