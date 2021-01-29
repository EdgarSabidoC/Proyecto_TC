#include "sintax.c"

/*
 * DESCRIPCIÓN: 
 * Función principal que controla al analizador.
 * Aquí se realizan los llamados a las funciones
 * del analizador sintáctico y se inicializa
 * la lista donde se guardarán los tokens.
 * 
 * ENTRADA: String con el nombre del archivo .lex
 * 
 * SALIDA: Resultado de la compilación:
 *  EXIT_SUCCES - Compilación exitosa.
 *  EXIT_FAILURE - Fallo en la compilación.
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
    char *lex = ".lex";

    if(strncmp(punto, lex, sizeof(".lex")))
    {
        printf("ERROR, no se encontró archivo .lex\n\n");
        return EXIT_FAILURE;
    }

    // Se declara e inicializa la lista:
    listaTok lista;
    iniListaTok(&lista);

    // Punteros al archivo .lex:    
    FILE *arch_lex = fopen(argv[1], "r");
    
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
        return EXIT_FAILURE;
    }
    else if(errores == 1)
    {
        printf("\n\nERROR DURANTE LA COMPILACIÓN:\n");
        printf("Se encontró %u error.\n", errores);
        return EXIT_FAILURE;
    }
    
    // Finalización exitosa del programa:
    printf("¡COMPILACIÓN EXITOSA!\n");
    return EXIT_SUCCESS;
}