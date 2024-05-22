cmake_minimum_required(VERSION 3.10)
project(Triangular_Pool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/classes)
include_directories(${PROJECT_SOURCE_DIR}/libs)

add_compile_options(-Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast)

set(SANITIZE_FLAGS "-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZE_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SANITIZE_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SANITIZE_FLAGS}")


add_library(core_lib
    src/simulation/ball.cpp
    src/simulation/pool.cpp
    src/simulation/collision.cpp
    src/simulation/system.cpp
    src/graphics/mainWindow.cpp
    src/graphics/menu.cpp
    src/graphics/configSimulation.cpp
    src/graphics/simulationWindow.cpp
    src/graphics/analysisWindow.cpp
    src/graphics/errorPopup.cpp
    src/graphics/components/textInput/textInput.cpp
    src/graphics/components/legend/legend.cpp
    src/graphics/components/legend/legendItem.cpp
    src/graphics/components/button/button.cpp
    src/analysis/parameters.hpp
    src/analysis/results.hpp
    src/analysis/analysis.hpp
    src/graphics/appStyle.cpp

)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} core_lib sfml-graphics sfml-window sfml-system)

enable_testing()

add_executable(tests
    tests/main_tests.cpp
    tests/analysis_tests.cpp
    tests/simulation_tests.cpp
    tests/graphics_tests.cpp
    tests/mock/mockSystem.cpp
)
target_link_libraries(tests core_lib) 
add_test(NAME Triangular_Pool_Testing COMMAND tests)
