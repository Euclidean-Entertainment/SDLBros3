/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <Assertions.h>
#include <gfx/Animation.h>

namespace GFX {

Animation::Animation(uint32_t ticks_per_frame)
: m_ticks_per_frame(ticks_per_frame)
{
}

Animation::Frame const& Animation::next_frame() const
{
    ASSERT((m_current_frame % frame_count()) < m_frames.size());
    return m_frames.at(m_current_frame % frame_count());
}

void Animation::add_frame(Frame const& frame)
{
    m_frames.push_back(frame);
}

void Animation::add_frame(int x, int y, int w, int h)
{
    m_frames.push_back(Frame(x, y, w, h));
}

Animation::Frame const& Animation::frame(size_t frame) const
{
    ASSERT(frame < m_frames.size());
    return m_frames.at(frame);
}

Animation::Frame const& Animation::current_frame() const
{
    return m_frames.at(m_current_frame);
}

void Animation::tick()
{
    if (m_current_tick < m_ticks_per_frame)
    {
        m_current_tick++;
    }
    else
    {
        m_current_frame++;
        m_current_tick = 0u;
        if (m_current_frame >= frame_count())
            m_current_frame = 0u;
    }
}

} // namespace GFX
