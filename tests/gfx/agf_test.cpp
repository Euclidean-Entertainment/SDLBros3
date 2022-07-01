/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <gfx/AnimationGroup.h>

static constexpr size_t EXPECTED_NUMBER_OF_ANIMATIONS   = 3;
static constexpr int EXPECTED_FRAME_WIDTH               = 32;
static constexpr int EXPECTED_FRAME_HEIGHT              = 32;

TEST_CASE("Test AGF load")
{
    GFX::AnimationGroup test_anim_group;

    CHECK(test_anim_group.load("./test_data/test.agf") == true);
    CHECK(test_anim_group.animation_count() == EXPECTED_NUMBER_OF_ANIMATIONS);
}

TEST_CASE("Test AGF animation check")
{
    GFX::AnimationGroup test_anim_group;

    CHECK(test_anim_group.load("./test_data/test.agf") == true);

    auto animation = test_anim_group.animation(0);
    for (auto i = 0u; i < animation.frame_count(); i++)
    {
        auto frame = animation.frame(i);
        CHECK(frame.sheet_rect.w == EXPECTED_FRAME_WIDTH);
        CHECK(frame.sheet_rect.h == EXPECTED_FRAME_HEIGHT);

        CHECK(frame.sheet_rect.x == i * (EXPECTED_FRAME_WIDTH * 2u));
        CHECK(frame.sheet_rect.y == 0u);
    }
}
