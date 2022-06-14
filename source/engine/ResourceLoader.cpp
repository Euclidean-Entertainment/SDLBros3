/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <engine/ResourceLoader.h>
#include <engine/Game.h>
#include <system/Log.h>

namespace Engine {

template<>
GFX::Texture ResourceLoader::load(std::string const& path, std::string const& name)
{
    GFX::Texture texture;

    auto load_rc = texture.load(m_game.renderer(), path, name);
    if (load_rc == false)
    {
        return {};
    }

    return texture;
}

};
