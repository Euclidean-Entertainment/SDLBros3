/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <engine/ResourceLoader.h>
#include <gfx/Texture.h>
#include <cstdint>

namespace GFX {

class SpriteSheet
{
public:
    SpriteSheet(uint8_t xsize, uint8_t ysize);
    ~SpriteSheet() = default;

    bool load(ResourceLoader& loader, std::string const& path, std::string const& name);
    void set_xsize(uint8_t xsize) { m_xsize = xsize; }
    void set_ysize(uint8_t ysize) { m_ysize = ysize; }
    void draw(SDL_Renderer* renderer, unsigned x, unsigned y, unsigned sheet_grid_x, unsigned sheet_grid_y);

    Texture const& texture() const { return m_texture; }
    uint8_t xsize() const { return m_xsize; }
    uint8_t ysize() const { return m_ysize; }

private:
    uint8_t m_xsize { 0u };
    uint8_t m_ysize { 0u };
    Texture m_texture;  // Texture that holds this spritesheet
};

};
