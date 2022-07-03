/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <gfx/SpriteSheet.h>

namespace GFX {

SpriteSheet::SpriteSheet(uint8_t xsize, uint8_t ysize)
: m_xsize(xsize),
  m_ysize(ysize)
{
}

bool SpriteSheet::load(ResourceLoader& loader, std::string const& path, std::string const& name)
{
    m_texture = loader.load<GFX::Texture>(path, name);
    return m_texture.loaded();
}

void SpriteSheet::draw(SDL_Renderer* renderer, int x, int y, int sheet_x, int sheet_y)
{
    // Set up the SDL_Rect to slice out the appropriate sprite from the sheet
    SDL_Rect sheet_rect;
    SDL_Rect dest_rect;

    // Disgusting casts as SDL uses signed types to represent x and y(?)
    sheet_rect.x = sheet_x;
    sheet_rect.y = sheet_y;
    sheet_rect.w = m_xsize;
    sheet_rect.h = m_ysize;

    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = m_xsize;
    dest_rect.h = m_ysize;

    (void)SDL_RenderCopy(renderer, m_texture.texture(), &sheet_rect, &dest_rect);
}

} // namespace GFX
