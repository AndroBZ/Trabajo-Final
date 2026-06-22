#include "raylib.h"

typedef enum { MENU, OPCIONES, JUEGO } Pantalla;
typedef enum { SELECCIONANDO, CONTANDO, MOSTRANDO } EstadoJuego;

int main() {
    const int pantallaAncho = 1200;
    const int pantallaAlto = 720;
    InitWindow(pantallaAncho, pantallaAlto, "Piedra, Papel, Tijera - Avatar");

    InitAudioDevice();
    Music musica = LoadMusicStream("Your Biggest Nightmare Three.ogg");
    PlayMusicStream(musica);

    Texture2D texturas[3] = { LoadTexture("piedra.png"), LoadTexture("papel.png"), LoadTexture("tijera.png") };

    Pantalla pantallaActual = MENU;
    EstadoJuego estadoJuego = SELECCIONANDO;
    
    const char *opcionesMenu[3] = {"Nueva Partida", "Opciones", "Salir"};
    int opcionSeleccionada = 0;
    
    bool musicaActiva = true;
    int opcionOpciones = 0;
    
    int eleccionJugador = -1;
    int eleccionPC = -1;
    float temporizador = 0.0f;
    const char *resultadoFinal = "";

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (musicaActiva) UpdateMusicStream(musica);

        if (pantallaActual == MENU) {
            if (IsKeyPressed(KEY_DOWN)) { opcionSeleccionada++; if (opcionSeleccionada >= 3) opcionSeleccionada = 0; }
            if (IsKeyPressed(KEY_UP)) { opcionSeleccionada--; if (opcionSeleccionada < 0) opcionSeleccionada = 2; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (opcionSeleccionada == 0) { pantallaActual = JUEGO; estadoJuego = SELECCIONANDO; }
                if (opcionSeleccionada == 1) pantallaActual = OPCIONES;
                if (opcionSeleccionada == 2) break;
            }
        } 
        else if (pantallaActual == OPCIONES) {
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) opcionOpciones = !opcionOpciones;
            if (IsKeyPressed(KEY_ENTER)) {
                if (opcionOpciones == 0) musicaActiva = !musicaActiva;
                if (opcionOpciones == 1) pantallaActual = MENU;
            }
            if (IsKeyPressed(KEY_BACKSPACE)) pantallaActual = MENU;
        }
        else if (pantallaActual == JUEGO) {
            if (estadoJuego == SELECCIONANDO) {
                if (IsKeyPressed(KEY_ONE)) { eleccionJugador = 0; estadoJuego = CONTANDO; temporizador = 3.0f; }
                if (IsKeyPressed(KEY_TWO)) { eleccionJugador = 1; estadoJuego = CONTANDO; temporizador = 3.0f; }
                if (IsKeyPressed(KEY_THREE)) { eleccionJugador = 2; estadoJuego = CONTANDO; temporizador = 3.0f; }
                if (IsKeyPressed(KEY_BACKSPACE)) pantallaActual = MENU;
            } 
            else if (estadoJuego == CONTANDO) {
                temporizador -= GetFrameTime();
                if (temporizador <= 0.0f) {
                    eleccionPC = GetRandomValue(0, 2);
                    if (eleccionJugador == eleccionPC) resultadoFinal = "EMPATE";
                    else if ((eleccionJugador == 0 && eleccionPC == 2) || (eleccionJugador == 1 && eleccionPC == 0) || (eleccionJugador == 2 && eleccionPC == 1)) resultadoFinal = "¡GANASTE!";
                    else resultadoFinal = "PERDISTE";
                    estadoJuego = MOSTRANDO;
                }
            } 
            else if (estadoJuego == MOSTRANDO) {
                if (IsKeyPressed(KEY_SPACE)) {
                    estadoJuego = SELECCIONANDO;
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    pantallaActual = MENU;
                    estadoJuego = SELECCIONANDO;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (pantallaActual == MENU) {
                int p1 = MeasureText("PIEDRA, ", 60);
                int p2 = MeasureText("PAPEL, ", 60);
                int p3 = MeasureText("TIJERA", 60);
                int startX = (pantallaAncho / 2) - ((p1 + p2 + p3) / 2);
                DrawText("PIEDRA, ", startX, 100, 60, MAROON);
                DrawText("PAPEL, ", startX + p1, 100, 60, LIME);
                DrawText("TIJERA", startX + p1 + p2, 100, 60, BLUE);
                DrawText("Avatar", (pantallaAncho / 2) - (MeasureText("Avatar", 80)/2), 170, 80, DARKGRAY);
                for (int i = 0; i < 3; i++) {
                    DrawText(opcionesMenu[i], (pantallaAncho / 2) - (MeasureText(opcionesMenu[i], 40) / 2), 350 + (i * 60), 40, (i == opcionSeleccionada) ? BLUE : GRAY);
                }
            } 
            else if (pantallaActual == OPCIONES) {
                DrawText("MENU DE OPCIONES", (pantallaAncho/2) - (MeasureText("MENU DE OPCIONES", 40)/2), 100, 40, DARKGRAY);
                DrawText(musicaActiva ? "Musica: ON" : "Musica: OFF", 450, 300, 30, (opcionOpciones == 0) ? BLUE : GRAY);
                DrawText("Volver", 450, 360, 30, (opcionOpciones == 1) ? BLUE : GRAY);
            }
            else if (pantallaActual == JUEGO) {
                if (estadoJuego == SELECCIONANDO) {
                    // Texto añadido aquí:
                    DrawText("SELECCIONA TU ELEMENTO", (pantallaAncho/2) - (MeasureText("SELECCIONA TU ELEMENTO", 40)/2), 150, 40, DARKGRAY);

                    for(int i = 0; i < 3; i++) {
                        DrawRectangleLines(250 + (i * 300), 300, 200, 250, DARKGRAY);
                        Rectangle destino = { 250 + (i * 300) + 25, 350, 150, 150 };
                        DrawTexturePro(texturas[i], (Rectangle){0, 0, (float)texturas[i].width, (float)texturas[i].height}, destino, (Vector2){0,0}, 0.0f, WHITE);
                        DrawText(TextFormat("[%i]", i+1), 330 + (i * 300), 570, 30, DARKGRAY);
                    }
                }
                else if (estadoJuego == CONTANDO) {
                    DrawText(TextFormat("%d", (int)temporizador + 1), 600, 300, 100, BLUE);
                }
                else if (estadoJuego == MOSTRANDO) {
                    DrawTexturePro(texturas[eleccionJugador], (Rectangle){0,0,(float)texturas[eleccionJugador].width,(float)texturas[eleccionJugador].height}, (Rectangle){250, 230, 150, 150}, (Vector2){0,0}, 0.0f, WHITE);
                    DrawTexturePro(texturas[eleccionPC], (Rectangle){0,0,(float)texturas[eleccionPC].width,(float)texturas[eleccionPC].height}, (Rectangle){750, 230, 150, 150}, (Vector2){0,0}, 0.0f, WHITE);
                    DrawText(resultadoFinal, (pantallaAncho/2) - (MeasureText(resultadoFinal, 60)/2), 550, 60, DARKGRAY);
                    DrawText("ESPACIO para reiniciar | BACKSPACE al menu", 350, 650, 20, DARKGRAY);
                }
            }
        EndDrawing();
    }

    for(int i = 0; i < 3; i++) UnloadTexture(texturas[i]);
    UnloadMusicStream(musica);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
