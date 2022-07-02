/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <entity/Entity.h>

namespace Entity {

Entity::Entity(uint8_t x_size, uint8_t y_size)
    : m_sprite_width(x_size),
      m_sprite_height(y_size)
{
    m_default_sprite.w = x_size;
    m_default_sprite.h = y_size;
    m_default_sprite.x = 0;
    m_default_sprite.y = 0;
}

bool Entity::load_animation_group(std::string const& path)
{
    return m_animation_group.load(path);
}

}
