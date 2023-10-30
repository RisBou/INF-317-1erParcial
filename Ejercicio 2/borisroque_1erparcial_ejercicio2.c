#include <stdio.h>
#include <string.h>
#include <omp.h>

//NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
//-----INF - 317 - 1ER EXAMEN PARCIAL - EJERCICIO 2------

void divideFrase(char *frase, char *fraseImpar, char *frasePar) {
    int longitud = strlen(frase);
    char palabras[longitud][longitud]; 
    int numPalabras = 0;

    char *token = strtok(frase, " ");
    while (token != NULL) {
        strcpy(palabras[numPalabras], token);
        numPalabras++;
        token = strtok(NULL, " ");
    }
  
    #pragma omp parallel for shared(numPalabras, palabras, fraseImpar, frasePar)
    for (int i = 0; i < numPalabras; ++i) {
        if (i % 2 == 0) {
            strcat(frasePar, palabras[i]);
            strcat(frasePar, " ");
        } else {
            strcat(fraseImpar, palabras[i]);
            strcat(fraseImpar, " ");
        }
    }
}

void main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char fraseImpar[1000] = ""; 
    char frasePar[1000] = ""; 

    divideFrase(frase, fraseImpar, frasePar);

    printf("Primera Frase: %s\n", frasePar);
    printf("Segunda Frase: %s\n", fraseImpar);
}

