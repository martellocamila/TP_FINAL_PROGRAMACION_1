#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "pregunta.h"
#include "jugador.h"

int chequeoTiempo(int tiempoTranscurrido);
int chequeoRespuesta(int respuesta, PreguntaPtr* p, int pos);
void juego(int cantJugadores, JugadorPtr* j, PreguntaPtr* p);
double crearPreguntaMatematica();
void mostrarResultados(JugadorPtr* j, int cantJugadores);

#endif // JUEGO_H_INCLUDED
