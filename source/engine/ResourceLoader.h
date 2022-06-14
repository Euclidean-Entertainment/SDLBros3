/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <gfx/Texture.h>
#include <NonCopy.h>

namespace Engine {

class Game;
class ResourceLoader final
{
    MAKE_NONCOPYABLE(ResourceLoader)
    MAKE_NONMOVABLE(ResourceLoader)

public:
    ResourceLoader() = delete;
    ResourceLoader(Game& game) : m_game(game){}
    ~ResourceLoader() = default;

    GFX::Texture load_texture(std::string const& path) { return load_texture(path, "default"); };
    GFX::Texture load_texture(std::string const& path, std::string const& name);

private:
    Game& m_game;
};

};

using Engine::ResourceLoader;
