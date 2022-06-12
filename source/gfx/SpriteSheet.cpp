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

bool SpriteSheet::load(SDL_Renderer* renderer, std::string const& path)
{
    return m_texture.load(renderer, path);
}

void SpriteSheet::draw(SDL_Renderer* renderer, unsigned x, unsigned y, unsigned sheet_grid_x, unsigned sheet_grid_y)
{
    // Set up the SDL_Rect to slice out the appropriate sprite from the sheet
    SDL_Rect sheet_rect;
    SDL_Rect dest_rect;

    // Disgusting casts as SDL uses signed types to represent x and y(?)
    sheet_rect.x = static_cast<int>(sheet_grid_x * m_xsize);
    sheet_rect.y = static_cast<int>(sheet_grid_y * m_ysize);
    sheet_rect.w = static_cast<int>(m_xsize);
    sheet_rect.h = static_cast<int>(m_ysize);

    dest_rect.x = static_cast<int>(x);
    dest_rect.y = static_cast<int>(y);
    dest_rect.w = static_cast<int>(m_xsize);
    dest_rect.h = static_cast<int>(m_ysize);

    (void)SDL_RenderCopy(renderer, m_texture.texture(), &sheet_rect, &dest_rect);
}

};
