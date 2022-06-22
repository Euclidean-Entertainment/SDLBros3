
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

Timer* State::create_timer(std::function<void()> callback, unsigned int ticks, TimerType type)
{
  auto timer = std::make_unique<Timer>(callback, ticks, type);
  m_timers.push_back(std::move(timer));
  return m_timers.back().get();
}

Timer* State::create_timer(unsigned int ticks, TimerType type)
{
  return create_timer(nullptr, ticks, type);
}


};
