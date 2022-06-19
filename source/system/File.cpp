/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <algorithm>
#include <system/File.h>
#include <system/Log.h>
#include <fstream>
#include <Assertions.h>
#include <cstring>

namespace System {

void File::seek(long position, std::ios_base::seekdir origin)
{
    if (origin == std::ios_base::beg)
    {
        m_fpos = position;
    }
    else if (origin == std::ios_base::cur)
    {
        m_fpos += position;
    }
    else if (origin == std::ios_base::end)
    {
        // Do nothing for now...
    }

    if (m_fpos > m_file_size)
    {
        log(LogLevel::WARN, "Attempted to seek past file size!");
        m_fpos = m_file_size;
    }
}

bool File::open(std::string const& filepath)
{
    if (m_open == true)
    {
        log(LogLevel::INFO, "File %s is already open!", filepath.c_str());
        return false;
    }

    std::ifstream file_stream;
    file_stream.open(filepath.c_str(), std::ios_base::binary | std::ios_base::ate);
    if (!file_stream.is_open())
    {
        log(LogLevel::WARN, "Failed to open file %s", filepath.c_str());
        return false;
    }

    m_file_size = file_stream.tellg();
    file_stream.seekg(0, std::ios_base::beg);                   // Seek back to beginning of the file
    m_data.reserve(static_cast<unsigned long>(m_file_size));    // FIXME: Why the fuck does this require a cast when `m_file_size` is std::vector<T>::size_type??
    (void)file_stream.read(reinterpret_cast<char*>(&m_data.data()[0]), m_file_size);
    m_open = true;

    return true;
}

long File::read(void* destination, long length)
{
    if (length > m_file_size)
    {
        log(LogLevel::WARN, "Attempted to read too many bytes from %s (m_fpos: %ld m_file_size: %ld length: %ld)", m_path.c_str(), m_fpos, m_file_size, length);
    }

    ASSERT(m_fpos <= m_file_size);

    auto number_of_bytes_to_read = std::min(length, m_file_size - m_fpos);
    memcpy(destination, &m_data.data()[m_fpos], static_cast<size_t>(number_of_bytes_to_read));
    m_fpos += number_of_bytes_to_read;

    return number_of_bytes_to_read;
}

};
