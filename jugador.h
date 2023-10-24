#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "puntos.h"

struct JugadorE;
typedef struct JugadorE *JugadorPtr;

//constructores
JugadorPtr crearJugador();
JugadorPtr* crearArrayJugadores(int t);

int pedirCantJugadores();
void pedirDatosJugador(JugadorPtr j);
void pedirDatosJugadores(JugadorPtr* j, int t);
void guardarPuntuacionMaximaJugador(JugadorPtr j, int nuevo);

void mostrarPuntosActualesJugador(JugadorPtr j);
void mostrarPuntuacionMaximaJugador(JugadorPtr j);

void chequeoPuntos(int cantJugadores, JugadorPtr* j);

//leer y guardar jugadores en el historial
void leerHistorial(JugadorPtr* j);
void guardarEnHistorial(JugadorPtr j);

//getters
char* getAlias(JugadorPtr j);
PuntosPtr getPuntosJugador(JugadorPtr j);

//setters
void setPuntosJugador(JugadorPtr j, PuntosPtr nuevos);
void setPuntuacionMaximaJugador(JugadorPtr j, int nuevo);

//destructor
void liberarArrayJugadores(JugadorPtr* j, int t);

#endif // JUGADOR_H_INCLUDED
