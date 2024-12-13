# asteroidee
# Asteroid Game

¡Bienvenido al proyecto **Asteroid Game**! Este archivo README sirve como un manual completo
 para jugar, entender el código fuente, y contribuir al desarrollo de este proyecto.

---

## Tabla de Contenidos
1. [Descripción del Juego](#descripción-del-juego)
2. [Controles del Juego](#controles-del-juego)
3. [Instalación y Ejecución](#instalación-y-ejecución)
4. [Estructura del Código](#estructura-del-código)
5. [Diagrama UML](#diagrama-uml)
6. [Imágenes y Capturas](#imágenes-y-capturas)
7. [Contribuciones](#contribuciones)
8. [Licencia](#licencia)

---

## Descripción del Juego
Asteroid Game es un juego donde el jugador debe esquivar meteoritos y lograr la mayor puntuación posible.
El juego está desarrollado utilizando **SFML (Simple and Fast Multimedia Library)**, y se basa en la interacción gráfica, música y manejo de eventos en tiempo real.

### Objetivo del Juego
- Controla a tu nave para evitar colisiones con meteoritos y evitar salirte de los limites o sera tu destruccion total.
- Esquiva la mayor cantidad de meteoros que puedas
- Sobrevive el mayor tiempo posible.

---


## Controles del Juego
________________________________________
| Tecla      | Acción                   |
|------------|--------------------------|
|   ` ↑`     | Mover hacia arriba       |
|   ` ↓`     | Mover hacia abajo        |
|   ` ←`     | Mover hacia la izquierda |
|   ` →`     | Mover hacia la derecha   |
|____________|__________________________|

---

### Guia Para el Juego
Una vez ejecutado el codigo, lo que se tiene que hacer es presionar el texto **JUGAR** y automaticamente te enviara al espacio con tu nave listo para esquivar meteritos y evitar salirte del limite o el agujero negro te atrapara, al momento de jugar en la esquina superior izquierda se te mostrara la cantidad de meteoritos que has esquivado una vez tu nave colisione (limite o meteoro) habras perdido, si deseas volver a jugar da click donde dice **click aqui para regresar al inicio** en el inicio debes repetir los mismos pasos, si deseas salir cierra la ventana edl ejecutable


---


### Elementos del Juego
Meteoros: evita chocar con ellos o haran que tu nave sea destruida
Limites: evita el tu nave toque algun limite o seras atrapdo por un aguero negro.



---
## Instalación y Ejecución

### Requisitos Previos
- **C++ Compiler** compatible con C++17.
- **SFML** (Simple and Fast Multimedia Library) instalada.

### Instalación
1. Clona este repositorio:
    ```bash
    git clone https://github.com/tuusuario/asteroid-game.git
    cd asteroid-game
    ```
2. intalar las Programas necesarios
    Visual estudio code
    Descargar e instalar vscode en el siguiente Enlace.

    MSYS2 (Windows)
    Instalar Msys2 usando el siguiente Enlace.

    No modificar ningua opcion al momento de intalacion o podrian variar las configuraciones.

    Una vez instalado es necesario agregar los siguientes directorios al path de windows y reiniciar.

    C:\msys64\mingw64\bin

    C:\msys64\usr\bin

    Librerias utilizadas (Msys2)
    Ejecutar los siguientes comandos en la terminal de msys2 para instalar las dependencias necesarias

    DevTools
    Compiladores y herramientas necesarias para el desarrollo.

    https://code.visualstudio.com/docs/cpp/config-mingw

    pacman -S --needed base-devel mingw-w64-x86_64-toolchain

    SFML
    https://packages.msys2.org/package/mingw-w64-x86_64-sfml

    pacman -S mingw-w64-x86_64-sfml

3. Compila el proyecto:
    ```bash
    g++ -o AsteroidGame main.cpp -lsfml-graphics -lsfml-window -lsfml-system
    ```
4. Ejecuta el juego:
    make runAsteroidee
    ```

---

## Estructura del Código

El proyecto está organizado en las siguientes clases:

### Clases Principales
- **Asteroid**: Clase principal que maneja el flujo del juego.
- **Texto**: Administra los textos renderizados en pantalla.
- **Musica**: Controla la reproducción de música en el juego.
- **Personaje**: Representa al jugador.
- **Meteoro**: Define los meteoritos que actúan como obstáculos.
- **Fondo**: Representa el fondo del juego.

### Archivos del Proyecto
```plaintext
.
├── src/
│   ├── Asteroid.cpp       # Implementación de la clase principal
│   ├── Texto.cpp          # Manejo de textos
│   ├── Musica.cpp         # Reproducción de música
│   ├── Personaje.cpp      # Control del personaje
│   ├── Meteoro.cpp        # Obstáculos (meteoritos)
│   └── Fondo.cpp          # Renderizado del fondo
├── include/
│   ├── Asteroid.h
│   ├── Texto.h
│   ├── Musica.h
│   ├── Personaje.h
│   ├── Meteoro.h
│   └── Fondo.h
└── README.md
