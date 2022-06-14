/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <gfx/Texture.h>
#include <system/Log.h>
#include <SDL2/SDL_image.h>

namespace GFX {

bool Texture::load(SDL_Renderer* renderer, std::string const& path, std::string const& name)
{
    if (m_loaded)
    {
        log(LogLevel::WARN, "Texture %s already loaded!", name.c_str());
        return true;
    }

    log(LogLevel::INFO, "Attempting to load texture %s...", path.c_str());
    m_texture = std::unique_ptr<SDL_Texture, Deleter>(IMG_LoadTexture(renderer, path.c_str()));
    if (!m_texture)
    {
        log(LogLevel::WARN, "Failed to load texture!");
        return false;
    }

    auto sdl_rc = SDL_QueryTexture(m_texture.get(), NULL, NULL, &m_width, &m_height);
    if (sdl_rc != 0)
    {
        // Just log the incident, but don't fail the load
        log(LogLevel::WARN, "Failed to query texture");
    }

    m_name = name;
    m_loaded = true;

    return true;
}

Texture& Texture::operator=(Texture&& rhs)
{
    m_name      = std::move(rhs.m_name);
    m_loaded    = std::exchange(rhs.m_loaded, false);
    m_width     = std::exchange(rhs.m_width, 0);
    m_height    = std::exchange(rhs.m_height, 0);
    m_texture   = std::move(rhs.m_texture);

    return *this;
}

};
