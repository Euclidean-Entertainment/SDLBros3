/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <cstdio>
#include <system/Log.h>
#include <system/Window.h>

namespace System {

std::unique_ptr<Window> Window::try_create(int width, int height, std::string const& title)
{
    auto window = std::unique_ptr<Window>(new Window(width, height, title));
    if (!window)
    {
        log(LogLevel::CRIT, "Failed to allocate window!");
        return nullptr;
    }

    auto result = window->create();
    if (result == false)
    {
        window.release();
        return nullptr;
    }

    return window;
}

Window::Window(int width, int height, std::string const& title)
    : m_width(width),
      m_height(height),
      m_title(title)
{
}

Window::~Window()
{
    if (m_hwnd != nullptr)
        SDL_DestroyWindow(m_hwnd);
}

bool Window::create()
{
    log(LogLevel::INFO, "Creating window of size %d %d", m_width, m_height);

    m_hwnd = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (!m_hwnd)
    {
        log(LogLevel::CRIT, "Failed to create physical Window!");
        return false;
    }

    // Create and attach renderer to this window
    m_renderer = std::unique_ptr<Renderer>(new Renderer(this));
    if (m_renderer == nullptr)
        return false;

    return true;
}

void Window::clear() const
{
    m_renderer->clear();
}

void Window::set_render_scale(float scale)
{
    SDL_RenderSetScale(m_renderer->renderer(), scale, scale);
}

void Window::set_clear_color(uint8_t r, uint8_t g, uint8_t b)
{
    m_renderer->set_clear_color(r, g, b);
}

void Window::present() const
{
    m_renderer->present();
}

} // namespace System
