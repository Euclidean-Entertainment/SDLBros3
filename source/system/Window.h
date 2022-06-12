/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <system/Renderer.h>

namespace System {

class Window
{
    static constexpr unsigned DEFAULT_WIDTH = 640;
    static constexpr unsigned DEFAULT_HEIGHT = 480;

public:
    static std::unique_ptr<Window> try_create(int width, int height, const std::string& title);

    Window() = delete;
    Window(int width, int height, const std::string& title);
    ~Window();

    bool create();
    void clear() const;
    void set_clear_color(uint8_t r, uint8_t g, uint8_t b);
    void present() const;

    int width() const { return m_width; }
    int height() const { return m_height; }
    std::string const& title() const { return m_title; }

    SDL_Window const* hwnd() const { return m_hwnd; }
    Renderer* renderer() const { return m_renderer.get(); }

private:
    int m_width { DEFAULT_WIDTH };
    int m_height { DEFAULT_HEIGHT };
    std::string m_title;

    SDL_Window* m_hwnd { nullptr };
    std::unique_ptr<Renderer> m_renderer { nullptr };
};


}

using System::Window;
