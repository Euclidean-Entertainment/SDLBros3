find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories("./")
include_directories(SYSTEM "${SDL2_INCLUDE_DIRS}/..")
include_directories(SYSTEM "${SDL2_IMAGE_INCLUDE_DIRS}/..")

add_executable("${CMAKE_PROJECT_NAME}"
    "Assertions.h"
    "NonCopy.h"
    "main.cpp"
    "engine/actscript/Queue.cpp"
    "engine/Game.h"
    "engine/Game.cpp"
    "engine/ResourceLoader.h"
    "engine/ResourceLoader.cpp"
    "engine/State.h"
    "engine/State.cpp"
    "engine/Timer.h"
    "engine/Timer.cpp"
    "entity/Entity.cpp"
    "gfx/Animation.h"
    "gfx/Animation.cpp"
    "gfx/AnimationGroup.h"
    "gfx/AnimationGroup.cpp"
    "gfx/BackgroundImage.h"
    "gfx/BackgroundImage.cpp"
    "gfx/FontRenderer.h"
    "gfx/FontRenderer.cpp"
    "gfx/SpriteSheet.h"
    "gfx/SpriteSheet.cpp"
    "gfx/Texture.h"
    "gfx/Texture.cpp"
    "states/Title.h"
    "states/Title.cpp"
    "system/File.h"
    "system/File.cpp"
    "system/JSONFile.cpp"
    "system/Log.h"
    "system/Log.cpp"
    "system/Renderer.h"
    "system/Renderer.cpp"
    "system/Window.h"
    "system/Window.cpp"
    "math/Vec2.h"
)

target_link_libraries("${CMAKE_PROJECT_NAME}"
    PRIVATE "${SDL2_LIBRARIES}"
    PRIVATE "${SDL2_IMAGE_LIBRARIES}"
    PRIVATE nlohmann_json::nlohmann_json
)

# Copy data directory to build directory
add_custom_command(TARGET "${CMAKE_PROJECT_NAME}" PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/data)
