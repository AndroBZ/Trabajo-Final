#ifndef PARTIDA_H
#define PARTIDA_H

// Nombres de los 6 elementos del juego, en el mismo orden que sus numeros (0 a 5)
extern const char *nombresElementos[6];

// Variables del estado de la partida (se comparten con Juego.c)
extern int jugadaJugador;   // -1 significa que todavia no eligio nada esta ronda
extern int jugadaPC;
extern int resultadoRonda;  // 1 = gana jugador, -1 = gana PC, 0 = empate
extern int puntosJugador;
extern int puntosPC;

// Carga las 6 imagenes de los elementos. Llamar una sola vez al arrancar el juego
void cargarImagenesPartida();

// Libera las 6 imagenes de memoria. Llamar una sola vez antes de cerrar el juego
void descargarImagenesPartida();

// Reinicia el marcador y deja la partida lista para arrancar
void iniciarPartida();

// Procesa el teclado mientras se esta jugando (elegir jugada, ver resultado, volver al menu)
// Devuelve 1 si hay que volver al menu, 0 si hay que seguir en la partida
int actualizarPartida();

// Dibuja en pantalla la eleccion de jugada o el resultado de la ronda
void dibujarPartida(int pantallaAncho);

#endif
