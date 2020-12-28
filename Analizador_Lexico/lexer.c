#include <stdio.h>
#include <string.h>
#include "lexer.h"

/* TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO */
//char palabras_reservadas[] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

//char operadores_relacionales[] = {">", "<", "=="};

//char operadores_aritmeticos[] = {'+', '-', '*', '/'};

//char asignacion = '=';

char comentario = '#';

//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------

/* La función halla la cantidad de líneas de un texto */
int __contarLineasArchivo(FILE *archivo)
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
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned int chars, char cadena[lineas][chars])
{
    unsigned int i = 0;

    while(1)
    {
        if(fgets(cadena[i], chars, archivo) != NULL) 
        {
            printf("%s", cadena[i]);
            i++;
        }
        else
        {
            break;
        }
    }
}

void generarTokens(unsigned int lineas, unsigned int chars, char cadena[lineas][chars])
{
    char *ptr, *token;
    unsigned int i;

    for(i = 0; i < lineas; i++)
    {
        token = strtok_r(cadena[i], " \n", &ptr);
        
        while (token != NULL)
        {
            printf("\n%s", token);
            token = strtok_r(NULL, " \n", &ptr);
        }
    }
}

/* La función imprime un arreglo con las líneas del archivo */
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars])
{
    unsigned int i;

    for(i = 0; i < lineas; i++)
        printf("\n%s", arreglo[i]);
}

int main(int argc, char **argv)
{   
    if (argc>1)
    {
        // Puntero al archivo:
        FILE *archivo = fopen(argv[1], "r");
    
        // Se cuenta la cantidad de líneas del archivo:
        unsigned int lineas;
        lineas = __contarLineasArchivo(archivo);
        fclose(archivo); // Se cierra el archivo

        // Cantidad de caracteres máximos de cada archivo:
        unsigned int caracteres = 256;

        // Arreglo que almacenará cada línea del archivo:
        char array[lineas][caracteres];

        // Puntero al archivo:
        FILE *parchivo = fopen(argv[1], "r");
        
        // Se guarda cada línea del archivo:
        __guardarLineas(parchivo, lineas, caracteres, array);
        fclose(parchivo); // Se cierra el archivo

        // Se imprime cada línea del archivo:
        printf("\n\n\nSe imprime lo del documento.\n");
        __imprimeLineas(lineas, caracteres, array);
        printf("\n\n\n");

        // Se generan los tokens:
        generarTokens(lineas, caracteres, array);
        

        // Se genera el archivo .lex:
        //generarLexer(lineas, array);

        // Se imprime la última línea del archivo:
        //printf("\nEl numero de caracteres de la ultima linea es: %d", strlen(array[lineas-1]));
        
    }

    return 0;
}
