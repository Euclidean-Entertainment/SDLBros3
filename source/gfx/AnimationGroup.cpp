/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <Assertions.h>
#include <gfx/AnimationGroup.h>
#include <system/File.h>
#include <system/Log.h>

namespace GFX {

static constexpr bool AGF_DEBUG = true;
static constexpr bool AGF_DEBUG_VERBOSE = true;

bool AnimationGroup::load(std::string const& path)
{
    DiskFile agf_file;

    if (agf_file.open(path) == false)
    {
        log(LogLevel::WARN, "Failed to open AGF File %s", path.c_str());
        return false;
    }

    // File is open, let's read in the header first
    agf_file_header file_header;
    auto bytes_read = agf_file.read(&file_header, sizeof(agf_file_header));
    if (bytes_read != sizeof(agf_file_header))
    {
        log(LogLevel::WARN, "Failed to read AGF File Header (is the file corrupt?)!");
        return false;
    }

    if (strncmp(ANIMATION_GROUP_HEADER_MAGIC, file_header.magic, sizeof(agf_file_header::magic)) != 0)
    {
        log(LogLevel::CRIT, "Invalid header magic for %s! Got %s!", path.c_str(), file_header.magic);
        return false;
    }

    log_if(AGF_DEBUG, LogLevel::INFO, "====== Animation Group File Header ======");
    log_if(AGF_DEBUG, LogLevel::INFO, "AGF Magic: \t%s", file_header.magic);
    log_if(AGF_DEBUG, LogLevel::INFO, "AGF Anim Count: \t%u", file_header.animation_count);
    log_if(AGF_DEBUG, LogLevel::INFO, "AGF Version: \t%u.%u", file_header.version_major, file_header.version_minor);

    m_animations.resize(file_header.animation_count);
    for (auto& animation : m_animations)
    {
        agf_animation_header animation_header;

        bytes_read = agf_file.read(&animation_header, sizeof(agf_animation_header));
        if (bytes_read != sizeof(agf_animation_header))
        {
            log(LogLevel::WARN, "Failed to read animation group header!");
            return false;
        }

        if (strncmp(ANIMATION_GROUP_ANIMATION_MAGIC, animation_header.magic, sizeof(agf_animation_header::magic)) != 0)
        {
            log(LogLevel::CRIT, "Invalid animation header! Got %s!", animation_header.magic);
            return false;
        }

        log_if(AGF_DEBUG, LogLevel::INFO, "====== Animation Header ======");
        log_if(AGF_DEBUG, LogLevel::INFO, "Header Magic: \t%s", animation_header.magic);
        log_if(AGF_DEBUG, LogLevel::INFO, "Num Frames: \t%u", animation_header.number_of_frames);
        log_if(AGF_DEBUG, LogLevel::INFO, "Frame length: \t%u (ticks)", animation_header.frame_length);

        // Setup animation data
        animation.set_ticks_per_frame(animation_header.frame_length);
        for (auto frame = 0u; frame < animation_header.number_of_frames; frame++)
        {
            agf_animation_data animation_data;

            bytes_read = agf_file.read(&animation_data, sizeof(agf_animation_data));
            if (bytes_read != sizeof(agf_animation_data))
            {
                log(LogLevel::WARN, "Failed to read animation data!");
                return false;
            }

            log_if(AGF_DEBUG_VERBOSE, LogLevel::INFO, "====== Frame %d ======", frame);
            log_if(AGF_DEBUG_VERBOSE, LogLevel::INFO, "sheet_x: \t%u", animation_data.sheet_x);
            log_if(AGF_DEBUG_VERBOSE, LogLevel::INFO, "sheet_y: \t%u", animation_data.sheet_y);
            log_if(AGF_DEBUG_VERBOSE, LogLevel::INFO, "sprite_w: \t%u", animation_data.sprite_height);
            log_if(AGF_DEBUG_VERBOSE, LogLevel::INFO, "sprite_h: \t%u", animation_data.sprite_width);

            animation.add_frame(animation_data.sheet_x, animation_data.sheet_y, animation_data.sprite_width, animation_data.sprite_width);
        }
    }

    return true;
}

Animation const& AnimationGroup::animation(std::vector<Animation>::size_type index)
{
    ASSERT(index < m_animations.size());

    return m_animations.at(index);
}

}; // namespace GFX
