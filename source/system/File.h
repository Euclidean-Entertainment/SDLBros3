/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <NonCopy.h>
#include <cstdint>
#include <iostream> // Required for `std::ios_base`
#include <string>
#include <vector>

namespace System {

class File final
{
    MAKE_NONCOPYABLE(File)
    MAKE_NONMOVABLE(File)

    using size_type = std::vector<uint8_t>::size_type;

public:
    File() = default;
    explicit File(std::string const& filepath);

    ~File() = default;

    void rewind() { m_fpos = 0; }
    void seek(long position, std::ios_base::seekdir origin);

    long read(void* destination, long length);
    long file_size() const { return m_file_size; }
    bool open(std::string const& filepath);
    bool open(void) { return m_open; }

private:
    long m_fpos { 0 };
    long m_file_size { 0 };
    std::string m_path;
    bool m_open { false };
    std::vector<uint8_t> m_data;
};

}; // namespace System

using DiskFile = System::File;
using System::File;
