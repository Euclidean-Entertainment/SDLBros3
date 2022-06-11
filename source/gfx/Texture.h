/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <NonCopy.h>

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

    std::string const& name() const { return m_name; }
    bool load(SDL_Renderer* renderer, std::string const& path) { return load(renderer, path, "default"); }
    bool load(SDL_Renderer* renderer, std::string const& path, std::string const& name);

    int width() const { return m_width; }
    int height() const { return m_height; }
    SDL_Texture* texture() const { return m_texture.get(); }

private:
    std::string m_name;
    int m_width { 0 };
    int m_height { 0 };
    std::unique_ptr<SDL_Texture, Deleter> m_texture { nullptr };
};

};
