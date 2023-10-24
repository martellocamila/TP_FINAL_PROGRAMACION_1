#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "juego.h"
#include "pregunta.h"
#include "respuesta.h"
#include "jugador.h"

int main()
{
    srand(time(0));
    int cantPreguntas = contarRenglonesArchivo("preguntas.txt");
    int cantRespuestas = contarRenglonesArchivo("respuestas.txt");
    PreguntaPtr* p = crearArrayPreguntas(cantPreguntas);
    RespuestaPtr* r = crearArrayRespuestas(cantRespuestas);
    leerPreguntas(p);
    leerRespuestas(r);
    asociarRespuestas(p, r, cantPreguntas, cantRespuestas);
    int cantJugadores;
    int opcion;

    do{
        opcion = mostrarMenuPrincipal();
        switch(opcion){

                case 1:
                    borrarPantalla();
                    cantJugadores = pedirCantJugadores();
                    JugadorPtr* j = crearArrayJugadores(cantJugadores);
                    pedirDatosJugadores(j, cantJugadores);
                    juego(cantJugadores, j, p);
                    liberarArrayJugadores(j, cantJugadores);
                    break;

                case 2:
                    borrarPantalla();
                    mostrarGuiaDelJuego();
                    break;

                case 3:
                    borrarPantalla();
                    mostrarHistorial();
                    break;

                case 4:
                    exit(0);
                    break;

                default:
                    getchar();
                    borrarPantalla();
                    printf("Opcion no disponible! Por favor, ingrese una del 1 al 4\n\n");
                    break;
        }

    } while(1);

    liberarArrayPreguntas(p, cantPreguntas);
    liberarArrayRespuestas(r, cantRespuestas);


    return 0;
}
