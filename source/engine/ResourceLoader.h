/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <gfx/Texture.h>

namespace Engine {

class Game;
class ResourceLoader final
{
    MAKE_NONCOPYABLE(ResourceLoader)
    MAKE_NONMOVABLE(ResourceLoader)

public:
    ResourceLoader() = delete;
    explicit ResourceLoader(Game& game)
        : m_game(game) {}
    ~ResourceLoader() = default;

    template<typename T>
    T load(std::string const& path)
    {
        return load<T>(path, "default");
    }

    template<typename T>
    T load(std::string const& path, std::string const& name);

private:
    Game& m_game;
};

} // namespace Engine

using Engine::ResourceLoader;
