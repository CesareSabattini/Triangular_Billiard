cmake_minimum_required(VERSION 3.10)
project(Triangular_Pool)

set(CMAKE_CXX_STANDARD 17)
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
    src/graphics/SimulationWindow.cpp
)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)