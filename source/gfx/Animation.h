/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <SDL2/SDL.h>
#include <vector>

namespace GFX {

class Animation
{
public:
    struct Frame
    {
        explicit Frame(int x, int y, int w, int h)
        : sheet_rect({ x, y, w, h }) {}
        SDL_Rect sheet_rect {};
    };

public:
    Animation() = default;
    Animation(uint32_t frames_per_tick);

    void set_ticks_per_frame(uint32_t ticks_per_frame) { m_ticks_per_frame = ticks_per_frame; }
    void add_frame(Frame const& frame);
    void add_frame(int x, int y, int w, int h);

    Frame const& frame(size_t frame) const;
    Frame const& next_frame() const;

    uint32_t ticks_per_frame() const { return m_ticks_per_frame; }

private:
    uint32_t m_ticks_per_frame { 0u };
    uint32_t m_frame_count { 0u };
    uint32_t m_current_frame { 0u };
    std::vector<Frame> m_frames;
};

} // namespace GFX
