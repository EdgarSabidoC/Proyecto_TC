#include "sintax.c"

int main(int argc, char **argv)
{
    // Falla el programa:
    if (argc <= 1)
        return EXIT_FAILURE;

    // Se declara e inicializa la lista:
    listaTok lista;
    iniListaTok(&lista);

    // Punteros al archivo .lex:    
    FILE *lex_1 = fopen(argv[1], "r");
    FILE *lex_2 = fopen(argv[1], "r");
    
    // Se guardan los tokens del archivo dentro de la lista:
    guardarTokens(lex_1, lex_2, &lista);

    // Puntero auxiliar para recorrer la lista:
    nodo_Tok *nodo = lista.raiz;

    // Se imprime el contenido de la lista:
    while(nodo)
    {
        printf("Cadena: [%s] -- Num_linea[%u]\n", nodo->token, nodo->num_linea);
        nodo = nodo->sig;
    }
    printf("\n\n");

    // Se inicia el analizador sintáctico con la lista:
    unsigned int errores; // Número de errores.
    errores = iniAnalSin(&lista);

    if(errores > 1)
    {
        printf("Compilación no exitosa:\n");
        printf("Se encontraron %u errores.\n", errores);
        return EXIT_FAILURE;
    }
    else if(errores == 1)
    {
        printf("Compilación no exitosa:\n");
        printf("Se encontró %u error.\n", errores);
        return EXIT_FAILURE;
    }
    
    // Finalización exitosa del programa:
    printf("¡COMPILACIÓN EXITOSA!\n");
    return EXIT_SUCCESS;
}