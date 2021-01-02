#include "lexer.h" // Funciones del analizador léxico.
 // Funciones de las listas.

// VARIABLES

/* TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO */

// operadores relacionales: ">", "<", "=="

// operadores aritméticos: '+', '-', '*', '/'

// asignacion: '='

unsigned int cont_var = 0;
unsigned int cont_txt = 0;

//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------

/* Genera un archivo .lex e imprime una cadena en él */
void generarLexer(char *cadena, char *nombre_programa)
{

    FILE *lexer = fopen("Programa.lex", "a+");

    // Se imprime la cadena en el archivo .lex:
    fprintf(lexer, "%s", cadena);

    fclose(lexer);
}

/* Genera el archivo .sim e imprime en él */
void generarLex(char *cadena, char *nombre_programa)
{
    
}




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


/* La función almacena las líneas del archivo dentro de un vector 
    Retorna la cantidad de espacios en blanco que hay al principio de la línea.
*/
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned caracteres, char cadena[lineas][caracteres])
{
    unsigned int i = 0;

    while(1)
    {
        // Se guarda la línea del archivo en el arreglo:
        if(fgets(cadena[i], sizeof(cadena[i]), archivo) != NULL)
        {
            // Se cambia el caracter \n por \0;
            cadena[i][strlen(cadena[i])-1] = '\0';

            printf("%s\n", cadena[i]);
            i++;
        }

        // Si se llega al final del archivo:
        else
            break;
    }
}


/* Valida si la cadena es una palabra reservada */
bool __esReservada(char *cadena)
{
    unsigned int i = 0;
    char *palabras_reservadas[11] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

    // Se verifica si es una palabra reservada:
    while(i < 11)
    {
        // Si es una palabra reservada:
        if(strncmp(cadena, palabras_reservadas[i], sizeof(palabras_reservadas[i])) == 0)
        {   
            return (true);
        }
        i++;
    }

    // Si no es una palabra reservada:
    return (false);
}


/* Valida si la cadena es una ASIGNACIÓN */
bool __esAsig(char *cadena)
{
    // '=' == 61 en ASCII.

    // Se verifica si es una asignación:
    if (*cadena == 61)
        return (true);
    
    // Si no es asignación:
    return (false);
}


/* Valida si la cadena es un SÍMBOLO */
bool __esSimbol(char *token)
{
    // Se verifica si el char es una letra o un número:
    if(isalpha(*token) != 0 || isdigit(*token) != 0)
    {
        return (false);
    }

    // Si es un símbolo:
    return (true);

}


/* Valida si la cadena es un OPERADOR ARITMÉTICO. */
bool __esOpAr(char *cadena) 
{ 
    unsigned int i = 0;
    char *op_ar[4] = {"+","-","*","/"};

    // Se verifica si es un operador aritmético:
    while(i < 4)
    {
        // Si es un operador aritmético:
        if(strncmp(cadena, op_ar[i], sizeof(op_ar[i])) == 0)
        {       
            return (true); 
        }
        i++;
    }
    
    // Si no es un operador aritmético:
    return (false);
}


/* Valida si la cadena es un NÚMERO */
bool __esNum(char *token)
{
    // Si el primer char es un número:
    if(isdigit(*token) != 0)
    {
        char *tmp = token;

        // Se recorre toda la cadena:
        while(isdigit(*tmp) != 0)
        {
            tmp++;
        }

        // Si es un número:
        if(*tmp == '\0')
        {
            return (true);
        }

        // Si no es un número
        return (false);
    }
}


/* Valida si la cadena es un OPERADOR RELACIONAL */
bool __esOpRel(char *cadena)
{
    unsigned int i = 0;
    char *op_rel[3] = {"<", ">", "=="};

    // Se verifica si es un operador relacional:
    while(i < 3)
    {
        if(strncmp(cadena, op_rel[i], sizeof(op_rel[i])) == 0)
        {       
            return (true); 
        }
        i++;
    } // Fin while

    // Si no es un operador relacional:
    return (false);      
}


/* Verifica si el caracter es un '#' COMENTARIO */
bool __esComentario(char *cadena)
{
    // '#' == 35 en ASCII.

    // Si es comentario:
    if(*cadena == 35)
        return (true);

    // Si no es comentario:
    return (false);
}


