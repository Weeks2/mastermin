#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "game.h";

void play(void) {
    agregar_jugador();
    int intentos = 3;
    printf("Welcome: %s", jugadores[num_jugadores-1].nombre);
    printf("\nCuantos intentos limite?:");
    scanf("%d", &intentos);
    int aciertos_posicion = 0, aciertos_color = 0;
    do {
        char option_selected[TAM_COMBINACION + 1];
        printf("\n%s", combinacion);
        printf("\nV=Verde  R=Rojo A=Amarillo M=Morado C=Cafe N=Naranja)");
        printf("\nJugada %d --> :", num_jugadas);
        scanf("\n%s", option_selected);

        if (!validarEntrada(option_selected)) {
            printf("\nEntrada inválida. Por favor, introduce 4 colores válidos.\n");
            continue;
        }
        if (buscarJugadaRepetida(history, option_selected, num_jugadas)) {
            printf("\nYa has ingresado esta combinación. Por favor, intenta otra.\n");
            continue;
        }
        obtenerRespuesta(combinacion, option_selected, &aciertos_posicion, &aciertos_color);
        registrarJugada(history, option_selected, aciertos_posicion, aciertos_color, &num_jugadas);

        printf("Aciertos de posición: %d\n", aciertos_posicion);
        printf("Aciertos de color: %d\n", aciertos_color);

        if (aciertos_posicion == TAM_COMBINACION) {
            printf("\n¡Felicidades! %s combinación correctamente.\n", jugadores[num_jugadores].nombre);
            jugadores[num_jugadores].intentos = MAX_INTENTOS - num_jugadas;
            jugadores[num_jugadores].aciertos_posicion = aciertos_posicion;
            jugadores[num_jugadores].aciertos_color = aciertos_color;
            break;
        }
    } while (num_jugadas <= intentos);
    printf("\nhas agotado todos tus intentos. La combinación : %s\n", combinacion);
}

int main() {
    while (1) {
        generarCombinacion(combinacion);
        printf("\n%s", combinacion);
        char opt[2];
        options();
        printf("\nElige una opcion:");
        scanf("\n%s", opt);
        if (isEqual(opt, "A") || isEqual(opt, "a")) {
            wait_second();
            play();
        }
        if (isEqual(opt, "B") || isEqual(opt, "b")) {
            wait_second();
            printf("\nLa combinación correcta es: %s\n", combinacion);
            mostrarJugadores(jugadores, num_jugadores);
            mostrarHistorial();
        }
        if (isEqual(opt, "C") || isEqual(opt, "c")) {
            wait_second();
            mostrarInstrucciones();
        }
        if (isEqual(opt, "D") || isEqual(opt, "d") || isEqual(opt, "0")) {
            break;
        }
    }
    wait_second();
    return 0;
}
