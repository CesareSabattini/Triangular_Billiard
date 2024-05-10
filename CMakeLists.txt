cmake_minimum_required(VERSION 3.10)
project(Triangular_Pool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/src/classes)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/simulation/Ball.cpp
    src/simulation/Pool.cpp
    src/simulation/Collision.cpp
    src/simulation/System.cpp
    src/graphics/MainWindow.cpp
    src/graphics/Menu.cpp
    src/graphics/ConfigSimulation.cpp
    src/graphics/SimulationWindow.cpp
    src/graphics/AnalysisWindow.cpp
    src/graphics/components/TextInput.cpp
    src/graphics/components/Legend.cpp
    src/graphics/components/LegendItem.cpp
    src/analysis/Results.hpp
    src/analysis/Analysis.hpp



)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
