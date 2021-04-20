set(TARGET race00)

set(SOURCES main.cpp src/snake.cpp
            src/StateMachines/StateManager.cpp
            src/StateMachines/MenuState.cpp
            src/StateMachines/GameState.cpp
            src/StateMachines/ScoreboardState.cpp
            src/StateMachines/DeathState.cpp)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wpedantic -g")

include_directories(src)
include_directories("../Framework/inc")

add_executable(${TARGET} ${SOURCES})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS}/..
                    ${SDL2_image_INCLUDE_DIRS}
                    ${SDL2_ttf_INCLUDE_DIRS})

target_link_libraries(${TARGET} FrameworkRelease)

target_link_libraries(${TARGET} SDL2::Main SDL2::Image SDL2::TTF) # X11)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)