cmake_minimum_required(VERSION 3.28)
project(FlappyBirds)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)
set(FLAGS   -Wall
            -Werror
            -Wpedantic
            -Wextra)

set(OPTIMIZATION_LEVEL  -Og)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME}  main.cpp)

add_subdirectory(Core/Game)
add_subdirectory(Core/Graphics)
add_subdirectory(Core/DataProcessor)
add_subdirectory(Core/Gameplay)
add_subdirectory(Core/Tests)
add_subdirectory(UI)
add_subdirectory(MachineLearning)

target_link_libraries(${PROJECT_NAME}   PRIVATE     Game
                                                    Graphics
                                                    Gameplay
                                                    UI)

target_compile_options(${PROJECT_NAME}  PRIVATE     ${FLAGS}    ${OPTIMIZATION_LEVEL})
set_target_properties(${PROJECT_NAME}   PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
