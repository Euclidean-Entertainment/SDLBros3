
#include <engine/Game.h>
#include <engine/State.h>

namespace Engine
{


State::State(Game& game, SDL_Renderer* renderer)
    : m_game(game),
      m_renderer(renderer),
      m_font_renderer(m_game.resource_loader())
{

}


};
