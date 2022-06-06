/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

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

    int width() const { return m_width; }
    int height() const { return m_height; }
    std::string const& title() const { return m_title; }

private:
    int m_width { DEFAULT_WIDTH };
    int m_height { DEFAULT_HEIGHT };
    std::string m_title;

    SDL_Window* m_hwnd { nullptr };
};


}

using System::Window;
