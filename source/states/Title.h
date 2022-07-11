/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <engine/Game.h>
#include <engine/State.h>
#include <engine/Timer.h>
#include <gfx/AnimationGroup.h>
#include <gfx/BackgroundImage.h>
#include <gfx/SpriteSheet.h>
#include <memory>

namespace States {

class TitleState : public Engine::State
{
    static constexpr uint32_t CURTAIN_TIMER_DELAY_TICKS = 70u;

public:
    TitleState(Engine::Game& game, SDL_Renderer* renderer);
    virtual ~TitleState() override = default;

    // ^State
    virtual void handle_input(SDL_Event const& event) override;
    virtual void update() override;
    virtual void render() override;

private:
    void init_resources();
    void init_animations();

    void raise_curtain();

private:
    BackgroundImage m_floor;
    BackgroundImage m_curtain;
    BackgroundImage m_title;
    BackgroundImage m_bg;
    GFX::SpriteSheet m_three_sheet;
    GFX::AnimationGroup m_three_animation;

    std::shared_ptr<Timer> m_curtain_timer { nullptr };
    int16_t m_title_drop_vertical_count { 0xD0 };
    uint16_t m_shake_counter { 32u };

    int m_three_x_position { 0 };
    int m_three_y_position { 0 };

    uint8_t m_bg_alpha { 0u };

    // State flags
    bool m_should_raise_curtain { false };
    bool m_should_drop_title { false };
    bool m_should_shake { false };
    bool m_should_fade_in { false };
    bool m_should_glow { false };
};

} // namespace States
