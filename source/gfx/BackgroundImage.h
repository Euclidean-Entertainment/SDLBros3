/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <engine/ResourceLoader.h>
#include <gfx/Texture.h>

namespace GFX {

class BackgroundImage
{
    MAKE_NONCOPYABLE(BackgroundImage)
    MAKE_NONMOVABLE(BackgroundImage)

public:
    BackgroundImage() = default;
    ~BackgroundImage() = default;

    bool load(Engine::ResourceLoader& loader, std::string const& path, std::string const& name);

    void draw(SDL_Renderer* renderer);
    void set_x(int x) { m_x = x; }
    void set_y(int y) { m_y = y; }
    void set_alpha(uint8_t alpha);

    int x() const { return m_x; }
    int y() const { return m_y; }
    int width() const { return m_texture.width(); }
    int height() const { return m_texture.height(); }
    uint8_t alpha() const { return m_alpha; }

private:
    int m_x { 0 };
    int m_y { 0 };
    uint8_t m_alpha { 255u };
    Texture m_texture;
};

} // namespace GFX

using GFX::BackgroundImage;
