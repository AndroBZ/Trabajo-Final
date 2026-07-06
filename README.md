# Piedra, Papel, Tijera Avatar - Juego desarrollado en C con Raylib

## Descripción

Este proyecto consiste en un juego desarrollado en C utilizando la biblioteca Raylib.

El programa incluye:

- Menú principal.
- Menú de opciones.
- Activación y desactivación de música.
- Juego contra la computadora.
- Sistema de puntuación.
- Imágenes para cada elemento.
- Sonidos de victoria y derrota.

## Requisitos

- GCC
- Raylib 5.x
- Linux

## Archivos del proyecto

- Juego.c
- partida.c
- partida.h
- piedra.png
- papel.png
- tijera.png
- fuego.png
- agua.png
- aire.png
- esponja.png
- victoria.wav
- derrota.wav
- Your Biggest Nightmare Three.ogg

## Compilación

```bash
gcc juego.c partida.c -o juego $(pkg-config --libs --cflags raylib)
```

## Ejecución

```bash
./juego
```

## Controles

- Flechas para navegar por los menús.
- Enter para seleccionar.
- Backspace para regresar.
- Teclas 1 al 7 para elegir la jugada durante la partida.

## Autores
Proyecto desarrollado por:
- Gael Brenes Zúñia C31328
- Oriana Mora López B75079
- Harim Méndez Gómez C24744
