/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <cmath>
#include <cstdint>
#include <utility>

namespace Math {

template<typename T>
class Vec2
{
public:
    Vec2() = default;
    Vec2(T x, T y)
    : m_x(x), m_y(y) {}
    Vec2(Vec2 const& rhs)
    : m_x(rhs.m_x), m_y(rhs.m_y) {}
    Vec2(Vec2&& rhs)
    : m_x(std::exchange(rhs.m_x, 0)), m_y(std::exchange(rhs.m_y, 0)) {}

    Vec2 operator=(Vec2 const& rhs)
    {
        Vec2 new_vec;

        new_vec.m_x = rhs.m_x;
        new_vec.m_y = rhs.m_y;

        return new_vec;
    }

    Vec2& operator=(Vec2&& rhs)
    {
        m_x = std::exchange(rhs.m_x, 0);
        m_y = std::exchange(rhs.m_y, 0);

        return *this;
    }

    [[nodiscard]] constexpr T x() const { return m_x; }
    [[nodiscard]] constexpr T y() const { return m_y; }

    void set_x(T value) { m_x = value; }
    void set_y(T value) { m_y = value; }

    constexpr Vec2& operator+=(Vec2 const& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;

        return *this;
    }

    constexpr Vec2& operator-=(Vec2 const& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;

        return *this;
    }

    constexpr Vec2& operator*=(Vec2 const& rhs)
    {
        m_x *= rhs.m_x;
        m_y *= rhs.m_y;

        return *this;
    }

    constexpr Vec2& operator/=(Vec2 const& rhs)
    {
        m_x /= rhs.m_x;
        m_y /= rhs.m_y;

        return *this;
    }

    constexpr Vec2 operator+(Vec2 const& rhs) const
    {
        Vec2 new_vec;

        new_vec.m_x += rhs.m_x;
        new_vec.m_y += rhs.m_y;

        return new_vec;
    }

    constexpr Vec2 operator-(Vec2 const& rhs) const
    {
        Vec2 new_vec;

        new_vec.m_x -= rhs.m_x;
        new_vec.m_y -= rhs.m_y;

        return new_vec;
    }

    constexpr Vec2 operator*(Vec2 const& rhs) const
    {
        Vec2 new_vec;

        new_vec.m_x *= rhs.m_x;
        new_vec.m_y *= rhs.m_y;

        return new_vec;
    }

    constexpr Vec2 operator/(Vec2 const& rhs) const
    {
        Vec2 new_vec;

        new_vec.m_x /= rhs.m_x;
        new_vec.m_y /= rhs.m_y;

        return new_vec;
    }

    constexpr T length() const
    {
        return std::sqrt((m_x * m_x) + (m_y * m_y));
    }

    void normalize()
    {
        T const inverse_length = static_cast<T>(1.0f) / length();

        m_x *= inverse_length;
        m_y *= inverse_length;
    }

private:
    T m_x;
    T m_y;
};

} // namespace Math

using FloatVector2 = Math::Vec2<float>;
using IntVector2 = Math::Vec2<int32_t>;
