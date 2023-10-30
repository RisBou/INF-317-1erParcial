using System;
using System.Collections.Generic;
using System.Threading;


// NOMBRES Y APELLIDOS: BORIS ORLANDO ROQUE HUANCA, CI: 9868420 LP
// ----- INF 317 - 1ER EXAMEN PARCIAL - EJERCICIO 5 -----

class Program
{
    static List<int> serieCompleta = new List<int>();
    static int numProcesos = Environment.ProcessorCount;
    static int threadsCompleted = 0;

    static void GenerarSerieParte(object estado)
    {
        int[] rango = (int[])estado;
        int inicio = rango[0];
        int fin = rango[1];
        List<int> serie = new List<int> { 2, 2 };
        int incremento = 3;
        for (int i = 2; i < fin; i++)
        {
            if (i % 2 == 0)
            {
                int nuevoTermino = serie[i - 2] + incremento;
                incremento = incremento + 2;
                serie.Add(nuevoTermino);
            }
            else
            {
                int nuevoTermino = serie[i - 2] + 2;
                serie.Add(nuevoTermino);
            }
        }

        lock (serieCompleta)
        {
            serieCompleta.AddRange(serie);
        }

        Interlocked.Increment(ref threadsCompleted);
        if (threadsCompleted == numProcesos)
        {
            // Esta linea imprime los 10000 primeros numeros de la serie
            //Console.WriteLine("Serie completa: " + string.Join(", ", serieCompleta));

            // Imprimir los primeros n números de la serie
            int n = 100;
            Console.WriteLine($"Primeros {n} números de la serie: " + string.Join(", ", serieCompleta.GetRange(0, n)));
        }
    }

    static void Main(string[] args)
    {
        int rangoPorProceso = 10000 / numProcesos;
        for (int i = 0; i < numProcesos; i++)
        {
            int inicio = i * rangoPorProceso;
            int fin = (i + 1) * rangoPorProceso;
            ThreadPool.QueueUserWorkItem(GenerarSerieParte, new int[] { inicio, fin });
        }

        Console.ReadLine(); 
}
