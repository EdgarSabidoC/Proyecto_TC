#include "listas.c"

// Contador global de errores del programa:
unsigned int num_errores = 0;

/* Cuenta la cantidad de líneas que hay en un archivo.
   
   Parámetros: Puntero a un archivo.
   
   Retorna: el número (int) de líneas que hay en el archivo.
   En caso de no encontrar el archivo, retorna -1.
*/
int __contarLineasArchivo(FILE *archivo)
{
    int numero_lineas = 0; // Contador del número de líneas del archivo.
    char c; // Almacena el caracter leído del archivo.

    // Si el archivo no existe o no se encuentra:
    if (!archivo)
    {
        printf("ERROR: No se pudo abrir el archivo.\n");
        return -1;
    }

    // Se extra el primer caracter de cada línea y se guarda en c:
    for(c = getc(archivo); c != EOF; c = getc(archivo))
        if(c == '\n') // Si hay un salto de línea se incrementa el contador.
            numero_lineas++;

    //printf("La cantidad de lineas es: %d\n", numero_lineas+1);
    return numero_lineas+1; // Se retorna la cantidad de líneas del archivo.
}


/* Crea una lista de los tokens del archivo .lex 
   en la lista no se guardan los toknes:
   "PROGRAMA", "[id] ID01" y "FINPROG" que
   son parte de la estructura principal del
   programa.

    Cierra los archivos que se le pasen como 
    argumento.

   También verifica que no falten los tokens
   principales de la estrucutra del programa:
   "PROGRAMA", "[id] ID01" y "FINPROG".
 */
void guardarTokens(FILE *arch_lex_1, FILE *arch_lex_2, listaTok *lista)
{
    // Contadores del número de líneas de los archivos .mio y .lex:
    unsigned int num_linea_mio = 0; // Número de línea del archivo .mio
    unsigned int num_linea_lex = 0; // Número de línea del archivo .lex
	unsigned int num_linea_fin_lex = 0; // Número de línea final del archivo .lex
	

    // Se cuenta la cantidad de líneas del archivo .lex:
	num_linea_fin_lex = __contarLineasArchivo(arch_lex_1);
	fclose(arch_lex_1); // Se cierra el primer archivo.
    arch_lex_1 = NULL; // Se apunta a nulo el puntero del primer archivo.


	// Guarda la línea del archivo .lex temporalmente:
	char linea[12];

	// Se recorre el archivo .lex para ir obteniendo cada línea:
    while(fgets(linea, sizeof(linea), arch_lex_2))
    {
		// Se aumenta el número de línea del archivo .lex:
		num_linea_lex++;

		// Si es el indicador de número de línea se lo salta:
		if(linea[0] == '~')
        {
			// Se aumenta el número de línea del archivo .mio:
            num_linea_mio = strtol(linea+1, NULL, 10);
            continue;
        }

		// Se cambia el salto de línea por el caracter nulo.
		// 10 == '\n' en ASCII
		// 0 == '\0' en ASCII
        if(linea[strlen(linea)-1] == 10)
            linea[strlen(linea)-1] = 0;

        // Se verifica que no hayan errores en la estructura principal del programa:
        if((num_linea_lex == 2) && strncmp(linea,"PROGRAMA", strlen(linea)) == 0)
			continue; // Si se encuentra no se agrega en la lista.
		
		// Si no se encuentra PROGRAMA:
		else if((num_linea_lex == 2) && strncmp(linea,"PROGRAMA", strlen(linea)) != 0)
		{	
            printf("ERROR de sintaxis en línea [%u] --PROGRAMA no encontrado.\n", num_linea_mio);
            num_errores++;
        }

        if((num_linea_lex == 3) && strncmp(linea, "[id] ID01", strlen(linea)) == 0)
            continue; // Si se encuentra, no se agrega en la lista.
        
		// Si no se encuentra el nombre del programa:
		else if((num_linea_lex == 3) && strncmp(linea, "[id] ID01", strlen(linea)) != 0)
		{
        	printf("ERROR de sintaxis en línea [%u] --Nombre de programa no encontrado.\n", num_linea_mio);
            num_errores++;
        }

        if(num_linea_lex == 46 && strncmp(linea, "FINPROG", strlen(linea)) == 0)
            continue; // Si se encuentra, no se agrega en la lista.
        
		// Si no se encuentra FINPROG:
		else if(num_linea_lex == 46 && strncmp(linea, "FINPROG", strlen(linea)) != 0)
		{
        	printf("ERROR de sintaxis en línea [%u] --FINPROG no encontrado.\n");
            num_errores++;
        }    
		
		// Se crea y agrega el nodo a la lista:
        nodo_Tok *nodo = creaNodoTok(linea, num_linea_mio);
        pushBackTok(lista, nodo);
    }
    fclose(arch_lex_2); // Se cierra el segundo archivo.
    arch_lex_2 = NULL; // Se apunta a nulo el puntero del segundo archivo.
}


