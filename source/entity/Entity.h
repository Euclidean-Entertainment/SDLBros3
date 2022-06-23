/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <gfx/SpriteSheet.h>
#include <math/Vec2.h>

namespace Entity {

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() {}

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void move() = 0;

    FloatVector2 const& position() const { return m_position; }
    void set_position(FloatVector2 const& position) { m_position = position; }

protected:
    GFX::SpriteSheet m_sheet;
    FloatVector2 m_position;
    FloatVector2 m_velocity;
};

}; // namespace Entity

using Entity::Entity;
