#include "lexer.h" // Funciones del analizador léxico.
#include <math.h>

/*  

TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO

 operadores relacionales: ">", "<", "=="

 operadores aritméticos: '+', '-', '*', '/'

 asignacion: '='

*/

// Contadores globales:

/* Contador de variables numéricas */
unsigned int cont_var = 0;

/* Contador de variables de texto */
unsigned int cont_txt = 0;


//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------


/* Genera un archivo ,Lex con el nombre del programa .mio */
void generarSim(char *cadena, char *nombre_programa)
{
    
}


/* Calcula el valor decimal de un número octal dada una cadena que sea un número */
long long OctADec(char *numero)
{
    // La cadena se convierte en número:
    int octal = atoi(numero);
    
    int decimal = 0;
  
    // Se inicializa el valor de la base de 1 que es 8^0:
    int base = 1; 
    
    // Variable temporal:
    int temp = octal; 
    
    while (temp) 
    { 
        // Se extrae el último dígito:
        int ultimo_digito = temp % 10; 
        temp = temp / 10; 

        // Se multiplica el último dígito con el valor
        // de la base correcto y se añade al valor decimal
        decimal += ultimo_digito * base; 
  
        base = base * 8; 
    } 

    // Se retorna el decimal:
    return decimal;
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


/* 
    La función almacena las líneas del archivo dentro de un vector 
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
int __esReservada(char *cadena)
{
    unsigned int i = 0;
    char *palabras_reservadas[11] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

    // Se verifica si es una palabra reservada:
    while(i < 11)
    {
        // Si es una palabra reservada:
        if(strncmp(cadena, palabras_reservadas[i], sizeof(palabras_reservadas[i])) == 0)
        {   
            return (0);
        }
        i++;
    }

    // Si no es una palabra reservada:
    return (1);
}


/* Valida si la cadena es una ASIGNACIÓN */
int __esAsig(char *cadena)
{
    // '=' == 61 en ASCII.

    // Se verifica si es una asignación:
    if (*cadena == 61)
        return (0);
    
    // Si no es asignación:
    return (1);
}


/* Valida si la cadena es un SÍMBOLO */
int __esSimbol(char *token)
{
    // Se verifica si el char es una letra o un número:
    if(isalpha(*token) != 0 || isdigit(*token) != 0)
    {
        return (1);
    }

    // Si es un símbolo:
    return (0);

}


/* Valida si la cadena es un OPERADOR ARITMÉTICO. */
int __esOpAr(char *cadena) 
{ 
    unsigned int i = 0;
    char *op_ar[4] = {"+","-","*","/"};

    // Se verifica si es un operador aritmético:
    while(i < 4)
    {
        // Si es un operador aritmético:
        if(strncmp(cadena, op_ar[i], sizeof(op_ar[i])) == 0)
        {       
            return (0); 
        }
        i++;
    }
    
    // Si no es un operador aritmético:
    return (1);
}


/* Valida si la cadena es un NÚMERO */
int __esNum(char *token)
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
            return (0);
        }

        // Si no es un número
        return (1);
    }
}


/* Valida si la cadena es un OPERADOR RELACIONAL */
int __esOpRel(char *cadena)
{
    unsigned int i = 0;
    char *op_rel[3] = {"<", ">", "=="};

    // Se verifica si es un operador relacional:
    while(i < 3)
    {
        if(strncmp(cadena, op_rel[i], sizeof(op_rel[i])) == 0)
        {       
            return (0); 
        }
        i++;
    } // Fin while

    // Si no es un operador relacional:
    return (1);      
}


/* Verifica si el caracter es un '#' COMENTARIO */
int __esComentario(char *cadena)
{
    // '#' == 35 en ASCII.

    // Si es comentario:
    if(*cadena == 35)
        return (0);

    // Si no es comentario:
    return (1);
}


/* Valida si el caracter es una COMILLA */
int __esComilla(char *cadena)
{
    // '\"' == 34 en ASCII,

    // Si es una comilla:
    if(*cadena == 34)
        return (0);

    // Si no es una comilla:
    return (1);
}


