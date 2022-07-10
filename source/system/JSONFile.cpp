/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <fstream>
#include <system/JSONFile.h>
#include <system/Log.h>

namespace System {

JSONFile::JSONFile(std::string const& path)
: m_json(),
  m_loaded(false)
{
    auto load_rc = load(path);
    if (load_rc == false)
        log(LogLevel::WARN, "Failed to load JSON file %s", path.c_str());
}

bool JSONFile::load(std::string const& path)
{
    std::ifstream fstream(path);

    if (fstream.is_open() == false)
        return false;

    fstream >> m_json;
    m_loaded = true;

    return true;
}

} // namespace System
