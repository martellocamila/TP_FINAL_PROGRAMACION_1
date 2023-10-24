#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include "juego.h"
#include "jugador.h"
#include "pregunta.h"
#include "respuesta.h"
#include "puntos.h"
#include "menu.h"

int chequeoTiempo(int tiempoTranscurrido){

    if(tiempoTranscurrido <= 5){
        return 1;
    }
    else if(tiempoTranscurrido <= 10){
        return 2;
    }
    else if(tiempoTranscurrido < 15){
        return 3;
    }
    else if(tiempoTranscurrido >= 15){
        return 4;
    }

    return 0;
}

int chequeoRespuesta(int respuesta, PreguntaPtr* p, int pos){

    RespuestaPtr* posibles = getPosibles(p, pos);

    if(respuesta == (getPosicionCorrecta(posibles)+1)){
        return 1;
    }

    return 0;
}

double crearPreguntaMatematica(){

    int num1 = 10 + rand() % 9991;
    int num2 =  10 + rand() % 10000;
    char operador;
    int operadorAleatorio = rand() % 4;

     switch (operadorAleatorio) {
        case 0:
            operador = '+';
            break;
        case 1:
            operador = '-';
            break;
        case 2:
            operador = '*';
            break;
        case 3:
            operador = '/';
            break;
    }

    printf("Cuanto es %d %c %d?\n", num1, operador, num2);

    double resultado;

    switch (operador) {
        case '+':
            resultado = num1 + (double)num2;
            break;
        case '-':
            resultado = num1 - (double)num2;
            break;
        case '*':
            resultado = num1 * (double)num2;
            break;
        case '/':
            resultado = num1 / (double)num2;
            break;
    }

    return resultado;

}

void mostrarResultados(JugadorPtr* j, int cantJugadores){

    printf("El JUEGO HA TERMINADO! AQUI ESTAN LOS RESULTADOS...\n\n");

    for(int i=0; i<cantJugadores; i++){
        mostrarPuntuacionMaximaJugador(j[i]);
    }

}

void juego(int cantJugadores, JugadorPtr* j, PreguntaPtr* p){

    time_t tiempoActual;
    int respuesta;
    int *preguntasUsadas = (int*)calloc(contarRenglonesArchivo("preguntas.txt"), sizeof(int));
    int preguntaActual;
    int cantPreguntasPorJugador;
    int auxPuntos;
    int preguntasRespondidasTotal = 0;

    for(int i=0; i<cantJugadores; i++){

        cantPreguntasPorJugador = 0;
        PuntosPtr puntos = getPuntosJugador(j[i]);
        auxPuntos = 0;

        while(1){

            preguntasRespondidasTotal++;
            cantPreguntasPorJugador++;
            borrarPantalla();
            printf("TURNO DE %s - PREGUNTA %d\n\n", getAlias(j[i]), cantPreguntasPorJugador);
            preguntaActual = indicePreguntaAleatoria(preguntasUsadas);
            mostrarPreguntaConRespuestas(p, preguntaActual);
            time_t tiempoInicio = time(NULL);
            printf("\nELIGE LA OPCION CORRECTA -> ");
            scanf("%d", &respuesta);

            //Obtiene el tiempo actual nuevamente
            tiempoActual = time(NULL);
            //Calcula el tiempo transcurrido
            int tiempoTranscurrido = difftime(tiempoActual, tiempoInicio);

            int resultadoTiempo = chequeoTiempo(tiempoTranscurrido);
            int resultadoRespuesta = chequeoRespuesta(respuesta, p, preguntaActual);

            if(resultadoRespuesta == 1){
                switch(resultadoTiempo){
                    case 1:
                        printf("\nCorrecto! Has respondido en menos de 5 seg, obtienes el puntaje maximo! (+3)\n");
                        auxPuntos += 3;
                        break;

                    case 2:
                        printf("\nCorrecto! Has respondido en menos de 10 seg, obtienes el puntaje medio! (+2)\n");
                        auxPuntos += 2;
                        break;

                    case 3:
                        printf("\nCorrecto! Has respondido en menos de 15 seg, obtienes el puntaje minimo! (+1)\n");
                        auxPuntos += 1;
                        break;

                    case 4:
                        printf("\nTiempo agotado! Has perdido :c\n");
                        break;
                }

            } else{
                printf("\nINCORRECTO! Has perdido :c\n");
            }

            setPuntosActuales(puntos, auxPuntos);
            setPuntosJugador(j[i], puntos);

            printf("\nPRESIONE ENTER PARA ");
            if(resultadoRespuesta == 1 && resultadoTiempo != 4){

                printf("PASAR A LA SIGUIENTE PREGUNTA...");
                mostrarPuntosActualesJugador(j[i]);
                while(_getch() != 13){}

            }else if(resultadoRespuesta == 0 || resultadoTiempo == 4){

                if(i != (cantJugadores-1)){
                    printf("QUE COMIENCE EL SIGUIENTE JUGADOR...");
                }else{
                    printf("VER LOS RESULTADOS...");
                }

                while(_getch() != 13){}
                break;

            }

            guardarPuntuacionMaximaJugador(j[i], getPuntosActuales(puntos));

        }

    }

    free(preguntasUsadas);
    borrarPantalla();
    chequeoPuntos(cantJugadores, j);
    for(int i=0; i<cantJugadores; i++){
        guardarEnHistorial(j[i]);
    }
    volverAlMenu();

}




