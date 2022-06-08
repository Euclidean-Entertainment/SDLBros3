find_package(SDL2 REQUIRED)

include_directories("./")
include_directories(SYSTEM "../third_party/debugbreak")
include_directories(SYSTEM "${SDL2_INCLUDE_DIRS}")

add_executable("${CMAKE_PROJECT_NAME}"
    "main.cpp"

    "engine/Game.cpp"

    "system/Log.cpp"
    "system/Renderer.cpp"
    "system/Window.cpp"
)

target_link_libraries("${CMAKE_PROJECT_NAME}"
    PRIVATE "${SDL2_LIBRARIES}"
)
