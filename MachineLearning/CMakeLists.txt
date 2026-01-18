set(target_name MachineLearningTrainer)

set(${target_name}_src      Environment.cpp)

add_library(${target_name}  STATIC  ${${target_name}_src})

target_link_libraries(${target_name}    PRIVATE     Gameplay)
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
