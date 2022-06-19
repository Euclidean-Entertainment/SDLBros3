find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("./")
include_directories(SYSTEM "../third_party/debugbreak")
include_directories(SYSTEM "${SDL2_INCLUDE_DIRS}/..")
include_directories(SYSTEM "${SDL2_IMAGE_INCLUDE_DIRS}/..")

add_executable("${CMAKE_PROJECT_NAME}"
    "main.cpp"
    "engine/Game.cpp"
    "engine/ResourceLoader.cpp"
    "engine/State.cpp"
    "gfx/Animation.cpp"
    "gfx/AnimationGroup.cpp"
    "gfx/BackgroundImage.cpp"
    "gfx/FontRenderer.cpp"
    "gfx/SpriteSheet.cpp"
    "gfx/Texture.cpp"
    "states/Title.cpp"
    "system/File.cpp"
    "system/Log.cpp"
    "system/Renderer.cpp"
    "system/Window.cpp"
)

target_link_libraries("${CMAKE_PROJECT_NAME}"
    PRIVATE "${SDL2_LIBRARIES}"
    PRIVATE "${SDL2_IMAGE_LIBRARIES}"
)

# Copy data directory to build directory
add_custom_command(TARGET "${CMAKE_PROJECT_NAME}" PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/data)
