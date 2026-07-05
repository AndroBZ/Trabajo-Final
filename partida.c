#include "raylib.h"
#include "partida.h"
#include <stdio.h>

// Los elementos del juego se representan con numeros del 0 al 5
// 0 = Piedra, 1 = Papel, 2 = Tijera, 3 = Fuego, 4 = Esponja, 5 = Aire
const char *nombresElementos[6] = {"Piedra", "Papel", "Tijera", "Fuego", "Esponja", "Aire"};

int jugadaJugador = -1;
int jugadaPC = -1;
int resultadoRonda = 0;
int puntosJugador = 0;
int puntosPC = 0;

// Tabla de victorias: si tabla[fila][columna] es 1, el elemento "fila" le gana al elemento "columna"
static int tablaVictorias[6][6] = {
    /*            Piedra Papel Tijera Fuego Esponja Aire */
    /* Piedra  */ {  0,    0,    1,     1,    1,      0 },
    /* Papel   */ {  1,    0,    0,     0,    1,      1 },
    /* Tijera  */ {  0,    1,    0,     0,    1,      1 },
    /* Fuego   */ {  0,    1,    1,     0,    1,      0 },
    /* Esponja */ {  0,    0,    0,     0,    0,      1 },
    /* Aire    */ {  1,    0,    0,     1,    0,      0 }
};

// Devuelve 1 si gana el jugador, -1 si gana la PC, 0 si es empate
static int obtenerResultado(int jugador, int pc) {
    if (jugador == pc) return 0;
    if (tablaVictorias[jugador][pc] == 1) return 1;
    return -1;
}

void iniciarPartida() {
    puntosJugador = 0;
    puntosPC = 0;
    jugadaJugador = -1;
}

int actualizarPartida() {
    if (jugadaJugador == -1) {
        // Esperando que el jugador elija su jugada
        if (IsKeyPressed(KEY_ONE))   jugadaJugador = 0;
        if (IsKeyPressed(KEY_TWO))   jugadaJugador = 1;
        if (IsKeyPressed(KEY_THREE)) jugadaJugador = 2;
        if (IsKeyPressed(KEY_FOUR))  jugadaJugador = 3;
        if (IsKeyPressed(KEY_FIVE))  jugadaJugador = 4;
        if (IsKeyPressed(KEY_SIX))   jugadaJugador = 5;

        if (jugadaJugador != -1) {
            jugadaPC = GetRandomValue(0, 5);
            resultadoRonda = obtenerResultado(jugadaJugador, jugadaPC);
            if (resultadoRonda == 1) puntosJugador++;
            if (resultadoRonda == -1) puntosPC++;
        }
    }
    else {
        // Ya se jugo la ronda, se muestra el resultado
        if (IsKeyPressed(KEY_ENTER)) jugadaJugador = -1;
        if (IsKeyPressed(KEY_BACKSPACE)) {
            jugadaJugador = -1;
            return 1; // avisa que hay que volver al menu
        }
    }
    return 0;
}

void dibujarPartida(int pantallaAncho) {
    if (jugadaJugador == -1) {
        // Pantalla de eleccion
        const char *titulo = "Elegi tu jugada";
        DrawText(titulo, (pantallaAncho/2) - (MeasureText(titulo, 50)/2), 80, 50, DARKGRAY);

        for (int i = 0; i < 6; i++) {
            char linea[40];
            sprintf(linea, "%d - %s", i + 1, nombresElementos[i]);
            int ancho = MeasureText(linea, 35);
            DrawText(linea, (pantallaAncho/2) - (ancho/2), 200 + (i * 50), 35, GRAY);
        }
    }
    else {
        // Pantalla de resultado
        char lineaJugador[50];
        char lineaPC[50];
        sprintf(lineaJugador, "Vos elegiste: %s", nombresElementos[jugadaJugador]);
        sprintf(lineaPC, "La PC eligio: %s", nombresElementos[jugadaPC]);

        DrawText(lineaJugador, (pantallaAncho/2) - (MeasureText(lineaJugador, 40)/2), 150, 40, DARKGRAY);
        DrawText(lineaPC, (pantallaAncho/2) - (MeasureText(lineaPC, 40)/2), 210, 40, DARKGRAY);

        const char *textoResultado;
        Color colorResultado;
        if (resultadoRonda == 1) {
            textoResultado = "GANASTE LA RONDA";
            colorResultado = LIME;
        } else if (resultadoRonda == -1) {
            textoResultado = "PERDISTE LA RONDA";
            colorResultado = MAROON;
        } else {
            textoResultado = "EMPATE";
            colorResultado = GRAY;
        }
        DrawText(textoResultado, (pantallaAncho/2) - (MeasureText(textoResultado, 45)/2), 300, 45, colorResultado);

        char marcador[50];
        sprintf(marcador, "Puntos -> Vos: %d   PC: %d", puntosJugador, puntosPC);
        DrawText(marcador, (pantallaAncho/2) - (MeasureText(marcador, 30)/2), 380, 30, BLUE);

        const char *ayuda = "ENTER para jugar de nuevo, BACKSPACE para volver al menu";
        DrawText(ayuda, (pantallaAncho/2) - (MeasureText(ayuda, 20)/2), 600, 20, MAROON);
    }
}
