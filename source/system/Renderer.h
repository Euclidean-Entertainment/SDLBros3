/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace System {

class Window;
class Renderer
{
public:
    Renderer() = delete;
    Renderer(Window const* const hwnd);
    Renderer(Renderer const& rhs) = delete;
    Renderer(Renderer&& rhs) = delete;
    ~Renderer();

    void set_clear_color(uint8_t r, uint8_t g, uint8_t b) { SDL_SetRenderDrawColor(m_renderer, r, g, b, 255u); }
    void clear() const { SDL_RenderClear(m_renderer); }
    void present() const { SDL_RenderPresent(m_renderer); }

    SDL_Renderer* renderer() { return m_renderer; }

private:
    SDL_Renderer* m_renderer { nullptr };
};

};
