set(target_name Game)

set(${target_name}_src Entity.cpp)

set(${target_name}_hpp Entity.hpp)

add_library(${target_name}  STATIC)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR     PARENT_PATH     GAME_PARENT_DIR)

target_sources(${target_name}
    PRIVATE
        ${${target_name}_src}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${GAME_PARENT_DIR}
        FILES ${${target_name}_hpp}
)

target_compile_options(${target_name}   PRIVATE     ${FLAGS}    ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)