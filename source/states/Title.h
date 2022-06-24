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
public:
    TitleState(Engine::Game& game, SDL_Renderer* renderer);
    virtual ~TitleState() override {}

    // ^State
    virtual void handle_input(SDL_Event const& event) override;
    virtual void update() override;
    virtual void render() override;

private:
    void init_resources();
    void init_animations();

private:
    BackgroundImage m_floor;
    BackgroundImage m_curtain;

    std::shared_ptr<Timer> m_curtain_timer { nullptr };
};

}; // namespace States
