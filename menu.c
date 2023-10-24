#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "juego.h"
#include <conio.h>
#include <windows.h>

int mostrarMenuPrincipal(){

    int opcion;

    printf("--------------MENU-----------\n");
    printf("1- Comenzar juego!!!\n");
    printf("2- Ver mini guia del juego\n");
    printf("3- Ver historial de jugadores\n");
    printf("4- Salir del programa\n");
    printf("-----------------------------\n");
    printf("\nElige una opcion -> ");
    scanf("%d", &opcion);
    return opcion;

}

void borrarPantalla(){

    //while (_getch() != 13) {}
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    DWORD charsWritten;
    // Obtén el tamaño de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    // Llena la pantalla con espacios en blanco
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, cursorPosition, &charsWritten);
    // Coloca el cursor en la parte superior izquierda
    SetConsoleCursorPosition(hConsole, cursorPosition);

}

void volverAlMenu(){

    printf("\nPresiona Enter para volver al menu...");
    while (_getch() != 13) {};
    borrarPantalla();

}

void mostrarGuiaDelJuego(){

    printf("\n");
    printf("                                                MINI GUIA\n");
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
    printf("-Iniciara el juego el jugador 1.\n\n");
    printf("-Se le mostrara una pregunta con sus cuatro opciones posibles.\n\n");
    printf("-Debera elegir una respuesta en 15 segundos o menos.\n\n");
    printf("-Se le asignara un puntaje por pregunta correcta y por el tiempo que demoro en responder.\n\n");
    printf("-El jugador seguira jugando mientras que siga acertando respuestas, una vez que pierda pasara al jugador 2,3, etc.\n\n");
    printf("-Una vez que todos pierden se mostrara el puntaje de cada uno. Mostrando quien fue el ganador.\n\n");
    printf("-En caso de un empate entre los ganadores, deberan responder preguntas matematicas y ganara el que mas cerca este.\n\n");
    printf("------------------------------------------------------------------------------------------------------------------\n\n");

    volverAlMenu();
}

void mostrarHistorial(){

    printf("       HISTORIAL\n");
    printf("-----------------------\n");

    FILE * archivo = fopen("historial.txt", "r");

    if(archivo == NULL){
        printf("Error al abrir el archivo historial :c");
        exit(1);
    }

    if(contarRenglonesArchivo("historial.txt") == 0){
        printf("El historial esta vacio");
    }

    char alias[20];
    int dni;
    int puntuacion;

    while (fscanf(archivo, "%99[^,],%d,%d\n", alias, &dni, &puntuacion) == 3) {
        printf("ALIAS: %s\n", alias);
        printf("DNI: %d\n", dni);
        printf("PUNTUACION MAXIMA: %d\n", puntuacion);
        printf("-----------------------\n");
    }
    printf("\n");

    fclose(archivo);

    volverAlMenu();
}
