#include "lexer.c"
// Programa principal del analizador léxico.

/* Función principal */
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
        printf("\n\n\nSe verifican los tokens:\n");
        anaLex(lineas, caracteres, array);

        // Se genera el archivo .lex:
        //generarLexer(lineas, array);

        // Se imprime la última línea del archivo:
        //printf("\nEl numero de caracteres de la ultima linea es: %d", strlen(array[lineas-1]));
        
    } // Fin if
    else
    {
        printf("ERROR: No fue ingresado un archivo .mio");
    }
    
    return 0;
}