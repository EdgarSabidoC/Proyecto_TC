// Programa principal del analizador sintático.

// Biblioteca con las funciones del analizador sintáctico:
#include "sintax.h"

/*
 * DESCRIPCIÓN: 
 * Función principal que controla al analizador.
 * Aquí se realizan los llamados a las funciones
 * del analizador sintáctico y se inicializa
 * la lista donde se guardarán los tokens.
 * 
 * ENTRADA: Cadena (string) con el nombre del archivo .lex
 * 
 * SALIDA: Resultado de la compilación:
 *          EXIT_SUCCESS - Compilación exitosa.
 *          EXIT_FAILURE - Fallo en la compilación.
 * 
 */
int main(int argc, char **argv)
{
    // Falla el programa si no se le pasa
    // el nombre del archivo .lex:
    if (argc <= 1)
        return EXIT_FAILURE;

    // Se verifica que el archivo sea extensión .lex:
    char *punto = strchr(argv[1], '.');

    // Se verifica si la extensión es .lex
    if(strncmp(punto, ".lex", strlen("lex")) != 0)
    {
        printf("\n\nERROR: no se encontró archivo .lex\n\n");
        printf("\nEl analizador sintáctico ha finalizado inesperadamente.\n\n\n");

        return EXIT_FAILURE;
    }

    // Punteros al archivo .lex:    
    FILE *arch_lex = fopen(argv[1], "r");
    
    printf("\n\n\tArchivo: %s\n\n", argv[1]);

    // Se verifica que exista el archivo:
    if(!arch_lex)
    {
        printf("ERROR: El archivo [%s] no existe.\n\n", argv[1]);
        printf("\nEl analizador sintáctico ha finalizado inesperadamente.\n\n\n");

        arch_lex = NULL;

        return EXIT_FAILURE;
    }

    // Se declara e inicializa la lista:
    listaTok lista;
    iniListaTok(&lista);

    // Se guardan los tokens del archivo dentro de la lista:
    guardarTokens(arch_lex, &lista);

    // Puntero auxiliar para recorrer la lista:
    nodo_Tok *nodo = lista.raiz;

    // Se imprime el contenido de la lista:
    while(nodo)
        nodo = nodo->sig;

    // Se inicia el analizador sintáctico con la lista:
    unsigned int errores; // Número de errores.
    errores = iniAnalSin(&lista);

    if(errores > 1)
    {
        printf("\n\nERROR DURANTE LA COMPILACIÓN:\n");
        printf("Se encontraron %u errores.\n", errores);
        printf("\n\nLa compilación se ha detenido inesperadamente.\n\n");
        return EXIT_FAILURE;
    }
    else if(errores == 1)
    {
        printf("\n\nERROR DURANTE LA COMPILACIÓN:\n");
        printf("Se encontró %u error.\n", errores);
        printf("\n\nLa compilación se ha detenido inesperadamente.\n\n");
        return EXIT_FAILURE;
    }
    
    // Finalización exitosa del programa:
    printf("********¡COMPILACIÓN EXITOSA!********\n\n\n");
    return EXIT_SUCCESS;
}