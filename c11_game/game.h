#ifndef GAME_H
#define GAME_H

#define NUM_COLORES 6
#define TAM_COMBINACION 4
#define MAX_INTENTOS 10
#define MAX_JUGADORES 100
#define MAX_NOMBRE 50
#define MAX_HISTORIAL 100
#define IS_TRUE 1

typedef struct {
    char nombre[MAX_NOMBRE];
    int intentos;
    int aciertos_posicion;
    int aciertos_color;
} Jugador;

void agregar_jugador();
void generarCombinacion(char combinacion[]);
void obtenerRespuesta(char combinacion[], char intento[], int *aciertos_posicion, int *aciertos_color);
void registrarJugada(char historial[][TAM_COMBINACION+1], char intento[], int aciertos_posicion, int aciertos_color, int *num_jugadas);
void mostrarJugadores(Jugador jugadores[], int num_jugadores);
void mostrarInstrucciones();
int esComandoEspecial(char entrada[]);
int validarEntrada(char entrada[]);
int buscarJugadaRepetida(char historial[][TAM_COMBINACION+1], char intento[], int num_jugadas);
void mostrarHistorial(void);

void options();
void wait_second();
int isEqual(char s1[],char s2[]);
void coloresPermitidos(void);

char colores[NUM_COLORES] = {'V', 'R', 'A', 'M', 'N', 'C'};
char combinacion[TAM_COMBINACION + 1];
char history[MAX_HISTORIAL][TAM_COMBINACION + 1];
int num_jugadas = 1;
Jugador jugadores[MAX_JUGADORES];
int num_jugadores = 0;

inline void coloresPermitidos(void) {
    printf("\nV=Verde  R=Rojo A=Amarillo M=Morado C=Cafe N=Naranja)");
}
inline void obtenerRespuesta(char combinacion[], char intento[], int *aciertos_posicion, int *aciertos_color) {
    int i, j;
    *aciertos_posicion = 0;
    *aciertos_color = 0;

    for (i = 0; i < TAM_COMBINACION; i++) {
        if (combinacion[i] == intento[i]) {
            (*aciertos_posicion)++;
        } else {
            for (j = 0; j < TAM_COMBINACION; j++) {
                if (combinacion[i] == intento[j]) {
                    (*aciertos_color)++;
                    break;
                }
            }
        }
    }
}

inline void registrarJugada(char historial[][TAM_COMBINACION+1], char intento[], int aciertos_posicion, int aciertos_color, int *num_jugadas) {
    strcpy(historial[*num_jugadas], intento);
    *num_jugadas += 1;
}

inline void mostrarJugadores(Jugador jugadores[], int num_jugadores) {
    printf("\nEstadísticas de jugadores:\n");
    for (int i = 0; i < num_jugadores; i++) {
        printf("Jugador:[%i] %s - Intentos restantes: %d - Aciertos de posición: %d - Aciertos de color: %d\n",i,
               jugadores[i].nombre, jugadores[i].intentos, jugadores[i].aciertos_posicion, jugadores[i].aciertos_color);
    }
}
int esComandoEspecial(char entrada[]) {
    return (strcmp(entrada, "historia") == 0 || strcmp(entrada, "salir") == 0 || strcmp(entrada, "trampa") == 0);
}

inline void mostrarInstrucciones() {
    printf("\n\t________________________________________________________________________________________________________\n\n");
    printf("\n\t¡Bienvenido al juego MasterMind!\n\n");
    printf("\tInstrucciones del juego MasterMind:\n\n");
    printf("\tEl sistema generará una combinación de 4 colores aleatoriamente.\n");
    printf("\tDeberás proponer una combinación de 4 colores.\n");
    printf("\tEl sistema indicará cuántos aciertos de color y posición tienes, y cuántos aciertos únicamente de color.\n\n");
    printf("\tEl sistema no indicará la posición de los aciertos, solo dirá si hay aciertos.\n");
    printf("\tTienes un máximo de 10 intentos para adivinar la combinación correcta.\n");
    printf("\tIntroduce tu combinación de 4 colores(Verde,Rojo,Amarillo,Morado,Cafe,Naranja):\n");
    printf("\t!Ingresa unicamente la inicial del color en mayusculas:");
    printf("\n\t________________________________________________________________________________________________________\n\n");
}

inline int validarEntrada(char entrada[]) {
    if (strlen(entrada) != TAM_COMBINACION) return 0;

    for (int i = 0; i < TAM_COMBINACION; i++) {
        char c = toupper(entrada[i]);
        int encontrado = 0;
        for (int j = 0; j < NUM_COLORES; j++) {
            if (c == colores[j]) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) return 0;
    }
    return 1;
}

inline int buscarJugadaRepetida(char historial[][TAM_COMBINACION+1], char intento[], int num_jugadas) {
    for (int i = 0; i < num_jugadas; i++) {
        if (strcmp(historial[i], intento) == 0) {
            return 1; // Jugada encontrada
        }
    }
    return 0; // Jugada no encontrada
}

inline int isEqual(char s1[],char s2[]) {
    // if equal then return 0
   return strcmp(s1, s2) == 0 ? 1: 0;
}

inline void options() {
    printf("\n\t_____ OPCIONES  ___________\n\n");
    printf("\t A) INICIAR JUEGO. \n\n");
    printf("\t B) JUGADORES Y ESTADISTICAS.\n\n");
    printf("\t C) INSTRUCCIONES. \n");
    printf("\n\t___________________________\n");
}

inline void wait_second() {
    system("clear");
    printf("\t Escribe una tecla para continuar...\n");
    getchar();
}

inline void generarCombinacion(char combinacion[]) {
    srand(time(NULL));
    for (int i = 0; i < TAM_COMBINACION; i++) {
        combinacion[i] = colores[rand() % NUM_COLORES];
    }
    combinacion[TAM_COMBINACION] = '\0'; // Terminador de cadena
}

inline void mostrarHistorial(void) {
    printf("\nHistorial de jugadas:\n");
    for (int i = 0; i < num_jugadas; i++) {
        printf("%s\n", history[i]);
    }
}

inline void agregar_jugador() {
    printf("---- > REGISTRATE PARA JUGAR. \n");
    if (num_jugadores < MAX_JUGADORES) {
        printf("Nombre: ");
        fgets(jugadores[num_jugadores].nombre, MAX_NOMBRE, stdin);
        jugadores[num_jugadores].nombre[strcspn(jugadores[num_jugadores].nombre, "\n")] = '\0';
        printf("Intentos permitidos: ");
        scanf("%d", &jugadores[num_jugadores].intentos);
        num_jugadores++;
        while (getchar() != '\n') {
        }
    } else {
        printf("Máximo de jugadores.\n");
    }
    mostrarJugadores(jugadores,num_jugadores);
}
#endif //GAME_H
