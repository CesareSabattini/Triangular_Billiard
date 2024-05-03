# Specifica che vogliamo compilare `main.cpp` in un eseguibile.
add_executable(${PROJECT_NAME} main.cpp)

# Include la directory delle classi per trovare gli header files durante la compilazione.
target_include_directories(${PROJECT_NAME} PRIVATE classes)

# Aggiungi i file sorgente delle classi al progetto
target_sources(${PROJECT_NAME} PRIVATE
    classes/Ball.cpp
    classes/Pool.cpp
    classes/Collision.cpp
    classes/System.cpp
)
