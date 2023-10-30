#include <stdio.h>
#include <mpi.h>

//NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
//--------INF 317 - 1ER EXAMEN PARCIAL, EJERCICIO 6------------

void generar_serie_parte(int inicio, int fin, int *serie) {
    int incremento = 3;
    serie[0] = 2;
    serie[1] = 2;

    for (int i = 2; i < fin; ++i) {
        if (i % 2 == 0) {
            serie[i] = serie[i - 2] + incremento;
            incremento += 2;
        } else {
            serie[i] = serie[i - 2] + 2;
        }
    }
}

int main(int argc, char **argv) {
    int num_procesos, id_proceso, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_proceso);

    int rango_por_proceso = 10000 / num_procesos;
    int inicio = id_proceso * rango_por_proceso;
    int fin = (id_proceso + 1) * rango_por_proceso;
    int resultado_local[rango_por_proceso];

    generar_serie_parte(inicio, fin, resultado_local);

    int serie_completa[10000];
    MPI_Gather(resultado_local, rango_por_proceso, MPI_INT, serie_completa, rango_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

    if (id_proceso == 0) {
        //printf("Los primeros 10000 números de la serie son:\n");
        //for (i = 0; i < 10000; ++i) {
            //printf("%d ", serie_completa[i]);
        //}
        //printf("\n");

        // Imprimir los primeros n números de la serie
        printf("Los primeros %d números de la serie son:\n", n);
        for (i = 0; i < n; ++i) {
            printf("%d ", serie_completa[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

