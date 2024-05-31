# Triangular Billiard
Il programma simula il moto di un punto materiale all'interno di un biliardo triangolare, e computa la distribuzione delle ordinate e degli angoli di uscita su un numero programmabile di simulazioni.
Realizzato secondo lo standard ISO di C++20, l'applicazione fornisce una GUI basata sul framework SFML e fa ampio uso della Standard Library.
Per la compilazione della soluzione si utilizza CMake Build System.

## Installazione e Configurazione
Per la configurazione dell'applicazione su LinuxOS e WSL, si consigliano i seguenti passaggi:

1. Installare le dipendenze necessarie:

    ```bash
    sudo apt update
    sudo apt install build-essential cmake libsfml-dev
    ```

2. Creare una directory di build:

    ```bash
    mkdir build
    cd build
    ```

3. Configurare la soluzione con CMake:
   
    ```bash
    cmake ..
    ```

4. Per compilare l'eseguibile "Triangular_Pool" in modalità Debug con Address Sanitizer:

    ```bash
    cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
    cmake --build build/debug --target Triangular_Pool
    ```
5. Per compilare l'eseguibile "tests" in modalità Debug con Address Sanitizer::

    ```bash
    cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
    cmake --build build/debug --target tests
    ```

6.  Per compilare l'eseguibile "Triangular_Pool" in modalità Release:

    ```bash
    cmake -B build/release -DCMAKE_BUILD_TYPE=Release -DENABLE_SANITIZERS=OFF
    cmake --build build/release --target Triangular_Pool
    ```

    7.  Per compilare l'eseguibile "tests" in modalità Release:

    ```bash
    cmake -B build/release -DCMAKE_BUILD_TYPE=Release -DENABLE_SANITIZERS=OFF
    cmake --build build/release --target tests
    ```
  
8. Per avviare l'eseguibile dalla opportuna directory:
   
    ```bash
    ./Triangular_Pool
    ```

9. Per eseguire il testing dalla opportuna directory:

    ```bash
    ./tests
    ```
