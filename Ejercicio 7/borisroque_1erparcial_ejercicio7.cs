using System;
using System.Threading;

// NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
// ----- INF 317 - 1ER EXAMEN PARCIAL - EJERCICIO 7 -----

class Program
{
    static double resultado = 0.0;

    static void CalcularPi(int inicio, int fin, object candado)
    {
        double sumaParcial = 0.0;
        for (int i = inicio; i < fin; i++)
        {
            sumaParcial += Math.Pow(-1, i) / (2 * i + 1);
        }
        lock (candado)
        {
            resultado += sumaParcial;
        }
    }

    static void Main(string[] args)
    {
        int numHilos = 4; 
        int iteraciones = 1000000;

        object candado = new object();
        Thread[] hilos = new Thread[numHilos];
        int tamañoBloque = iteraciones / numHilos;

        for (int i = 0; i < numHilos; i++)
        {
            int inicio = i * tamañoBloque;
            int fin = inicio + tamañoBloque;
            hilos[i] = new Thread(() => CalcularPi(inicio, fin, candado));
            hilos[i].Start();
        }

        foreach (Thread hilo in hilos)
        {
            hilo.Join();
        }

        double estimacionPi = resultado * 4;
        Console.WriteLine($"Aproximación de Pi: {estimacionPi}");
    }
}