/* Valida si el caracter es una COMILLA */
bool __esComilla(char *cadena)
{
    // '\"' == 34 en ASCII,

    // Si es una comilla:
    if(*cadena == 34)
        return (true);

    // Si no es una comilla:
    return (false);
}


/* Valida si la cadena es un string */
bool __esTexto(char *token, unsigned int num_linea)
{
    // Se verifica si es una palabra reservada:

    // Si es una cadena de text0:
    if(*token == '\"')
    {
        return (true);    
    }
    
    // No es una cadena de texto:
    return (false);
}


/* Valida si la cadena es una variable válida */
bool __esVarValid(char *token)
{
    // Se verifica que no se trate de una palabra reservada:
    if(__esReservada(token) == true)
        return (false);

    // Si el token comienza con una letra:
    if (isalpha(*token) != 0)
    {  
        // Se valida si es un nombre de variable correcto:
        char *tmp = token;
        
        // Se verifica que todos los caracteres de la cadena sean válidos:
        while(isalpha(*tmp) != 0 || isdigit(*tmp) != 0)
        {
            // El puntero se mueve al siguiente char:
            tmp++;

        } // Fin while
        
        // Si el char al que apunta tmp es nulo:
        if(*tmp == '\0' || *tmp == ' ')
        {   
            // Es una variable válida:
            return (true); 
        }
        
        // Si el char al que apunta tmp es un símbolo:
        return (false);
    }

    // Si no es una variable válida:
    return (false);
}


/* Valida si la cadena se trata de una variable */
bool __esVariable(char *token)
{
    if(__esReservada(token) == true)
        return (false);
    
    else if(__esVarValid(token) == true)
        return (true);
    
    else
        return (false);
    
}


/* Identifica el tipo de unidad léxica */
char __Identifica(char *token, unsigned int num_linea)
{
    if(isalpha(*token) != 0)
    {
        if(__esReservada(token) == true)
            return 'R';
        else
        {
            if(__esVarValid(token) == true)
                return 'V';
            else
                return 'v'; // Es variable, pero no válida. Pues tiene algún símbolo raro dentro de la variable.
        }
        
    }
    else
    {
        if(isdigit(*token) != 0)
        {
            if(__esNum(token) == true)
                return 'N';
            else
                return 'n'; // Es una variable que comienza con un número. Error.
        }
        
        else if(__esSimbol(token) == true)
        {
            if(__esComentario(token) == true)
                return '#'; // Es comentario.

            else if(__esOpRel(token) == true)
                return 'r'; // Es operador relacional.
            
            else if(__esOpAr(token) == true)
                return 'a';
            
            else if(__esAsig(token) == true)
                return 'A'; // Es asignación.
            
            else if(__esComilla(token) == true)
                return 'C'; // Es comilla.
            
            else if(strlen(token) > 2)
                return 's'; // Es variable que comienza con un símbolo.
            
            else
                return 'S'; // Es un símbolo:
            
        }
    }
        
}


/* Genera el token para cadenas */
char *tokenCadena(char *cadena)
{
    char *token, *tmp;
    
    tmp = cadena;

    unsigned int cont = 0;
    // " == 34 en ASCII.
    // espacio == 32 en ASCII.

    // Se recorre la cadena:
     while(*tmp != '\0' || *tmp != '\n')
    {
        if(strstr(tmp, "\"") || strstr(tmp, "\"\0"))
        { 
            break;
        }
        tmp++;
    }

    token = malloc(strlen(tmp) * sizeof(char));
    strcpy(token, tmp);
    
    //printf("EL TOKEN ES: %s", token);
    return token;
}


