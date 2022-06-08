/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <system/Renderer.h>
#include <system/Window.h>

namespace System {


Renderer::Renderer(Window const* const hwnd)
{
    m_renderer = SDL_CreateRenderer(const_cast<SDL_Window*>(hwnd->hwnd()), -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }
}

}
