/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <engine/Game.h>
#include <engine/State.h>
#include <engine/Timer.h>
#include <gfx/BackgroundImage.h>
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

    std::shared_ptr<Timer> m_curtain_timer { nullptr };

    // State flags
    bool m_should_raise_curtain { false };
};

} // namespace States
