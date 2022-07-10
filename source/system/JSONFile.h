/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <nlohmann/json.hpp>

namespace System {

class JSONFile final
{
public:
    JSONFile() = default;
    JSONFile(std::string const& path);

    nlohmann::json const& json() const { return m_json; }
    bool loaded() const { return m_loaded; }

private:
    bool load(std::string const& path);

private:
    nlohmann::json m_json;
    bool m_loaded { false };
};

} // namespace System

using System::JSONFile;
