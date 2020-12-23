#include <stdio.h>
#include <string.h>
#include "lexer.h"

/* TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO */
char palabras_reservadas[] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

char operadores_relacionales[] = {">", "<", "=="};

char operadores_aritmeticos[] = {'+', '-', '*', '/'};

char asignacion = '=';

char comentario = '#';

//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------

/* La función halla la cantidad de líneas de un texto */
int contarLineaArchivo(FILE *archivo)
{
    int numero_lineas = 0;
    char c; // Almacena el caracter leído del archivo.

    // Si el archivo no existe:
    if (!archivo)
    {
        printf("ERROR: No se pudo abrir el archivo");
        return -1;
    }

    // Se extra el primer caracter de cada línea y se guarda en c:
    for(c = getc(archivo); c != EOF; c = getc(archivo))
        if(c == '\n') // Si hay un salto de línea se incrementa el contador.
            numero_lineas++;

    printf("La cantidad de lineas es: %d\n", numero_lineas+1);
    return numero_lineas+1; // Se retorna la cantidad de líneas del archivo.
}

/* La función almacena las líneas del archivo dentro de un vector */
char *guardarLineas(char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "r"); // Puntero al principio del archivo.
    FILE *puntero_archivo = fopen(nombre_archivo, "r");
    int cantidad_lineas = contarLineaArchivo(archivo); // Se cuenta el número de líneas del archivo.

    char lineas[cantidad_lineas][256]; // Arreglo que almacena las líneas del archivo.

    unsigned int i = 0; // Contador

    // Se lee cada línea del archivo y se almacena en el arreglo:
    while(fgets(lineas[i], 256, puntero_archivo) != NULL)
    {   
        printf("%s", lineas[i]);    
        i++; // Se aumenta el contador
    }

    fclose(archivo); // Se cierra el archivo
    fclose(puntero_archivo);
}

