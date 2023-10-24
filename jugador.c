#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <conio.h>
#include "jugador.h"
#include "menu.h"
#include "puntos.h"
#include "pregunta.h"
#include "juego.h"

struct JugadorE{

    char alias[20];
    int dni;
    PuntosPtr puntos;

};

JugadorPtr crearJugador(){

    JugadorPtr j = (JugadorPtr) malloc(sizeof(struct JugadorE));

    strcpy(j->alias, "VACIO");
    j->dni = -1;
    j->puntos = crearPuntos();

    return j;

}

JugadorPtr* crearArrayJugadores(int t){

    JugadorPtr* j = (JugadorPtr*) malloc(t * sizeof(struct JugadorE));

    for(int i=0; i<t; i++){
        j[i] = crearJugador();
    }

    return j;

}

int pedirCantJugadores(){

    int cantidad;

    printf("Ingrese el numero de jugadores (de 2 a 4)... ");
    scanf("%d", &cantidad);
    while(cantidad < 2 || cantidad > 4){
        printf("\nError! La cantidad es menor o supera la indicada... Intente denuevo\n");
        printf("\nIngrese el numero de jugadores (de 2 a 4)... ");
        scanf("%d", &cantidad);
    }

    return cantidad;

}

void pedirDatosJugador(JugadorPtr j){

    printf("Alias: ");
    fflush(stdin);
    gets(j->alias);
    printf("DNI: ");
    scanf("%d", &j->dni);

};

void pedirDatosJugadores(JugadorPtr* j, int t){

    printf("\n");
    for(int i=0; i<t; i++){
        printf("----JUGADOR %d----\n", i+1);
        pedirDatosJugador(j[i]);
        printf("\n");
    }
    system("cls");

};


void mostrarPuntosActualesJugador(JugadorPtr j){

    printf("\n\n||PUNTOS ACTUALES: %d PUNTOS||\n", getPuntosActuales(j->puntos));

}

void mostrarPuntuacionMaximaJugador(JugadorPtr j){

    printf("%s -> %d\n", j->alias, getPuntuacionMaxima(j->puntos));

}

void guardarPuntuacionMaximaJugador(JugadorPtr j, int nuevo){

    setPuntuacionMaxima(j->puntos, nuevo);

}

void chequeoPuntos(int cantJugadores, JugadorPtr* j){

    int puntajeMaximo = 0;
    int cantGanadores = 0;
    int* ganadores = (int*)calloc(cantJugadores, sizeof(int));

    for (int i = 0; i < cantJugadores; i++) {

        int puntajeJugador = getPuntuacionMaxima(j[i]->puntos);

        if (puntajeJugador > puntajeMaximo) {

            puntajeMaximo = puntajeJugador;
            cantGanadores = 0; // Reiniciar la lista de ganadores
            ganadores[cantGanadores++] = i; // Establecer el nuevo ganador

        } else if (puntajeJugador == puntajeMaximo) {

               ganadores[cantGanadores++] = i; // Empate, agregar a la lista de ganadores

        }

    }

    if(cantGanadores == 1){
        mostrarResultados(j, cantJugadores);
        printf("\nEL/LA GANADOR/GANADORA ES %s!!\n", getAlias(j[ganadores[0]]));
    }else {
            while(cantGanadores > 1){

                printf("Oh! hubo un empate entre los siguientes jugadores: ");

                for(int i=0; i<cantGanadores; i++){
                    printf("%s ", getAlias(j[ganadores[i]]));
                }
                printf("\n\n");
                printf("||Los jugadores que han empatado deberan responder preguntas matematicas||\n");
                printf("||y el que mas cerca este del resultado sumara un punto, Mucha suerte!! ||\n\n");
                printf("Presione enter para comenzar el desempate...");
                while(_getch() != 13){}
                borrarPantalla();
                double respuestaCorrecta = crearPreguntaMatematica();
                double respuestaJugador;
                double diferenciaMinima = DBL_MAX;
                int cantEmpatados = 0;

                for(int i=0; i<cantGanadores; i++){

                    printf("\n%s Introduce tu respuesta: ", getAlias(j[ganadores[i]]));
                    scanf("%lf", &respuestaJugador);

                    double diferencia = fabs(respuestaJugador - respuestaCorrecta);

                    if(diferencia < diferenciaMinima){
                        diferenciaMinima = diferencia;
                        cantEmpatados = 0;
                        ganadores[cantEmpatados++] = ganadores[i];
                    } else if(diferencia == diferenciaMinima){
                        ganadores[cantEmpatados++] = ganadores[i];
                    }
                }

            cantGanadores = cantEmpatados;
            printf("\n\n");
        }

        setPuntuacionMaxima(j[ganadores[0]]->puntos, (getPuntuacionMaxima(j[ganadores[0]]->puntos) + 1));
        mostrarResultados(j, cantJugadores);
        printf("\nEL/LA GANADOR/GANADORA ES %s!!\n", getAlias(j[ganadores[0]]));

    }

    free(ganadores);

}

void leerHistorial(JugadorPtr* j){

    FILE* archivo = fopen("historial.txt", "r");

    if (archivo == NULL) {
        printf("\nError al abrir el archivo historial.");
        exit(1);
    }

    int i = 0;
    int puntuacion;

    while(!feof(archivo)){
        fscanf(archivo, "%19[^,],%d,%d\n",  j[i]->alias, &j[i]->dni, &puntuacion);
        setPuntuacionMaxima(j[i]->puntos, puntuacion);
        i++;
    }

    fclose(archivo);
}

void guardarEnHistorial(JugadorPtr j){

    FILE *archivo = fopen("historial.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    // Crear un archivo temporal para escribir los datos actualizados
    FILE *tempArchivo = fopen("temp.txt", "w");

    if (tempArchivo == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        exit(1);
    }

    char linea[100];
    char nombreArchivo[50];
    int dniArchivo;
    int puntaje;
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^,],%d,%d", nombreArchivo, &dniArchivo, &puntaje);

        if (j->dni == dniArchivo) {

            if (getPuntuacionMaxima(j->puntos) > puntaje) {
                fprintf(tempArchivo, "%s,%d,%d\n", j->alias, j->dni, getPuntuacionMaxima(j->puntos));
            } else {
                fprintf(tempArchivo, "%s,%d,%d\n", nombreArchivo, dniArchivo, puntaje);
            }
            encontrado = 1;
        } else {
            fprintf(tempArchivo, "%s,%d,%d\n", nombreArchivo, dniArchivo, puntaje);
        }
    }

    if (!encontrado) {
        fprintf(tempArchivo, "%s,%d,%d\n", j->alias, j->dni, getPuntuacionMaxima(j->puntos));
    }

    fclose(archivo);
    fclose(tempArchivo);

    // Reemplazar el archivo original con el archivo temporal
    remove("historial.txt");
    rename("temp.txt", "historial.txt");
}

char* getAlias(JugadorPtr j){

    return j->alias;

}

PuntosPtr getPuntosJugador(JugadorPtr j){

    return j->puntos;

}

void setPuntosJugador(JugadorPtr j, PuntosPtr nuevos){

    j->puntos = nuevos;

}

void liberarArrayJugadores(JugadorPtr* j, int t){

    for(int i=0; i<t; i++){
        liberarPuntos(j[i]->puntos);
        free(j[i]);
    }

    free(j);

}

