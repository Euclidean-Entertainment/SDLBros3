/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */


#include <cstdio>
#include <engine/Game.h>

int main(void)
{
    auto game = Engine::Game::try_create();
    if (game)
    {
        game->start();
    }

    return 0;
}
