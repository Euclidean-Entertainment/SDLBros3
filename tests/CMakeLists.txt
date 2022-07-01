find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("../source/")
include_directories(SYSTEM "${SDL2_INCLUDE_DIRS}/..")
include_directories(SYSTEM "${SDL2_IMAGE_INCLUDE_DIRS}/..")

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

add_custom_command(TARGET "file_test" PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tests/test_data ${CMAKE_BINARY_DIR}/tests/test_data)
