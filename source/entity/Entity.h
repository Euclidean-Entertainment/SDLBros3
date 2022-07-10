/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <gfx/AnimationGroup.h>
#include <gfx/SpriteSheet.h>
#include <math/Vec2.h>

namespace Entity {

class Entity
{
public:
    Entity() = default;
    Entity(uint8_t x_size, uint8_t y_size);
    virtual ~Entity() = default;

    virtual void initialize(ResourceLoader& loader) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void move() = 0;

    uint8_t sprite_width() const { return m_sprite_width; }
    uint8_t sprite_height() const { return m_sprite_height; }
    bool is_animated() const { return m_is_animated; }
    bool load_animation_group(std::string const& path);
    FloatVector2 const& position() const { return m_position; }

    void set_is_animated() { m_is_animated = true; }
    void set_position(FloatVector2 const& position) { m_position = position; }

protected:
    GFX::SpriteSheet m_sheet;
    GFX::AnimationGroup m_animation_group;
    FloatVector2 m_position;
    FloatVector2 m_velocity;

    SDL_Rect m_default_sprite;

    uint8_t m_sprite_width { 8u };
    uint8_t m_sprite_height { 8u };

    bool m_is_animated { true };
    bool m_should_animate { true };

    uint32_t m_ticks { 0u }; // Internal tick counter for animation and updates
};

} // namespace Entity
