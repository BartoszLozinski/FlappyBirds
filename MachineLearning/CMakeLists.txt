set(target_name flappy_env)
set(target_name_ML  AIDrivenFlappyBird)
set(${target_name}_src      CoreLogicAdapter.cpp
                            Environment.cpp
                            BirdNeuralNetwork.cpp
                            MLController.cpp
                            AIDrivenSession.cpp)

find_package(pybind11 REQUIRED)
find_package(nlohmann_json REQUIRED)

pybind11_add_module(${target_name}  ${${target_name}_src} PythonBind.cpp)
target_link_libraries(${target_name}    PRIVATE     #pybind11::embed 
                                                    Game
                                                    Gameplay)


add_library(${target_name_ML}   STATIC  ${${target_name}_src})
target_link_libraries(${target_name_ML}    PRIVATE      Game
                                                        Gameplay
                                                        nlohmann_json::nlohmann_json)

target_compile_options(${target_name_ML}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name_ML}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)



target_include_directories(${target_name}   PRIVATE     ${PYBIND11_INCLUDE_DIR})
target_compile_options(${target_name}   PRIVATE     ${FLAGS} ${OPTIMIZATION_LEVEL})
set_target_properties(${target_name}    PROPERTIES  CXX_STANDARD 20     CXX_STANDARD_REQUIRED ON)
