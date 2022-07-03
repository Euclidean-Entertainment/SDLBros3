/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <utility>

namespace GFX {

class Texture
{
    MAKE_NONCOPYABLE(Texture)
    struct Deleter
    {
        void operator()(SDL_Texture* texture)
        {
            SDL_DestroyTexture(texture);
        }
    };

public:
    Texture() = default;
    ~Texture() = default;

    Texture(Texture&& rhs) noexcept
    : m_name(std::move(rhs.m_name)),
      m_loaded(std::exchange(rhs.m_loaded, false)),
      m_width(std::exchange(rhs.m_width, 0)),
      m_height(std::exchange(rhs.m_height, 0)),
      m_texture(std::move(rhs.m_texture))
    {
    }

    bool load(SDL_Renderer* renderer, std::string const& path) { return load(renderer, path, "default"); }
    bool load(SDL_Renderer* renderer, std::string const& path, std::string const& name);

    int width() const { return m_width; }
    int height() const { return m_height; }
    std::string const& name() const { return m_name; }
    bool loaded() const { return m_loaded; }

    SDL_Texture* texture() const { return m_texture.get(); }

    Texture& operator=(Texture&& rhs) noexcept;

private:
    std::string m_name;
    bool m_loaded { false };
    int m_width { 0 };
    int m_height { 0 };
    std::unique_ptr<SDL_Texture, Deleter> m_texture { nullptr };
};

} // namespace GFX
