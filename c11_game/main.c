#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "game.h";

int completeIfWinner(int location, int aciertos_posicion, int aciertos_color) {
    if (aciertos_posicion == TAM_COMBINACION) {
        printf("\n¡Felicidades! %s combinación correctamente.\n", jugadores[location].nombre);
        jugadores[location].intentos = MAX_INTENTOS - num_jugadas;
        jugadores[location].aciertos_posicion = aciertos_posicion;
        jugadores[location].aciertos_color = aciertos_color;
        return 1;
    }
    return 0;
}

int validateIfContinue(char option_selected[5]) {
    if (!validarEntrada(option_selected)) {
        coloresPermitidos();
        printf("\nEntrada inválida. colores válidos. \n");
        return 1;
    }
    if (buscarJugadaRepetida(history, option_selected, num_jugadas)) {
        coloresPermitidos();
        printf("\nPor favor, intenta otra combinacion.\n");
        return 1;
    }
    return 0;
}

void play(void) {
    agregar_jugador();
    int intentos = 3;
    int location = num_jugadores-1;
    printf("Welcome: %s", jugadores[location].nombre);
    printf("\nIntentos maximos:");
    scanf("%d", &intentos);
    int aciertos_posicion = 0, aciertos_color = 0;
    do {
        char option_selected[TAM_COMBINACION + 1];
        printf("\n%s", combinacion);
        coloresPermitidos();
        printf("\nJugada %d --> :", num_jugadas);
        scanf("\n%s", option_selected);

        if (validateIfContinue(option_selected)) continue;

        obtenerRespuesta(combinacion, option_selected, &aciertos_posicion, &aciertos_color);
        registrarJugada(history, option_selected, aciertos_posicion, aciertos_color, &num_jugadas);
        printf("Aciertos de posición: %d\n", aciertos_posicion);
        printf("Aciertos de color: %d\n", aciertos_color);

        if (completeIfWinner(location, aciertos_posicion, aciertos_color)) break;

    } while (num_jugadas <= intentos);
    printf("\nIntentos agotados. La combinación : %s\n", combinacion);
}

int evaluateOption(char opt[2]) {
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
        return 1;
    }
    return 0;
}

int main() {
    while (IS_TRUE) {
        generarCombinacion(combinacion);
        char opt[2];
        options();
        printf("\tOption:");
        scanf("%s", opt);
        if (evaluateOption(opt)) break;
    }
    wait_second();
    return 0;
}
