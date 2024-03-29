// NOTA: Para evitar errores inesperados
// NO MODIFICAR ninguna de las funciones de este archivo.


#include "lexer.h" // Funciones del analizador léxico.

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


/*  
 * DESCRIPCIÓN:
 * Esta función calcula el valor decimal de un número 
 * octal dada una cadena que sea un número.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 *          (string) que represente 
 *          un número en base octal.
 * 
 * SALIDA: Un long long en base decimal.
 *  
 */
long long OctADec(char *numero)
{
    // Si se encuentra un número que no debería de estar, se arroja el error:
    if(strchr(numero, '8') || strchr(numero, '9'))
    {
        printf("Error! El número ingresado no es está en base octal.\n");
        exit(1);
    }

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


/*  
 * DESCRIPCIÓN:
 * Esta función halla la cantidad de líneas de un 
 * texto dentro de un archivo.
 * 
 * ENTRADA: Un puntero a un archivo.
 * 
 * SALIDA: Un número entero (int).
 *  
 */
int __contarLineasArchivo(FILE *archivo)
{
    int numero_lineas = 0;
    char c; // Almacena el carácter leído del archivo.

    // Si el archivo no existe:
    if (!archivo)
    {
        printf("ERROR: No se pudo abrir el archivo");
        return -1;
    }

    // Se extra el primer carácter de cada línea y se guarda en c:
    for(c = getc(archivo); c != EOF; c = getc(archivo))
    {
        if(c == '\n') // Si hay un salto de línea se incrementa el contador.
            numero_lineas++;
    }

    printf("La cantidad de lineas es: %d\n", numero_lineas+1);
    return numero_lineas+1; // Se retorna la cantidad de líneas del archivo.
}


/*  
 * DESCRIPCIÓN:
 * La función almacena las líneas del archivo dentro 
 * de un vector y retorna la cantidad de espacios en
 * blanco que hay al principio de la línea.
 * 
 * ENTRADA: Un puntero a un archivo, dos unsigned int
 *          (dimensiones del arrreglo) y un arreglo
 *          estático de dos dimensiones.
 * 
 * SALIDA: N/A.
 *  
 */
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned int caracteres, char cadena[lineas][caracteres])
{
    unsigned int i = 0;

    while(i < lineas)
    {
        // Se guarda la línea del archivo en el arreglo:
        if(fgets(cadena[i], sizeof(cadena[i]), archivo) != NULL)
        {
            // Se cambia el carácter '\n' por '\0';
            if(cadena[i][strlen(cadena[i])-1] == '\n')
                cadena[i][strlen(cadena[i])-1] = '\0';

            // Si hay espacios al principio de la línea:
            if(cadena[i][0] == ' ')
            {   
                unsigned int tam = strlen(cadena[i]); // Tamaño de la cadena.
                unsigned int espacios = strspn(cadena[i], " "); // Cantidad de espacios en blanco al principio.

                // Se mueve la memoria:
                memmove(cadena[i], cadena[i]+espacios, tam);
                //cadena[i][--tam] = 0; // Se vuelven '\0' los char finales.
                //printf("[%s]\n", cadena[i]);
            }
        }
        i++;
    }
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es una
 * palabra reservada.
 * 
 * Palabras reservadas: PROGRAMA, FINPROG, SI,
 *                      ENTONCES, SINO, FINSI,
 *                      REPITE, VECES FINREP, 
 *                      IMPRIME, LEE.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esReservada(char *cadena)
{
    unsigned int i = 0;
    char *palabras_reservadas[11] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

    // Se verifica si es una palabra reservada:
    while(i < 11)
    {
        // Si es una palabra reservada:
        if(strncmp(cadena, palabras_reservadas[i], strlen(cadena)) == 0)
        {   
            return (0);
        }
        i++;
    }

    // Si no es una palabra reservada:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es un
 * símbolo de asignación: =.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esAsig(char *cadena)
{
    // '=' == 61 en ASCII.

    // Se verifica si es una asignación:
    if (*cadena == 61)
        return (0);
    
    // Si no es asignación:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es un
 * símbolo.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es un
 * operador aritmético.
 * 
 * Operadores aritméticos: +, -, *, /.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esOpAr(char *cadena) 
{ 
    unsigned int i = 0;
    char *op_ar[4] = {"+","-","*","/"};

    // Se verifica si es un operador aritmético:
    while(i < 4)
    {
        // Si es un operador aritmético:
        if(strncmp(cadena, op_ar[i], strlen(cadena)) == 0)
        {       
            return (0); 
        }
        i++;
    }
    
    // Si no es un operador aritmético:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es un
 * número.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esNum(char *cadena)
{
    // Si el primer char es un número:
    if(isdigit(*cadena) != 0)
    {
        char *tmp = cadena;

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

    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es un
 * operador relacional.
 * 
 * Operadores relacionales: <, >, ==.
 *
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esOpRel(char *cadena)
{
    unsigned int i = 0;
    char *op_rel[3] = {"<", ">", "=="};

    // Se verifica si es un operador relacional:
    while(i < 3)
    {
        if(strncmp(cadena, op_rel[i], strlen(op_rel[i])) == 0)
        {       
            return (0); 
        }
        i++;
    } // Fin while

    // Si no es un operador relacional:
    return (1);      
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es el símbolo
 * de un comentario: #.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esComentario(char *cadena)
{
    // '#' == 35 en ASCII.

    // Si es comentario:
    if(*cadena == 35)
        return (0);

    // Si no es comentario:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento son unas
 * comillas dobles: ".
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esComilla(char *cadena)
{
    // '\"' == 34 en ASCII,

    // Si es una comilla:
    if(*cadena == 34)
        return (0);

    // Si no es una comilla:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es una
 * una cadena de texto (string) aceptada
 * por el lenguaje MIO.
 * 
 * ENTRADA: Un puntero de tipo char (cadena) del token,
 *          un unsigned int (número de línea de la sentencia).
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esTexto(char *token, unsigned int num_linea)
{
    // Si es una cadena de texto:
    // EN ASCII:
    // '"' = 34
    // '\' = 92
    if(*token == 34 && *(token+strlen(token)-1) == 34 && *(token+strlen(token)-2) != 92)
        return (0);
    
    // Se verifica que tanto al inicio como al final de la cadena de texto hayan comillas "...":
    unsigned int i;
    for(i = 0; i < strlen(token); ++i)
    {
        if(*(token+i) == '\\' && *(token+i+1) == '\"')
            i++; // Continúa después de la comilla.
        else if(*(token+i) == '\"')
            return 0;
    }

    // Hubo error:
    fprintf(stdout,"ERROR en línea: [%u] --Se esperaba carácter terminal --> \" en %s\n\n", num_linea, token);

    // No es una cadena de texto:
    return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es una
 * variable válida del lenguaje MIO.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esVarValid(char *cadena)
{
    // Se verifica que no se trate de una palabra reservada:
    if(__esReservada(cadena) == 0)
        return (1);

    // Si la cadena comienza con una letra:
    if (isalpha(*cadena) != 0)
    {  
        // Se valida si es un nombre de variable correcto:
        char *tmp = cadena;
        
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es una
 * variable.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esVariable(char *cadena)
{
    if(__esReservada(cadena) == 0)
        return (1);
    
    else if(__esVarValid(cadena) == 0)
        return (0);
    
    else
        return (1);
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicia el análisis léxico 
 * identifica el tipo de componente léxico 
 * de acuerdo al carácter con el que comienza 
 * la cadena y retorna un carácter indicando el 
 * tipo de componente léxico del que se trate.
 * 
 * TIpos de componentes léxicos:
 *      R: palabra reservada.
 *      V: variable válida.
 *      v: variable no válida.
 *      N: número.
 *      n: variable no válida (inicia con número)
 *      #: comentario.
 *      r: operador relacional. 
 *      a: operador aritmético.
 *      A: asignación.
 *      C: comilla.
 *      s: variable no válida (comienza con símbolo).
 *      S: símbolo.             
 * 
 * ENTRADA: Un puntero de tipo char (cadena) del token,
 *          un unsigned int (número de línea de la sentencia).
 * 
 * SALIDA: Un carácter (char).
 * 
 */
char __identifica(char *token, unsigned int num_linea)
{
    if(!token)
        return 'e';

    if(isalpha(*token) != 0)
    {
        if(__esReservada(token) == 0)
            return 'R'; // Palabra reservada.
        else
        {
            if(__esVarValid(token) == 0)
                return 'V'; // Variable válida.
            else
                return 'v'; // Es variable, pero no válida. Pues tiene algún símbolo raro dentro de la variable.
        }
        
    }
    else
    {
        if(isdigit(*token) != 0)
        {
            if(__esNum(token) == 0)
                return 'N'; // Número.
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

            else if(strlen(token) > 2 && isalpha(*(token+1)) != 0)
                return 's'; // Es variable que comienza con un símbolo.

            else
                return 'S'; // Es uno o son varios símbolos.
        }
    } 
    return 'e'; // Hubo error. 
}


/* 
 * DESCRIPCIÓN:
 * Esta función obtiene el token de tipo
 * cadena (string) aceptada por el lenguaje
 * MIO a partir de una cadena de texto y
 * lo retorna.
 * 
 * ENTRADA: Un puntero a una cadena de chars
 * 
 * SALIDA: Un puntero de tipo char (cadena) al token.
 * 
 */
char *tokenCadena(char *cadena)
{
    char *token, *tmp;

    tmp = cadena;

    // " == 34 en ASCII.
    // espacio == 32 en ASCII.

    // Se recorre la cadena:
    unsigned int i = 1; // Indicador del tamaño de la cadena a copiar.

    while(*tmp != '\0' || *tmp != '\n')
    {
        tmp++; // Se corre el apuntador al siguiente char.
        i++; // Se aumenta el tamaño de la cadena.
        
        // Si el char actual de tmp es una comilla, entonces se rompe:
        if(*tmp == '\"' || (*tmp == '\"' && *(tmp+1) == '\0'))
        { 
            break;
        }
    }

    // Se copia copia el pedazo de la cadena que va de 0 a i:
    token = malloc(i * sizeof(char));
    strncpy(token, cadena, i);
    
    //printf("EL TOKEN ES: %s", token);
    return token;
}


/* 
 * DESCRIPCIÓN:
 * Esta función guarda en una lista 
 * (listaVarNum, listaText, listaVal)
 * el token de una variable, cadena de texto o valor
 * en su respectivo tipo de lista e imprime en el
 * archivo .lex la representación del tipo de token.
 * 
 * Tipos de representación: 
 *      [id] IDxx: variable numérica (identificador).
 *      [txt] TXxx: cadena de texto (string).
 *      [val]: número (valor). 
 * 
 * ENTRADA: Un puntero a un archivo .lex, 
 *          un char tipo de identificador),
 *          un puntero a la cadena del token,
 *          un puntero a una lista tipo listaVarNum,
 *          un puntero a una lista tipo listaText,
 *          un puntero a una lista tipo listaVal.
 * 
 * SALIDA: N/A.
 * 
 */
void impTokLex(FILE *archivo_lex, char ident, char *token, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
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
            // Se imprime en el archivo .lex:
            fprintf(archivo_lex, "[id] ID%02u\n", nodo->ID);
        }

        // Si el nodo no existe:
        else
        {   
            // Se aumenta el contador de variables numéricas:
            cont_var++;

            // Se crea el nodo y se ingresa a la lista:
            nodo = creaNodoVarNum(token, cont_var);
            pushBackVarNum(lista_vars, nodo);

            // Se imprime en el archivo .lex:
            fprintf(archivo_lex, "[id] ID%02u\n", nodo->ID);
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

        // Se imprime en el archivo .lex:
        fprintf(archivo_lex, "[txt] TX%02u\n", nodo->ID);
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

        // Se imprime en el archivo .lex:
        fprintf(archivo_lex, "[val]\n");
    }
}


/* 
 * DESCRIPCIÓN:
 * Esta función imprime las 3 listas en el 
 * archivo .sim
 * 
 * ENTRADA: Un puntero a un archivo .sim,
 *          un puntero a una lista tipo listaVarNum,
 *          un puntero a una lista tipo listaText,
 *          un puntero a una lista tipo listaVal.
 * 
 * SALIDA: N/A.
 * 
 */
void imprimeSim(FILE *archivo_sim, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
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
        fprintf(archivo_sim, "%d, %lld\n", cont3->valor_octal, cont3->valor_decimal);
        cont3 = cont3->sig;
    }

}


/* 
 * DESCRIPCIÓN:
 * Esta función obtiene un token (cadena) según el
 * tipo de componenete léxico identificado por
 * la función __identifica y lo retorna.
 * 
 * ENTRADA: Un puntero a un archivo .lex,
 *          un puntero a una cadena,
 *          un unsigned int (número de línea de la sentencia),
 *          un puntero a una lista tipo listaVarNum,
 *          un puntero a una lista tipo listaText,
 *          un puntero a una lista tipo listaVal.
 * 
 * SALIDA: Puntero a una cadena.
 * 
 */
char *genTok(FILE *archivo_lex, char *cadena, unsigned int num_linea, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores)
{
    // Se crea un arreglo dinámico del tamaño de la cadena:
    char *copia_lex = malloc(strlen(cadena)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena para generar el lexema:
    strncpy(copia_lex, cadena, strlen(cadena)+1);

    // Se crea otro arreglo dinámico del tamaño de la cadena:
    char *copia = malloc(strlen(cadena)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena:
    strncpy(copia, cadena, strlen(cadena)+1);

    // Se genera la unidad léxica a verificar:
    char *aux = NULL;  // Variable auxiliar para la función strtok_r.
    char *lexema; // Puntero al token que pasará por la función __Identifica.

    // Se genera el puntero del lexema:
    lexema = strtok_r(copia_lex, " \t\n", &aux);


    // Se identifica el tipo de unidad léxica:
    char ident = __identifica(lexema, num_linea);
    
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
        break;

        // Es variable válida:
        case 'V':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
        break;

        // Es variable que contiene símbolos:
        case 'v':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(stdout, "ERROR en línea: [%u] --La variable contiene caracteres no válidos: %s\n", num_linea, ptr_strok);
        break;

        // Es variable que comienza con un número:
        case 'n':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(stdout, "ERROR en línea: [%u] --La variable comienza con un número: %s\n", num_linea, ptr_strok);
        break;

        // Es variable  que comienza con un símbolo:
        case 's':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(stdout,"ERROR en línea: [%u] --La variable comienza con un carácter no válido: %s\n", num_linea, ptr_strok);
        break;

        // Es un número
        case 'N':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
        break;

        // Es un operador aritmético:
        case 'a':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(archivo_lex, "[op_ar]\n"); // Se imprime en el archivo .lex
        break;

        // Es un operador relacional:
        case 'r':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(archivo_lex, "[op_rel]\n"); // Se imprime en el archivo .lex
        break;

        // Es asginación:
        case 'A':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
        break;

        // Es cadena:
        case 'C':
            // Se genera token con la copia:
            ptr_strok = tokenCadena(copia);

            // Se valida que la cadena sea un token válido:
            __esTexto(ptr_strok, num_linea);
        break;

        // Es símbolo:
        case 'S':
            // Se genera token con la copia:
            ptr_strok = strtok_r(copia, " \n\t", &aux);
            fprintf(stdout,"ERROR en línea: [%u] --Símbolo o cadena de símbolos no válida: %s\n", num_linea, ptr_strok);
        break;

        // Hubo error:
        case 'e':
            fprintf(stdout, "Hubo un error en la obtención del token.\n");
        break;
    }

    // Se crea un arreglo dinámico del tamaño de la cadena:    
    char *token = malloc(strlen(ptr_strok)+1 * sizeof(char));

    // Se genera una copia dinámica de la cadena:
    strncpy(token, ptr_strok, strlen(ptr_strok)+1);    

    // Se imprime la palabra reservada o la asignación en el archivo .lex:
    if(ident == 'R' || ident == 'A')
         fprintf(archivo_lex, "%s\n", ptr_strok); // Se imprime en el archivo .lex

    // Se imprime el token de la lista correspondiente en el archivo .lex:
    impTokLex(archivo_lex, ident, token, lista_vars, lista_cadenas, lista_valores);

    // Se apunta el puntero de lexema a NULL:
    lexema = NULL;

    // Se libera la memoria de las copias creadas:
    free(copia);
    copia = NULL;

    free(copia_lex);
    copia_lex = NULL;

    return token;
}


/* 
 * DESCRIPCIÓN:
 * Esta función crea las cadenas para obtener los tokens
 * a través de la función genTok e inicia el proceso
 * de análisis léxico por línea.
 * Identifica si hay una o más unidades léxicas en la
 * línea.
 * 
 * ENTRADA: Un puntero a un archivo .lex,
 *          dos unsigned int (dimensiones del arreglo),
 *          un arreglo estático de dos dimensiones,
 *          un puntero a una lista tipo listaVarNum,
 *          un puntero a una lista tipo listaText,
 *          un puntero a una lista tipo listaVal.
 * 
 * SALIDA: N/A.
 * 
 */
void analizador(FILE *archivo_lex, unsigned int lineas, unsigned int chars, char cadena[lineas][chars], listaVarNum *lista_vars, listaText *lista_strs, listaVal *lista_vals)
{
    unsigned int i; 

    // Se recorre cada línea:
    for(i = 0; i < lineas; i++)
    {
        // Se ignora la línea si es un comentario o una línea en blanco:
        if(__esComentario(cadena[i]) == 0 || cadena[i][0] == '\0' || cadena[i][0] == '\n')
            // Se pasa a la siguiente línea:
            continue;
        else if(strlen(cadena[i]) == 4 && (strncmp(cadena[i], "    ", 4) == 0 || cadena[i][0] == '\t'))
            continue;

        // Se imprime el primer número de línea en el archivo:
        fprintf(archivo_lex,"~%u\n", i+1);

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

        // Se genera una copia dinámica de la cadena a partir del primero carácter que no sea espacio:
        strncpy(copia, cadena[i]+espacios, strlen(cadena[i]) - (espacios) + 1);

        // Se genera el primer token:
        char *token;
        token = genTok(archivo_lex, copia, i+1, lista_vars, lista_strs, lista_vals);
        
        // Si sólo hay un token en la línea:
        if(strlen(token) == strlen(cadena[i]))
        {
            
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
                // Si al final de la línea sólo hay espacios:
                if(strspn(ptr," ") == strlen(ptr))
                    break; // Se rompe el while
                
                // Se genera el siguiente token de la línea:
                token = genTok(archivo_lex, ptr, i+1, lista_vars, lista_strs, lista_vals);
                
                // Se genera el último o único token en la línea:
                if(strlen(token) == strlen(ptr))
                {
                    //printf("\n\n");

                    // Se libera la memoria del token:
                    free(token);
                    token = NULL;

                    break; // Se rompe el ciclo.
                }

                // Se apunta a la siguiente unidad léxica de la cadena
                // (la siguiente porción de la cadena):
                ptr = ptr + strlen(token) + 1;

                // Se libera la memoria del token:
                free(token);
                token = NULL;
            } // Fin while
        } // Fin else

        // Se libera el espacio ocupado por copia:
        free(copia);
        copia = NULL;

    } // Fin for
}

