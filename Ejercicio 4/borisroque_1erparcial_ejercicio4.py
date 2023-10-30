from multiprocessing import Pool, cpu_count

# NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
# ----- INF 317 - 1ER EXAMEN PARCIAL - EJERCICIO 4 -----


def generar_serie_parte(inicio, fin):
    serie = [2, 2]
    incremento = 3
    for i in range(2, fin):
        if i % 2 == 0:
            nuevo_termino = serie[i - 2] + incremento
            incremento = incremento + 2
        else:
            nuevo_termino = serie[i - 2] + 2

        serie.append(nuevo_termino)
    return serie

if __name__ == "__main__":
    num_procesos = cpu_count()  
    pool = Pool(processes=num_procesos)  

    rango_por_proceso = 10000 // num_procesos
    rangos = [(i * rango_por_proceso, (i + 1) * rango_por_proceso) for i in range(num_procesos)]

    resultados = pool.starmap(generar_serie_parte, rangos)

    serie_completa = []
    for resultado in resultados:
        serie_completa.extend(resultado)

    # Las siguientes lineas imprimen los primeros 10000 numeros de la serie
    #print("Los primeros 10000 números de la serie son:")
    #print(serie_completa)

    # Imprimir los primeros n números de la serie
    n = 100
    print(f"Los primeros {n} números de la serie son:")
    print(serie_completa[:n])