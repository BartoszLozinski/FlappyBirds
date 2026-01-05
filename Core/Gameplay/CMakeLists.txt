set(target_name Gameplay)

set(${target_name}_src      CoreGameplay.cpp
                            Gameplay.cpp)

add_library(${target_name}  STATIC  ${${target_name}_src})

target_link_libraries(${target_name}    PUBLIC     Game Graphics)
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)

