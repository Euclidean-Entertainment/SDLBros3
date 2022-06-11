/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#define MAKE_NONCOPYABLE(klass) \
private: \
    klass(klass const&) = delete; \
    klass& operator=(klass const&) = delete;\

#define MAKE_NONMOVABLE(klass) \
private: \
    klass(klass&&) = delete; \
    klass& operator=(klass&&) = delete;\