// Valida si la cadena es una palabra reservada 
int __esReservada(char *token)
{
    unsigned int i = 0;
    char *palabras_reservadas[11] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

    // Se verifica si es una palabra reservada:
    while(i < 11)
    {
        // Se verifica si es una palabra reservada:
        if(strstr(token, palabras_reservadas[i]))
        {   
            return (0); // Si es una palabra reservada.
        }
        i++; // Se pasa a la siguiente palabra.
    }

    // Si no es una palabra reservada:
    return (1);
}


// Valida si la cadena es un OPERADOR ARITMÉTICO. 
int __esOpAr(char *cadena) 
{ 
    // Se verifica si es un operador aritmético:
    if(strstr(cadena, "[op_ar]"))
        return 0; // Es un operador aritmético.

    // Si no es un operador aritmético:
    return 1;

}


// Valida si la cadena es un NÚMERO 
int __esVal(char *token)
{
    // Se verifica si es un número:
    if(strstr(token, "[val]"))
    {       
        return 0; // Si es un número.
    }

    // Si no es un número:
    return 1;
}


// Valida si la cadena es un OPERADOR RELACIONAL 
int __esOpRel(char *cadena)
{
    // Se verifica si es un operador relacional:
    if(strstr(cadena, "[op_rel]"))
    {       
        return 0; // Si es operador relacional.
    }

    // Si no es un operador relacional:
    return 1;      
}


// Valida si el caracter es una COMILLA 
int __esComilla(char *cadena)
{
    // '\"' == 34 en ASCII,

    // Si es una comilla:
    if(*cadena == 34)
        return (0);

    // Si no es una comilla:
    return (1);
}


// Valida si la cadena es un string 
int __esTexto(char *token)
{
    // Se verifica si es una palabra reservada:

    // Si es una cadena de text0:
    if(strstr(token, "[txt]"))
    {
        return 0;    
    }
    
    // No es una cadena de texto:
    return 1;
}


// Valida si la cadena se trata de una variable 
int __esVariable(char *token)
{
    if(strstr(token,"[id]"))
        return 0; // Si es variable.
    
    // Si no es una variable:
    return 1;
    
}


// Identifica si el token es un elemento 
int __esElem(char *token)
{
    if(__esVariable(token))
        return 0; // Es un elemento, es una variable.
    
    else if(__esVal(token))
        return 0; // Es un elemento, es un valor.
    
    // No es un elemento:
    return 1;
}

/*
// Identifica si es una comparación 
int __esCompara(nodo_Tok *nodo, unsigned int num_linea)
{
    if(__esVariable(nodo->token))
    {
        nodo = nodo->sig; // Se pasa al siguiente nodo.

        if(__esOpRel(nodo->token))
        {
            nodo = nodo->sig; // Se pasa al siguiente nodo.

            if(__esElem(nodo->token))
                return 0; // No hubo errores.
            
            // Hubo errores:
            printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", num_linea);
            return 1;
        } // Fin if

        // Hubo errores:
        printf("ERROR de sintaxis en línea [%u] --No es un operador relacional.\n", num_linea);
        return 1;
    } // Fin if

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un identificador.\n", num_linea);
    return 1;
}
*/

// Identifica si la sentencia es de lectura 
int __esLee(char *token, unsigned int num_linea)
{
    if(__esVariable(token) == 0)
            return 0; // No hubo errores.

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un identificador válido", num_linea);   
    return 1;
    
}


