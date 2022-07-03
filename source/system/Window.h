/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <NonCopy.h>
#include <string>
#include <system/Renderer.h>

namespace System {

class Window
{
    static constexpr unsigned DEFAULT_WIDTH = 640;
    static constexpr unsigned DEFAULT_HEIGHT = 480;

    MAKE_NONCOPYABLE(Window)
    MAKE_NONMOVABLE(Window)
public:
    static std::unique_ptr<Window> try_create(int width, int height, std::string const& title);

    Window() = delete;
    Window(int width, int height, std::string const& title);
    ~Window();

    bool create();
    void clear() const;
    void set_clear_color(uint8_t r, uint8_t g, uint8_t b);
    void set_render_scale(float scale);
    void present() const;

    int width() const { return m_width; }
    int height() const { return m_height; }
    std::string const& title() const { return m_title; }

    SDL_Window const* hwnd() const { return m_hwnd; }
    SDL_Renderer* renderer() const { return m_renderer.get()->renderer(); }

private:
    int m_width { DEFAULT_WIDTH };
    int m_height { DEFAULT_HEIGHT };
    std::string m_title;

    SDL_Window* m_hwnd { nullptr };
    std::unique_ptr<Renderer> m_renderer { nullptr };
};

} // namespace System

using System::Window;
