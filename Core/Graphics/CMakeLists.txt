set(target_name Graphics)

set(${target_name}_src  Renderable.cpp
                        ShapeRenderable.cpp
                        Circle.cpp
                        KeyboardController.cpp)

set(${target_name}_hpp  Renderable.hpp
                        ShapeRenderable.hpp
                        Circle.hpp
                        KeyboardController.hpp)

set(SFML_LIB    sfml-graphics
                sfml-window
                sfml-system)

find_package(SFML 2.6 COMPONENTS    graphics
                                    window
                                    system  REQUIRED)

add_library(${target_name}  STATIC  ${${target_name}_src})

target_link_libraries(${target_name}    PRIVATE     Game ${SFML_LIB})
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)

