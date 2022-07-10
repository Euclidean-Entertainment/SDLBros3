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

void BackgroundImage::set_alpha(uint8_t alpha)
{
    auto sdl_rc = SDL_SetTextureAlphaMod(m_texture.texture(), alpha);
    if (sdl_rc != 0)
    {
        auto const* error_message = SDL_GetError();
        log(LogLevel::WARN, "Failed to set texture (%s) alpha! Reason: %s", m_texture.name().c_str(), error_message);
        return;
    }

    m_alpha = alpha;
}

} // namespace GFX