// Identifica si la sentencia es de impresión 
int __esImprime(char *token, unsigned int num_linea)
{
    // Si es una cadena de texto:
    if(__esTexto(token) == 0)
        return 0; // No hubo errores.
    
    // Si es un elemento:
    else if(__esElem(token) == 0)
        return 0; // No hubo errores.
            
    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un elemento (identificador o valor) o cadena válida.\n", num_linea);
    return 1;
}

/*
// Identifica si es una asginación 
int __esAsig(nodo_Tok *nodo, unsigned int num_linea)
{
    if(strncmp(nodo->token, "=", strlen(nodo->token)+1) == 0)
    {
        nodo = nodo->sig; // Se pasa al siguiente nodo.

        if(__esElem(nodo->token) == 0)
            return 0; // No hubo errores.

        // Hubo error, no es un elemento válido:
        printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", num_linea);
        return 1;

    } // Fin if

    // Hubo error, no es una asignación:
    printf("ERROR de sintaxis en línea [%u] --No es un operador de asginación válido.\n", num_linea);
    return 1;
}


// Identifica si la cadena es una operación aritmética 
int __esOperArit(nodo_Tok *nodo, unsigned int num_linea)
{
    if(__esOpAr(nodo->token) == 0)
    {
        nodo = nodo->sig; // Se pasa al nodo siguiente.

        if(__esElem(nodo->token) == 0)
            return 0; // No hubo errores.

        // Hubo error, no es un elemento válid:
        printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", num_linea);
        return 1;

    } // Fin if
             
    printf("ERROR de sintaxis en línea [%u] --No es un operador aritmético válido.\n", num_linea);
    return 1;
}


// Identifica si se trata de una sentencia válida 
int __esSent(nodo_Tok *nodo, unsigned int num_linea)
{
    //nodo_Tok *aux = lista->raiz;
    
    unsigned int error = 0;

    if(__esReservada(nodo->token) == 0)
    {   
        // Si empieza con LEE:
        if(strncmp(nodo->token,"LEE", strlen(nodo->token)+1) == 0)
        {   
            // Se pasa al token siguiente:
            nodo = nodo->sig;
            
            error = __esLee(nodo->token, num_linea);

            return error; // Se retorna el valor de error.
        }

        // Si empieza con IMPRIME:
        else if(strncmp(nodo->token, "IMPRIME", strlen(nodo->token)+1) == 0)
        {
            // Se pasa al token siguiente:
            nodo = nodo->sig;

            error = __esImprime(nodo->token, num_linea);

            return error; // Se retorna el valor de error.
        }

        // Si es repite:
        else if(strncmp(nodo->token, "REPITE", strlen(nodo->token)+1) == 0)
        {   
            // Se pasa al token siguiente:
            nodo = nodo->sig;

            if(__esElem(nodo->token) == 0)
            {
                // Se pasa al token siguiente:
                nodo = nodo->sig;

                if(strncmp(nodo->token,"VECES", strlen(nodo->token)+1) == 0)
                {
                    nodo = nodo->sig; // Se pasa al token siguiente.

                    if(__esSent(nodo, nodo->num_linea) == 0)
                    {
                        nodo = nodo->sig; // Se pasa al token siguiente.

                        if(strncmp(nodo->token,"FINREP", strlen(nodo->token)+1) == 0)
                            return 0; // No hubo errores.

                        while(__esSent(nodo, nodo->num_linea) == 0)
                        {
                            nodo = nodo->sig; // Se pasa al token siguiente.

                            if(strncmp(nodo->token,"FINREP", strlen(nodo->token)+1) == 0)
                                return 0; // No hubo errores.
                        }

                        // Hubo error, falta FINREP:
                        printf("ERROR de sintaxis en línea [%u] --Falta FINREP.\n", num_linea);
                        return 1;

                    } // Fin if

                    // Hubo error, sentencia no válida:
                    printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", num_linea);
                    return 1;  

                } // Fin if

                // Hubo error, falta VECES:
                printf("ERROR de sintaxis en línea [%u] --Falta VECES.\n", num_linea);
                return 1;

            } // Fin if

            // Hubo error:
            printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", num_linea);
            return 1;

        } // Fin de else if de repite

        // Si es condicional si-entonces o si-entonces-sino:
        else if(strncmp(nodo->token, "SI", strlen(nodo->token)+1) == 0)
        {
            nodo = nodo->sig;  // Se pasa al token siguiente.

            if(__esCompara(nodo, nodo->num_linea) == 0)
            {
                nodo = nodo->sig;  // Se pasa al token siguiente.

                if(strncmp(nodo->token, "ENTONCES", strlen(nodo->token)+1) == 0)
                {
                    nodo = nodo->sig;  // Se pasa al token siguiente.

                    if(__esSent(nodo, nodo->num_linea) == 0)
                    {
                        nodo = nodo->sig;  // Se pasa al token siguiente.
                    
                        if(strncmp(nodo->token, "FINSI", strlen(nodo->token)+1) == 0)
                            return 0; // No hubo errores.

                        while(__esSent(nodo, nodo->num_linea) == 0)
                        {
                            nodo = nodo->sig; // Se pasa al nodo siguiente.

                            if(strncmp(nodo->token,"FINSI", strlen(nodo->token)+1) == 0)
                                return 0; // No hubo errores.
                        }

                        // Hubo error:
                        printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", nodo->num_linea);
                        return 1;

                    } // Fin if __esSent

                    // Hubo error:
                    printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
                    return 1;

                } // Fin if ENTONCES

                // Hubo error:
                printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (ENTONCES).\n", nodo->num_linea);
                return 1;

            } // Fin if __esCompara

            // Hubo error:
            printf("ERROR de sintaxis en línea [%u] --No es una comparación.\n", nodo->num_linea);
            return 1;

        } // Fin else if de condicional 
        
        // Hubo error:
        printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
        return 1;

    } // Fin if __esReservada


    // Si es una asignación:
    else if((error = __esVariable(nodo->token)) == 0)
    {
        nodo = nodo->sig; // Se pasa al token siguiente.

        if ((error = __esAsig(nodo, num_linea)) == 0)
        {
            nodo = nodo->sig;

            if(nodo) // Si hay otro nodo después:
                error = __esOperArit(nodo, num_linea);
        
        } // Fin if

        return error; // Se retorna el valor de error.

    } // Fin else if de asignación

    // Hubo errores
    printf("[ERROR de sintaxis en línea [%u] --No es una sentencia válida].\n", num_linea);
    error = 1;

    // Se retorna el resultado del error, 0 si no hubo, 1 si hubo:
    return error;
}


// Inicia el analizador sintáctico 
int analSintax(listaTok *lista) 
{
    nodo_Tok *aux = lista->raiz;

    if(strncmp(aux->token, "PROGRAMA", strlen(aux->token)+1) == 0)
    {
        aux = aux->sig; // Se pasa al nodo siguiente.

        if(__esVariable(aux->token) == 0)
        {
            aux = aux->sig; // Se pasa al nodo siguiente.

            if(__esSent(aux, aux->num_linea) == 0)
            {
                aux = aux->sig; // Se pasa al nodo siguiente.

                if(strncmp(aux->token,"FINPROG", strlen(aux->token)+1) == 0)
                    return 0; // No hubo errores.

                while(__esSent(aux, aux->num_linea) == 0)
                {
                    aux = aux->sig; // Se pasa al nodo siguiente.

                    if(strncmp(aux->token,"FINPROG", strlen(aux->token)+1) == 0)
                        return 0; // No hubo errores.

                }

                // Hubo error:
                printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINPROG).\n", aux->num_linea);
                return 1;

            } // Fin if

            // Hubo error:
            printf("ERROR de sintaxis en línea [%u] --No es una sentencia válida.\n", aux->num_linea);
            return 1;

        } // Fin if __esVariable

        printf("ERROR de sintaxis en línea [%u] --Falta identificador.\n", aux->num_linea);
        return 1;

    } // Fin if PROGRAMA

    printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (PROGRAMA).\n", aux->num_linea);
    return 1;
}

*/