/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <gfx/BackgroundImage.h>
#include <system/Log.h>

namespace GFX {

bool BackgroundImage::load(Engine::ResourceLoader& loader, std::string const& path, std::string const& name)
{
    m_texture = loader.load<GFX::Texture>(path, name);
    return m_texture.loaded();
}

void BackgroundImage::draw(SDL_Renderer* renderer)
{
    SDL_Rect draw_rect;

    draw_rect.x = m_x;
    draw_rect.y = m_y;
    draw_rect.w = m_texture.width();
    draw_rect.h = m_texture.height();
    SDL_RenderCopy(renderer, m_texture.texture(), NULL, &draw_rect);
}

}; // namespace GFX
