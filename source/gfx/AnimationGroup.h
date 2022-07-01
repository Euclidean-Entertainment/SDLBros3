/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <gfx/Animation.h>
#include <string>
#include <vector>

namespace GFX {

class AnimationGroup final
{
    static constexpr char const* ANIMATION_GROUP_FILE_EXT = ".agf";
    static constexpr char const* ANIMATION_GROUP_HEADER_MAGIC = "SMB3ANM\0";
    static constexpr char const* ANIMATION_GROUP_ANIMATION_MAGIC = "ADH\0";

    struct [[gnu::packed]] agf_file_header
    {
        char magic[8];
        uint16_t animation_count;
        uint8_t version_major;
        uint8_t version_minor;
        uint8_t reserved[4];
    };

    struct [[gnu::packed]] agf_animation_header
    {
        char magic[4];
        uint8_t number_of_frames;
        uint8_t frame_length;
    };

    struct [[gnu::packed]] agf_animation_data
    {
        uint16_t sheet_x;
        uint16_t sheet_y;
        uint8_t sprite_width;
        uint8_t sprite_height;
    };

public:
    AnimationGroup() = default;
    ~AnimationGroup() = default;

    bool load(std::string const& path);

    Animation const& animation(std::vector<Animation>::size_type index);
    std::vector<Animation>::size_type animation_count() const { return m_animations.size(); }

private:
    std::vector<Animation> m_animations;
};

}; // namespace GFX