/* Retorna un token */
char *genTok(char *cadena, unsigned int num_linea, listaVarNum *lista_vars, listaText *lista_cadenas)
{
    if(!cadena)
        return 0;

    // Se crea un arreglo dinámico del tamaño de la cadena:
    char *copia_lex = malloc(strlen(cadena)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena para generar el lexema:
    strncpy(copia_lex, cadena, strlen(cadena)+1);

    // Se crea otro arreglo dinámico del tamaño de la cadena:
    char *copia = malloc(strlen(cadena)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena:
    strncpy(copia, cadena, strlen(cadena)+1);

    // Se genera la unidad léxica a verificar:
    char *aux;  // Variable auxiliar para la función strtok_r.
    char *lexema; // Puntero al token que pasará por la función __Identifica.
    
    // Se genera el puntero del lexema:
    lexema = strtok_r(copia_lex, " \n\t\0", &aux);
    
    // Se identifica el tipo de unidad léxica:
    char ident = __Identifica(lexema, num_linea);
    
    // Se apunta el aux a NULL para ser reutilizado:
    aux = NULL;

    // Puntero al token que se genere:
    char *ptr_strok;

    switch(ident)
    {
        // Es reservada:
        case 'R':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t\0", &aux);
        printf("Es reservada: ");
        break;

        // Es variable válida:
        case 'V':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es Variable: ");
        break;

        // Es variable que contiene símbolos:
        case 'v':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("ERROR en línea: [%u] --La variable contiene caracteres no válidos: ", num_linea);
        break;

        // Es variable que comienza con un número:
        case 'n':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("ERROR en línea: [%u] --La variable comienza con un número: ", num_linea);
        break;

        // Es variable  que comienza con un símbolo:
        case 's':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("ERROR en línea: [%u] --La variable comienza con un caracter no válido: ", num_linea);
        break;

        // Es un número
        case 'N':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es número: ");
        break;

        // Es un operador aritmético:
        case 'a':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es un operador aritmético: ");
        break;

        // Es un operador relacional:
        case 'r':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es un operador relacional: ");
        break;

        // Es asginació:
        case 'A':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es asignación: ");
        break;

        // Es cadena:
        case 'C':
        // Se genera token con la copia:
        //ptr_strok = strtok_r(copia, "\n\0", &aux);
        ptr_strok = tokenCadena(copia);
        printf("Es cadena: ");
        break;

        // Es símbolo:
        case 'S':
        // Se genera token con la copia:
        ptr_strok = strtok_r(copia, " \n\t", &aux);
        printf("Es símbolo: ");
        break;
    }

    // Se crea un arreglo dinámico del tamaño de la cadena:    
    char *token = malloc(strlen(ptr_strok)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena:
    strncpy(token, ptr_strok, strlen(ptr_strok)+1);    

    printf("[%s]\n", token);

    // Si es una variable:
    if(ident == 'V')
    { 
        // Puntero a un nodo de variable;
        nodo_VarNum *nodo;
        nodo = buscaVarNum(lista_vars, token);

        if (nodo)
        {
            // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
        }

        // Si el nodo no existe:
        else
        {   
            // Se aumenta el contador:
            cont_var++;

            // Se crea el nodo y se ingresa a la lista:
            nodo = creaNodoVarNum(token, cont_var);
            pushBackVarNum(lista_vars, nodo);

            // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
        }
        
    }

    // Si es cadena de texto:
    else if (ident == 'C')
    {
        // Puntero a un nodo de variable;
        nodo_Txt *nodo;
        nodo = buscaTxt(lista_cadenas, token);

        // Si existe el nodo:
        if(nodo)
        {
            // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
        }

        // Si el nodo no existe:
        else
        {
            nodo = NULL;

            // Aumenta el contado:
            cont_txt++;
            
            // Se crea el nodo y se ingresa en la lista:
            nodo = creaNodoText(token, cont_txt);
            pushBackTxt(lista_cadenas, nodo);

            // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
        } 
    }

    // Se apunta el puntero de lexema a NULL:
    lexema = NULL;

    // Se libera la memoria de las copias creadas:
    free(copia);
    copia = NULL;

    free(copia_lex);
    copia_lex = NULL;

    return token;
}


/* Analizador léxico, aquí se generan los tokens del programa y se imprimen en los archivos .lex y .sim */
void anaLex(unsigned int lineas, unsigned int chars, char cadena[lineas][chars], listaVarNum *lista_vars, listaText *lista_cadenas)
{
    unsigned int i; 

    // Se recorre cada línea:
    for(i = 0; i < lineas; i++)
    {
        // Se ignora la línea es un comentario:
        if(__esComentario(cadena[i]) == true)
        {
            // Se pasa a la siguiente línea:
            continue;
        }

        
        unsigned int espacios = 0; // Contador de los espacios en blanco.
        char *tmp = cadena[i]; // Puntero para recorrer la cadena.
        
        // Se cuentan los espacios en blanco al principio de la cadena:
        // espacio == 32 en ASCII.
        while(*tmp == 32)
        {
            espacios++;
            tmp++;
        }

        // Se crea un arreglo dinámico del tamaño de la cadena menos la cantidad de espacios al principio:
        char *copia = malloc((strlen(cadena[i])+1-(espacios)) * sizeof(char));

        // Se genera una copia dinámica de la cadena a partir del primero caracter que no sea espacio:
        strncpy(copia, cadena[i]+espacios, strlen(cadena[i]) - (espacios) + 1);

        // Se genera el primer token:
        char *token;
        token = genTok(copia, i+1, lista_vars, lista_cadenas);

        // Si sólo hay un token en la línea:
        if(strlen(token) == strlen(cadena[i]))
        {
            printf("\n\n");
            
            // Se libera la memoria del token:
            free(token);
            token = NULL;

            // Se continúa a la siguiente línea:
            continue;
        }

        // Si hay más de un token en la línea:
        else
        {
            // Puntero que apunta al resto de la cadena.
            char *ptr = copia;

            // Se apunta a la siguiente unidad léxica de la cadena
            // (la siguiente porción de la cadena):
            ptr = ptr + strlen(token) + 1;

            // Se libera la memoria del token:
            free(token);
            token = NULL;

            // Se generan el resto de tokens:
            while(*ptr != 10 && *ptr != 35 && *ptr != 0)
            {   
                
                // Se genera el siguiente token de la línea:
                token = genTok(ptr, i+1, lista_vars, lista_cadenas);

                // Se genera el último o único token en la línea:
                if(strlen(token) == strlen(ptr))
                {
                    printf("\n\n");

                    // Se libera la memoria del token:
                    free(token);
                    token = NULL;

                    break;
                }

                // Se apunta a la siguiente unidad léxica de la cadena
                // (la siguiente porción de la cadena):
                ptr = ptr + strlen(token) + 1;

                // Se libera la memoria del token:
                free(token);
                token = NULL;
            } // Fin while
        }
    } // Fin for
}


/* La función imprime un arreglo con las líneas del archivo */
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars])
{
    unsigned int i;

    for(i = 0; i < lineas; i++)
        printf("%s\n", arreglo[i]);
}


/* Función principal */
int main(int argc, char **argv)
{   
    if (argc>1)
    {
        char *punto = strchr(argv[1], '.');
        char *mio = ".mio";

        // Se verifica que la extensión sea .mio
        if(strncmp(punto, mio, sizeof(".mio")))
        {
            printf("ERROR, no se encontró archivo .mio\n\n");
            return -1;
        }

        // Puntero al nombre del programa:
        char *nombre_programa = argv[1];
        
        printf("%s\n", nombre_programa);

        //generarLex(NULL, nombre_programa);

        // Puntero al archivo:
        FILE *archivo = fopen(argv[1], "r");
        
        // Se inicializan las listas para almacenar la tabla de símbolos.
        listaVarNum lista_var;
        listaText lista_txt;

        iniListaVarNum(&lista_var);
        iniListaTxt(&lista_txt);

        // Se cuenta la cantidad de líneas del archivo:
        unsigned int lineas;
        lineas = __contarLineasArchivo(archivo);
        fclose(archivo); // Se cierra el archivo

        // Cantidad de caracteres máximos de cada archivo:
        unsigned int caracteres = 10000;

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
        anaLex(lineas, caracteres, array, &lista_var, &lista_txt);

        // Se genera el archivo .lex:
        //generarLexer(lineas, array);

        // Se imprime la última línea del archivo:
        //printf("\nEl numero de caracteres de la ultima linea es: %d", strlen(array[lineas-1]));
        

        // Se imprimen las listas:
        nodo_VarNum *cont = lista_var.raiz;
        printf("\n\nLista de variables:\n\n");
        while(cont)
        {
            printf("%s, ID%02u\n", cont->nombre, cont->ID);
            cont = cont->sig;
        }

        nodo_Txt *cont2 = lista_txt.raiz;
        
        printf("\n\nLista de cadenas de texto:\n\n");
        while(cont2)
        {
            printf("%s, TX%02u\n", cont2->cadena, cont2->ID);
            cont2 = cont2->sig;
        }

        // Se libera la memoria ocupada por las listas:
        liberaListaVarNum(&lista_var);
        liberaListaTxt(&lista_txt);
    }
    return 0;
}
