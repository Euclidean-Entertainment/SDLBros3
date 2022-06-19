cmake_minimum_required(VERSION 3.10.0)

project(sdlbros CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    list(APPEND CXX_FLAGS
        "-g3"
        "-ggdb"
        "-pedantic"
        "-Wall"
        "-Wextra"
        "-Werror"
        "-Wsign-compare"
        "-Wold-style-cast"
        "-Wdeprecated"
        "-Wsign-conversion"
        "-Wconversion"
        "-Wnon-virtual-dtor"
        "-Wundef"
        "-Wfloat-equal"
        "-Wunreachable-code"
        "-Wswitch-enum"
    )
    string(REPLACE ";" " " CXX_FLAGS "${CXX_FLAGS}")
    set(CXX_FLAGS "${CXX_FLAGS}" CACHE INTERNAL "Additional compiler flags to use.")

    option(CXX_FORCE_COLOR "Force compiler to use colored output (if available)." ON)
    if(CXX_FORCE_COLOR)
        set(COLOR_DIAG_FLAGS "fcolor-diagnostics" "fdiagnostics-color=always")
        foreach(COLOR_DIAG_FLAG ${COLOR_DIAG_FLAGS})
            set(TEST_NAME "HAVE_${COLOR_DIAG_FLAG}_FLAG")
            if(${TEST_NAME})
                message(STATUS "Forcing colored compiler output")
                set(CXX_FLAGS "${CXX_FLAGS} -${COLOR_DIAG_FLAG}")
            endif()
        endforeach()
    endif()

    set(BUILD_EXTRA_WARNINGS "Some" CACHE STRING "How many extra warnings to enable.")
    set_property(CACHE BUILD_EXTRA_WARNINGS PROPERTY STRINGS "None" "Some" "Many")

    # Some warnings that are of absolutely no interest
    set(WARN_NOT_FLAGS "c++98-compat" "c++98-compat-pedantic" "exit-time-destructors" "ignored-qualifiers" CACHE STRING "Warning-flags to disable.")
    if(NOT ${BUILD_EXTRA_WARNINGS} STREQUAL "Many")
        # These warnings often produce much uninteresting output
        list(APPEND WARN_NOT_FLAGS "padded")
    endif()

    if(NOT ${BUILD_EXTRA_WARNINGS} STREQUAL "None")
        set(WARN_EVERYTHING_FLAG "Weverything" CACHE STRING "The flag that enables all warnings.")
        if(HAVE_${WARN_EVERYTHING_FLAG}_FLAG)
            set(CXX_FLAGS "${CXX_FLAGS} -${WARN_EVERYTHING_FLAG}")
        endif()
    endif()

    foreach(WARN_FLAG ${WARN_NOT_FLAGS})
        string(REPLACE "+" "x" TEST_NAME "HAVE_W${WARN_FLAG}_FLAG")
        if(${TEST_NAME})
            message(STATUS "Disabling -W${WARN_FLAG}")
            set(CXX_FLAGS "${CXX_FLAGS} -Wno-${WARN_FLAG}")
        endif()
    endforeach()
elseif(MSVC)
    set(CXX_FLAGS "/W4")
endif()

set(CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_subdirectory(source)


