/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <gfx/SpriteSheet.h>
#include <string>

namespace GFX {

class FontRenderer final
{
    static constexpr uint8_t GLYPH_WIDTH = 8u;
    static constexpr uint8_t GLYPH_HEIGHT = GLYPH_WIDTH;

public:
    FontRenderer(ResourceLoader& loader);
    ~FontRenderer() = default;

    void draw_string(SDL_Renderer* renderer, int x, int y, std::string const& message);

private:
    SpriteSheet m_font_sheet { GLYPH_WIDTH, GLYPH_HEIGHT };
};

} // namespace GFX
