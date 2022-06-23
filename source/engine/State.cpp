
/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>, Zac Brannelly <zac.brannelly@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <engine/Game.h>
#include <engine/State.h>
#include <engine/Timer.h>

namespace Engine
{


State::State(Game& game, SDL_Renderer* renderer)
    : m_game(game),
      m_renderer(renderer),
      m_font_renderer(m_game.resource_loader())
{

}

void State::tick_timers()
{
  for (auto& timer : m_timers)
  {
    timer->tick();
  }
}

std::shared_ptr<Timer> State::create_timer(std::function<void()> callback, uint32_t ticks, TimerType type)
{
  auto timer = std::make_shared<Timer>(callback, ticks, type);
  m_timers.push_back(std::move(timer));
  return m_timers.back();
}

std::shared_ptr<Timer> State::create_timer(uint32_t ticks, TimerType type)
{
  return create_timer(nullptr, ticks, type);
}


};
