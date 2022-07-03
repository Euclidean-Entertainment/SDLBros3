find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("../source/")
include_directories(SYSTEM "${SDL2_INCLUDE_DIRS}/..")
include_directories(SYSTEM "${SDL2_IMAGE_INCLUDE_DIRS}/..")

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

add_executable(file_test
    "./file/file_test.cpp"

    "../source/system/File.cpp"
    "../source/system/Log.cpp"
)
set_target_properties(file_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

add_executable(agf_test
    "./gfx/agf_test.cpp"

    "../source/gfx/Animation.cpp"
    "../source/gfx/AnimationGroup.cpp"
    "../source/system/File.cpp"
    "../source/system/Log.cpp"
)
set_target_properties(agf_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

add_executable(actscript_test
    "./engine/actscript_test.cpp"

    "../source/engine/actscript/Queue.cpp"
    "../source/system/File.cpp"
    "../source/system/Log.cpp"
)
set_target_properties(actscript_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

file(COPY ${CMAKE_SOURCE_DIR}/tests/test_data DESTINATION ${CMAKE_BINARY_DIR})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        target_link_libraries(actscript_test gcov)
        target_link_libraries(agf_test gcov)
        target_link_libraries(file_test gcov)
        setup_target_for_coverage_lcov(NAME actscript_test_coverage EXECUTABLE actscript_test coverage)
        setup_target_for_coverage_lcov(NAME agf_test_coverage EXECUTABLE agf_test coverage)
        setup_target_for_coverage_lcov(NAME file_test_coverage EXECUTABLE file_test coverage)
    endif()
endif()
