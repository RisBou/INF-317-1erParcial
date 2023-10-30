#include <stdio.h>
#include <string.h>
#include <mpi.h>

//NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
//--------INF 317 - 1ER EXAMEN PARCIAL, EJERCICIO 3------------



void divideFrase(char *frase, char *fraseImpar, char *frasePar, int numPalabras) {
    char palabras[numPalabras][1000]; 

    
    char *token = strtok(frase, " ");
    int i = 0;
    while (token != NULL) {
        strcpy(palabras[i], token);
        i++;
        token = strtok(NULL, " ");
    }

  
    for (i = 0; i < numPalabras; ++i) {
        if (i % 2 == 0) {
            
            strcat(frasePar, palabras[i]);
            strcat(frasePar, " ");
        } else {
            
            strcat(fraseImpar, palabras[i]);
            strcat(fraseImpar, " ");
        }
    }
}

void main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, numProcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char fraseImpar[1000] = ""; 
    char frasePar[1000] = ""; 

    int numPalabras;
    if (rank == 0) {
        numPalabras = 10; 
    }

    MPI_Bcast(&numPalabras, 1, MPI_INT, 0, MPI_COMM_WORLD);

   
    divideFrase(frase, fraseImpar, frasePar, numPalabras);

    
    char resultadoFraseImpar[1000 * numProcs];
    char resultadoFrasePar[1000 * numProcs];

    MPI_Gather(fraseImpar, 1000, MPI_CHAR, resultadoFraseImpar, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Gather(frasePar, 1000, MPI_CHAR, resultadoFrasePar, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Finalize();

   
    if (rank == 0) {
    	printf("Primera Frase: %s\n", resultadoFrasePar);
        printf("Segunda Frase: %s\n", resultadoFraseImpar);
        
    }

}

