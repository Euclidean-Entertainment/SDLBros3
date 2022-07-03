/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <SDL2/SDL.h>
#include <algorithm>
#include <gfx/FontRenderer.h>
#include <system/Log.h>

namespace GFX {

// Font sprite sheet x-index Look Up Table
static int const character_index_lut[59] = {
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x20-0x2F
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11,                 // 0x30-0x39
    0, 0, 0, 0, 0, 0, 0,                            // 0x3A-0x41
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36
};

FontRenderer::FontRenderer(ResourceLoader& loader)
{
    (void)m_font_sheet.load(loader, "./data/sheets/font.png", "glyphs");
}

void FontRenderer::draw_string(SDL_Renderer* renderer, int x, int y, std::string const& message)
{
    if (m_font_sheet.texture().loaded() == false)
    {
        return;
    }

    auto total_width = static_cast<int>(message.length() * GLYPH_WIDTH);
    SDL_Texture* string_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, total_width, GLYPH_HEIGHT);
    SDL_SetTextureBlendMode(string_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, string_texture);
    SDL_RenderClear(renderer);

    SDL_Rect dest_rect = { 0, 0, GLYPH_WIDTH, GLYPH_HEIGHT };
    for (auto const& character : message)
    {
        SDL_Rect clip_rect = { 0, 0, GLYPH_WIDTH, GLYPH_HEIGHT };
        auto character_lut_index = character - ' ';

        // Convert a lower case character to an upper case one
        // This is marked `unlikely` because we control the text data, which
        // will all be upper case, but you never know!
        if (islower(character)) [[unlikely]]
            character_lut_index = toupper(character);

        auto const sheet_x_offset = character_index_lut[character_lut_index];
        clip_rect.x = GLYPH_WIDTH * sheet_x_offset;
        SDL_RenderCopy(renderer, m_font_sheet.texture().texture(), &clip_rect, &dest_rect);

        // Increment to the next slot to draw to
        dest_rect.x += GLYPH_WIDTH;
    }

    // Draw the string to the screen
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_Rect from_rect = { 0, 0, total_width, GLYPH_HEIGHT };
    SDL_Rect to_rect = { x, y, total_width, GLYPH_HEIGHT };
    SDL_RenderCopy(renderer, string_texture, &from_rect, &to_rect);
}

} // namespace GFX
