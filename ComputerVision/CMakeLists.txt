set(target_name ComputerVision)
set(${target_name}_src      Observer.cpp
                            CVSession.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(${target_name}   STATIC  ${${target_name}_src})

target_link_libraries(${target_name}    PRIVATE     Game
                                                    Graphics
                                                    AIDrivenFlappyBird
                                        PUBLIC      ${OpenCV_LIBS})

target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
