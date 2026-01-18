set(target_name MachineLearningTrainer)

set(${target_name}_src      Environment.cpp
                            PythonBind.cpp)

find_package(pybind11 REQUIRED)

add_executable(${target_name} main.cpp ${${target_name}_src})

target_include_directories(${target_name}   PRIVATE     ${PYBIND11_INCLUDE_DIR})
target_link_libraries(${target_name}    PRIVATE     pybind11::embed Game Gameplay)
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