/* Valida si la cadena es un string */
int __esTexto(char *token, unsigned int num_linea)
{
    // Se verifica si es una palabra reservada:

    // Si es una cadena de text0:
    if(*token == '\"')
    {
        return (0);    
    }
    
    // No es una cadena de texto:
    return (1);
}


/* Valida si la cadena es una variable válida */
int __esVarValid(char *token)
{
    // Se verifica que no se trate de una palabra reservada:
    if(__esReservada(token) == 0)
        return (1);

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
            return (0); 
        }
        
        // Si el char al que apunta tmp es un símbolo:
        return (1);
    }

    // Si no es una variable válida:
    return (1);
}


/* Valida si la cadena se trata de una variable */
int __esVariable(char *token)
{
    if(__esReservada(token) == 0)
        return (1);
    
    else if(__esVarValid(token) == 0)
        return (0);
    
    else
        return (1);
    
}


/* Identifica el tipo de unidad léxica */
char __Identifica(char *token, unsigned int num_linea)
{
    if(isalpha(*token) != 0)
    {
        if(__esReservada(token) == 0)
            return 'R';
        else
        {
            if(__esVarValid(token) == 0)
                return 'V';
            else
                return 'v'; // Es variable, pero no válida. Pues tiene algún símbolo raro dentro de la variable.
        }
        
    }
    else
    {
        if(isdigit(*token) != 0)
        {
            if(__esNum(token) == 0)
                return 'N';
            else
                return 'n'; // Es una variable que comienza con un número. Error.
        }
        
        else if(__esSimbol(token) == 0)
        {
            if(__esComentario(token) == 0)
                return '#'; // Es comentario.

            else if(__esOpRel(token) == 0)
                return 'r'; // Es operador relacional.
            
            else if(__esOpAr(token) == 0)
                return 'a';
            
            else if(__esAsig(token) == 0)
                return 'A'; // Es asignación.
            
            else if(__esComilla(token) == 0)
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


/* Guarda en una lista el token y lo imprime en el archivo .lex */
void impTokLex(char ident, char *token, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
{
    // Si es una variable:
    if(ident == 'V')
    { 
        // Puntero a un nodo de variable;
        nodo_VarNum *nodo;

        // Se busca el nodo en la lista:
        nodo = buscaVarNum(lista_vars, token);

        // Si el nodo ya existe:
        if (nodo)
        {
            // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
        }

        // Si el nodo no existe:
        else
        {   
            // Se aumenta el contador de variables numéricas:
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
        // Aumenta el contador de cadenas de texto:
        cont_txt++;
        
        // Puntero a un nodo de cadena de texto;
        nodo_Txt *nodo;

        // Se crea el nodo y se ingresa en la lista:
        nodo = creaNodoText(token, cont_txt);
        pushBackTxt(lista_cadenas, nodo);

        // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
    }

    // Si es un valor numérico
    else if (ident == 'N')
    {
        // Puntero a un nodo de variable;
        nodo_Val *nodo;

        // Se obtiene el valor decimal del número:
        long long token_decimal = OctADec(token);

        // Se obtiene el valor octal del token:
        int token_octal = atoi(token);
            
        // Se crea el nodo y se ingresa en la lista:
        nodo = creaNodoVal(token_octal, token_decimal);
        pushBackVal(lista_valores, nodo);

        // SE TIENE QUE IMPRIMIR EN EL ARCHIVO .LEX
    }
}


/* Retorna un token obtenido en la línea */
char *genTok(char *cadena, unsigned int num_linea, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
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

    // Se imprime el token de la lista correspondiente en el archivo .lex:
    impTokLex(ident, token, lista_vars, lista_cadenas, lista_valores);

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
void anaLex(unsigned int lineas, unsigned int chars, char cadena[lineas][chars], listaVarNum *lista_vars, listaText *lista_strs, listaVal *lista_vals)
{
    unsigned int i; 

    // Se recorre cada línea:
    for(i = 0; i < lineas; i++)
    {
        // Se ignora la línea es un comentario:
        if(__esComentario(cadena[i]) == 0)
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
        token = genTok(copia, i+1, lista_vars, lista_strs, lista_vals);

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
                token = genTok(ptr, i+1, lista_vars, lista_strs, lista_vals);

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


/* Se imprimen las listas en el archivo .sim */
void impSim(FILE *archivo_sim, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
{
    // Se imprimen las listas en el archivo .sim:

    // Se imprime la lista de variables:
    fprintf(archivo_sim,"IDS\n");

    nodo_VarNum *cont = lista_vars->raiz;
    while(cont)
    {
        fprintf(archivo_sim, "%s, ID%02u\n", cont->nombre, cont->ID);
        cont = cont->sig;
    }
    
    // Se imprime la lista de cadenas de texto:    
    fprintf(archivo_sim, "\nTXT\n");

    nodo_Txt *cont2 = lista_cadenas->raiz;
    while(cont2)
    {
        fprintf(archivo_sim,"%s, TX%02u\n", cont2->cadena, cont2->ID);
        cont2 = cont2->sig;
    }

    // Se imprime la lista de valores:
    fprintf(archivo_sim, "\nVAL\n");

    nodo_Val *cont3 = lista_valores->raiz;
    while(cont3)
    {
        fprintf(archivo_sim, "%d, %ld\n", cont3->valor_octal, cont3->valor_decimal);
        cont3 = cont3->sig;
    }

}

/* Función principal */
int main(int argc, char **argv)
{   
    // Si el programa no tiene la cantidad de argumentos correctos:
    if (argc <= 1 || argc > 2)
    // Falló al correr el programa:
        return 1;
    
    // Se verifica que el archivo sea extensión .mio:
    char *punto = strchr(argv[1], '.');
    char *mio = ".mio";

    // Se verifica que la extensión sea .mio
    if(strncmp(punto, mio, sizeof(".mio")))
    {
        printf("ERROR, no se encontró archivo .mio\n\n");
        return 1;
    }

    // Puntero al nombre del programa:
    char *nombre_programa = argv[1];
        
    printf("%s\n", nombre_programa);

    // Archivo .lex:
        
    // Nombre del archivo .lex:
    char nombre_lex[strlen(argv[1])+1];
    strncpy(nombre_lex, argv[1], strlen(argv[1])-3);
    strcat(nombre_lex, "lex");

    printf("%s\n", nombre_lex);

    // Se crea el archivo .lex:
    FILE *lexer = fopen(nombre_lex, "a+");
        
    // Archivo .sim:
        
    // Nombre del archivo .sim:
    char nombre_sim[strlen(argv[1])+1];
    strncpy(nombre_sim, argv[1], strlen(argv[1])-3);
    strcat(nombre_sim, "sim");

    printf("%s\n", nombre_sim);

    // Se crea el archivo .sim:
    FILE *sim = fopen(nombre_sim, "a+");

    // Se inicializan las listas para almacenar la tabla de símbolos.
    listaVarNum lista_var;
    listaText lista_txt;
    listaVal lista_val;

    iniListaVarNum(&lista_var);
    iniListaTxt(&lista_txt);
    iniListaVal(&lista_val);

    // Se cuenta la cantidad de líneas del archivo .mio:
    FILE *archivo = fopen(argv[1], "r");
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
    anaLex(lineas, caracteres, array, &lista_var, &lista_txt, &lista_val);

    // Se imprimen las listas en el archivo .sim:
    impSim(sim, &lista_var, &lista_txt, &lista_val);

    // Se libera la memoria ocupada por las listas:
    liberaListaVarNum(&lista_var);
    liberaListaTxt(&lista_txt);
    liberaListaVal(&lista_val);

    // Se cierra el archivo .lex y el archivo .sim:
    fclose(lexer);
    fclose(sim);

    // Programa exitoso:
    return 0;
}
