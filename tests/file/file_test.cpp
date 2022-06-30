/*
 * Copyright (c) 2022, Jesse Buhagiar <jooster669@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <system/File.h>

#define EXPECTED_BUFFER_SIZE 16

TEST_CASE("Test File open")
{
    DiskFile file;

    CHECK(file.open("./test_data/file.txt") == true);
}

TEST_CASE("Test File read")
{
    static const char* expected_string = "0123456789ABCDEF";
    static char str[EXPECTED_BUFFER_SIZE];
    DiskFile file;

    (void)file.open("./test_data/file.txt");
    CHECK(file.read(&str[0], EXPECTED_BUFFER_SIZE) == EXPECTED_BUFFER_SIZE);
    CHECK(memcmp(expected_string, str, EXPECTED_BUFFER_SIZE) == 0);
}

TEST_CASE("Test File size")
{
    DiskFile file;

    (void)file.open("./test_data/file.txt");

    // We subtract one to take in the ending newline at the end of the file
    CHECK(file.file_size()-1 == EXPECTED_BUFFER_SIZE);
}
