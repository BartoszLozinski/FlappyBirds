set(target_name UI)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(${target_name}_src     UI.cpp)

add_library(${target_name}  STATIC  ${${target_name}_src})

target_link_libraries(${target_name}    PUBLIC      Qt6::Widgets Qt6::Core Qt6::Gui)
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
