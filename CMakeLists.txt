cmake_minimum_required(VERSION 3.10)
project(Triangular_Pool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/classes)
include_directories(${PROJECT_SOURCE_DIR}/libs)

add_compile_options(-Wall -Wextra -pedantic)

add_library(core_lib
    src/simulation/Ball.cpp
    src/simulation/Pool.cpp
    src/simulation/Collision.cpp
    src/simulation/System.cpp
    src/graphics/MainWindow.cpp
    src/graphics/Menu.cpp
    src/graphics/ConfigSimulation.cpp
    src/graphics/SimulationWindow.cpp
    src/graphics/AnalysisWindow.cpp
    src/graphics/components/textInput/TextInput.cpp
    src/graphics/components/legend/Legend.cpp
    src/graphics/components/legend/LegendItem.cpp
    src/graphics/components/button/Button.cpp
    src/analysis/Results.hpp
    src/analysis/Analysis.hpp
    src/graphics/AppStyle.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} core_lib sfml-graphics sfml-window sfml-system)

enable_testing()

add_executable(tests
    tests/main_tests.cpp
    tests/analysis_tests.cpp
    tests/simulation_tests.cpp
    tests/graphics_tests.cpp
)
target_link_libraries(tests core_lib) 
add_test(NAME Triangular_Pool_Testing COMMAND tests)
