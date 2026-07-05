#include "raylib.h"
#include "partida.h"
#include <time.h>

typedef enum { MENU, OPCIONES, PARTIDA } Pantalla;

int main() {
    const int pantallaAncho = 1200;
    const int pantallaAlto = 720;

    InitWindow(pantallaAncho, pantallaAlto, "Juego con Menús");
    InitAudioDevice();
    SetRandomSeed((unsigned int)time(NULL));

    Music musica = LoadMusicStream("Your Biggest Nightmare Three.ogg");
    PlayMusicStream(musica);

    Pantalla pantallaActual = MENU;
    const char *opcionesMenu[3] = {"Nueva Partida", "Opciones", "Salir"};
    int opcionSeleccionada = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMusicStream(musica);

        if (pantallaActual == MENU) {
            if (IsKeyPressed(KEY_DOWN)) {
                opcionSeleccionada++;
                if (opcionSeleccionada >= 3) opcionSeleccionada = 0;
            }
            if (IsKeyPressed(KEY_UP)) {
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = 2;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (opcionSeleccionada == 0) {
                    iniciarPartida();
                    pantallaActual = PARTIDA;
                }
                if (opcionSeleccionada == 1) pantallaActual = OPCIONES;
                if (opcionSeleccionada == 2) break;
            }
        }
        else if (pantallaActual == OPCIONES) {
            if (IsKeyPressed(KEY_BACKSPACE)) pantallaActual = MENU;
        }
        else if (pantallaActual == PARTIDA) {
            int volverAlMenu = actualizarPartida();
            if (volverAlMenu) pantallaActual = MENU;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (pantallaActual == MENU) {
                int p1 = MeasureText("PIEDRA, ", 60);
                int p2 = MeasureText("PAPEL, ", 60);
                int p3 = MeasureText("TIJERA", 60);
                int totalAncho = p1 + p2 + p3;
                int startX = (pantallaAncho / 2) - (totalAncho / 2);
                DrawText("PIEDRA, ", startX, 100, 60, MAROON);
                DrawText("PAPEL, ", startX + p1, 100, 60, LIME);
                DrawText("TIJERA", startX + p1 + p2, 100, 60, BLUE);

                int subAncho = MeasureText("Avatar", 80);
                DrawText("Avatar", (pantallaAncho / 2) - (subAncho / 2), 170, 80, DARKGRAY);

                for (int i = 0; i < 3; i++) {
                    int anchoOpcion = MeasureText(opcionesMenu[i], 40);
                    Color color = (i == opcionSeleccionada) ? BLUE : GRAY;

                    if (i == opcionSeleccionada)
                        DrawText("->", (pantallaAncho / 2) - (anchoOpcion / 2) - 50, 350 + (i * 60), 40, BLUE);

                    DrawText(opcionesMenu[i], (pantallaAncho / 2) - (anchoOpcion / 2), 350 + (i * 60), 40, color);
                }
            }
            else if (pantallaActual == OPCIONES) {
                DrawText("MENU DE OPCIONES", (pantallaAncho/2) - (MeasureText("MENU DE OPCIONES", 40)/2), 100, 40, DARKGRAY);
                DrawText("Presiona BACKSPACE para volver", (pantallaAncho/2) - (MeasureText("Presiona BACKSPACE para volver", 20)/2), 600, 20, MAROON);
            }
            else if (pantallaActual == PARTIDA) {
                dibujarPartida(pantallaAncho);
            }
        EndDrawing();
    }

    UnloadMusicStream(musica);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
