set(TARGET race00)

set(SOURCES main.cpp src/snake.cpp
            src/StateMachines/StateManager.cpp
            src/StateMachines/MenuState.cpp
            src/StateMachines/GameState.cpp
            src/StateMachines/ScoreboardState.cpp)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wpedantic")

include_directories(src)
include_directories("../Framework/inc")

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} FrameworkRelease)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)