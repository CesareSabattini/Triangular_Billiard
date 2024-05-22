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

4. Compilare la soluzione:

    ```bash
    cmake --build .
    ```

5. Per avviare l'eseguibile dalla directory build:
   
    ```bash
    ./Triangular_Pool
    ```

6. Per eseguire il testing:

    ```bash
    ./tests
    ```
