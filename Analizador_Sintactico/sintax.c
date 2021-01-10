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
            return 0; // Si es una palabra reservada.
        }
        i++; // Se pasa a la siguiente palabra.
    }

    // Si no es una palabra reservada:
    return 1;
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
        return 0;

    // Si no es una comilla:
    return 1;
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


// Identifica si es una comparación 
int __esCompara(nodo_Tok *nodo)
{
    // Se verifica si el token es un identificador:
    if(__esVariable(nodo->token) == 0)
    {
        nodo = nodo->sig; // Se pasa al siguiente nodo.

        // Se verifica si el token es un operador relacional:
        if(__esOpRel(nodo->token) == 0)
        {
            nodo = nodo->sig; // Se pasa al siguiente nodo.

            if(__esElem(nodo->token) == 0)
                return 0; // No hubo errores.
            
            // Hubo errores:
            printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", nodo->num_linea);
            num_errores++;
            return 1;
        } // Fin if

        // Hubo errores:
        printf("ERROR de sintaxis en línea [%u] --No es un operador relacional.\n", nodo->num_linea);
        num_errores++;
        return 1;
    } // Fin if

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un identificador.\n", nodo->num_linea);
    num_errores++;
    return 1;
}


// Identifica si la sentencia es de lectura 
int __esLee(char *token)
{
    if(strncmp(token, "LEE", strlen(token)+1) == 0)
            return 0; // Es LEE.
    
    // No es LEE:
    return 1;  
}


// Identifica si la sentencia es de impresión 
int __esImprime(char *token)
{
    // Se verifica si el token es IMPRIME:
    if(strncmp(token, "IMPRIME", strlen(token)+1) == 0)
        return 0; // Es IMPRIME.
            
    // No es IMPRIME:
    return 1;
}


// Identifica si es una asginación 
int __esAsig(nodo_Tok *nodo)
{
    if(strncmp(nodo->token, "=", strlen(nodo->token)+1) == 0)
    {
        nodo = nodo->sig; // Se pasa al siguiente nodo.

        if(__esElem(nodo->token) == 0)
            return 0; // No hubo errores.

        // Hubo error, no es un elemento válido:
        printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", nodo->num_linea);
        num_errores++;
        return 1;

    } // Fin if

    // Hubo error, no es una asignación:
    printf("ERROR de sintaxis en línea [%u] --No es un operador de asginación válido.\n", nodo->num_linea);
    num_errores++;
    return 1;
}


// Identifica si la cadena es una operación aritmética 
int __esOperArit(char *token)
{
    if(__esOpAr(token) == 0)
    {
        nodo = nodo->sig; // Se pasa al nodo siguiente.

        if(__esElem(nodo->token) == 0)
            return 0; // No hubo errores.

        // Hubo error, no es un elemento válid:
        printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", nodo->num_linea);
        num_errores++;
        return 1;

    } // Fin if
             
    printf("ERROR de sintaxis en línea [%u] --No es un operador aritmético válido.\n", nodo->num_linea);
    num_errores++;
    return 1;
}



int __esRepite(char *token)
{
    // Se verifica que el token sea un REPITE:
    if(strncmp(token, "REPITE", strlen(token)+1) == 0)
        return 0; // Es REPITE.
    
    // No es REPITE:
    return 1;
}



int __esVeces(char *token)
{   
    // Se verifica si el token es VECES:
    if(strncmp(token,"VECES", strlen(token)+1) == 0)
        return 0; // Es VECES.

    // No es VECES:
    return 1; 
}



int __esFinRep(char *token)
{   
    // Se verifica si el token es FINREP:
    if(strncmp(token,"FINREP", strlen(token)+1) == 0)
        return 0; // Es FINREP.

    // No es FINREP:
    return 1; 
}



int __esSi(char *token)
{   
    // Se verifica si el token es SI:
    if(strncmp(token,"SI", strlen(token)+1) == 0)
        return 0; // Es SI.

    // No es SI:
    return 1; 
}



int __esSiNo(char *token)
{   
    // Se verifica si el token es SINO:
    if(strncmp(token,"SINO", strlen(token)+1) == 0)
        return 0; // Es SINO.

    // No es SINO:
    return 1; 
}



int __esFinSi(char *token)
{   
    // Se verifica si el token es FINSI:
    if(strncmp(token,"FINSI", strlen(token)+1) == 0)
        return 0; // Es FINSI.

    // No es FINSI:
    return 1; 
}



int __esEntonces(char *token)
{   
    // Se verifica si el token es ENTONCES:
    if(strncmp(token,"ENTONCES", strlen(token)+1) == 0)
        return 0; // Es ENTONCES.

    // No es ENTONCES:
    return 1; 
}



// Identifica si se trata de una sentencia válida 
nodo_Tok *__esSent(nodo_Tok *nodo)
{   
    unsigned int error = 0;

    if(__esReservada(nodo->token) == 0)
    {   
        // Si empieza con LEE:
        if(__esLee(nodo->token) == 0)
        {   
            // Se pasa al token siguiente:
            nodo = nodo->sig;
            
            // Se verifica que el token siguiente
            // sea un identificador, si no, hay error:
            if(__esVariable(nodo->token) != 0);
            {    
                // Hubo error:
                printf("ERROR de sintaxis en línea [%u] --No es un identificador válido", nodo->num_linea);
                num_errores++;   
            }
        }

        // Si empieza con IMPRIME:
        else if(__esImprime(nodo->token) == 0)
        {    
            // Se pasa al token siguiente:
            nodo = nodo->sig;

            // Se verifica que el token siguiente sea 
            // un elemento o una cadena, si no, hay error:
            if(__esElem(nodo->token) != 0 && __esTexto(nodo->token) != 0)
            {
                printf("ERROR de sintaxis en línea [%u] --No hay identificador, número o cadena.\n", nodo->num_linea);
                num_errores++;
            }
        }

        // Si es repite:
        else if(__esRepite(nodo->token) == 0)
        {   
            // Se pasa al token siguiente:
            nodo = nodo->sig;

            // Se verifica que el token sea un elemento:
            if(__esElem(nodo->token) == 0)
            {
                nodo = nodo->sig; // Se pasa al nodo siguiente.
                
                // Se verifica que el token sea VECES:
                if(__esVeces(nodo->token) == 0)
                {
                    nodo = nodo->sig; // Se pasa al nodo siguiente.

                    if(__esSent(nodo) == 0)
                    {
                        nodo = nodo->sig; // Se pasa al nodo siguiente.

                        // Se verifica si el token no es FINREP:
                        if(__esFinRep(nodo->token) != 0)
                        {   
                            // Se verifica que sea un nodo diferente de NULL y 
                            // que lo que siga sean sentencias válidas:
                            while(nodo && __esSent(nodo) == 0)
                            {
                                nodo = nodo->sig; // Se pasa al nodo siguiente.

                                // Si es FINREP:
                                if(__esFinRep(nodo->token) == 0)
                                    break; // No hubo errores.
                            }
                            
                            // Se verifica si se llegó al final de la lista:
                            // Si se llegó al final, hubo error, pues falta FINREP:
                            if(!nodo)
                            {
                                printf("ERROR de sintaxis en línea [%u] --Falta FINREP.\n", nodo->num_linea);
                                num_errores++;
                            }
                        }
                    } // Fin if __esSent.

                    else
                    {
                        // Hubo error, sentencia no válida:
                        printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
                        num_errores++;  
                    }
                } // Fin if __esVeces.

                else
                {                
                    // Hubo error, falta VECES:
                    printf("ERROR de sintaxis en línea [%u] --Falta VECES.\n", nodo->num_linea);
                    num_errores++;
                }
            } // Fin if

            else
            {
                // Hubo error:
                printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", nodo->num_linea);
                num_errores++;
            }
        } // Fin de else if de repite

        // Si es condicional si-entonces o si-entonces-sino:
        else if(__esSi(nodo->token) == 0)
        {
            nodo = nodo->sig;  // Se pasa al nodo siguiente.

            if(__esCompara(nodo) == 0)
            {
                nodo = nodo->sig;  // Se pasa al nodo siguiente.

                if(__esEntonces(nodo->token) == 0)
                {
                    nodo = nodo->sig;  // Se pasa al nodo siguiente.

                    if(__esSent(nodo) == 0)
                    {
                        nodo = nodo->sig;  // Se pasa al nodo siguiente.
                    
                        if(__esFinSi(nodo->token) != 0)
                        {    
                            // Se verifica que sea un nodo diferente de NULL y 
                            // que lo que siga sean sentencias válidas:
                            while(nodo && __esSent(nodo) == 0)
                            {
                                nodo = nodo->sig; // Se pasa al nodo siguiente.

                                // Si es FINSI o SINO:
                                if(__esFinSi(nodo->token) == 0 || __esSiNo(nodo->token) == 0)
                                    break; // No hubo errores.   
                            }

                            // Se verifica si se llegó al final de la lista:
                            // Si se llegó al final, hubo error, pues falta FINSI:
                            if(!nodo)
                            {
                                printf("ERROR de sintaxis en línea [%u] --Falta (FINSI).\n", nodo->num_linea);
                                num_errores++;
                            }

                            // Si no se llegó al final de la lista,
                            // entonces se verifica si es un SINO:
                            else if(__esSiNo(nodo->token) == 0)
                            {
                                if(__esSent(nodo) == 0)
                                {
                                    nodo = nodo->sig;  // Se pasa al nodo siguiente.
                    
                                    if(__esFinSi(nodo->token) != 0)
                                    {    
                                        // Se verifica que sea un nodo diferente de NULL y 
                                        // que lo que siga sean sentencias válidas:
                                        while(nodo && __esSent(nodo) == 0)
                                        {
                                            nodo = nodo->sig; // Se pasa al nodo siguiente.

                                            // Si es FINSI:
                                            if(__esFinSi(nodo->token) == 0)
                                                break; // No hubo errores.   
                                        }

                                        // Se verifica si se llegó al final de la lista:
                                        // Si se llegó al final, hubo error, pues falta FINSI:
                                        if(!nodo)
                                        {
                                            printf("ERROR de sintaxis en línea [%u] --Falta (FINSI).\n", nodo->num_linea);
                                            num_errores++;
                                        }
                                    } // Fin if __esFinSi.    
                                } // FIn if __esSent.
                            } // Fin else if __esSiNo.
                        } // Fin if __esFinSi.

                        else
                        {
                            // Hubo error, falta un FINSI:
                            printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", nodo->num_linea);
                            num_errores++;
                        }
                    } // Fin if __esSent
                    
                    else
                    {
                        // Hubo error:
                        printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
                        num_errores++;
                    }
                } // Fin if ENTONCES

                else
                { 
                    // Hubo error:
                    printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (ENTONCES).\n", nodo->num_linea);
                    num_errores++;
                }
            } // Fin if __esCompara

            else
            {
                // Hubo error, no es una COMPARACIÓN:
                printf("ERROR de sintaxis en línea [%u] --No es una comparación válida.\n", nodo->num_linea);
                num_errores++;
            }
        } // Fin else if de condicional 
        
        // Si no es una sentencia válida:
        else
        {
            // Hubo error:
            printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
            num_errores++;
        }
    } // Fin if __esReservada

    // Si es una asignación:
    else if((__esVariable(nodo->token)) == 0)
    {
        nodo = nodo->sig; // Se pasa al nodo siguiente.

        if((__esAsig(nodo)) == 0)
        {
            nodo = nodo->sig;

            if(nodo) // Si hay otro nodo después:
                if(__esOperArit(nodo) != 0)
                {
                    printf("ERROR de sintaxis en línea [%u] --No es un operador aritmético válido.\n", nodo->num_linea);
                    num_errores++;
                }
        
        } // Fin if

        return nodo; // Se retorna el valor de nodo.

    } // Fin else if de asignación

    // Hubo error de sentencia:
    else
    {    
        printf("ERROR de sintaxis en línea [%u] --No es una sentencia válida.\n", nodo->num_linea);
        num_errores++;
    }

    // Se retorna el puntero al nodo siguiente
    // si el nodo no es nulo:
    if(nodo)    
        return nodo;
    return NULL;
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

            if(__esSent(aux) == 0)
            {
                aux = aux->sig; // Se pasa al nodo siguiente.

                if(strncmp(aux->token,"FINPROG", strlen(aux->token)+1) == 0)
                    return 0; // No hubo errores.

                while(__esSent(aux) == 0)
                {
                    aux = aux->sig; // Se pasa al nodo siguiente.

                    if(strncmp(aux->token,"FINPROG", strlen(aux->token)+1) == 0)
                        return 0; // No hubo errores.

                }

                // Hubo error:
                printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINPROG).\n", aux->num_linea);
                num_errores++;

            } // Fin if

            // Hubo error:
            printf("ERROR de sintaxis en línea [%u] --No es una sentencia válida.\n", aux->num_linea);
            num_errores++;

        } // Fin if __esVariable

        printf("ERROR de sintaxis en línea [%u] --Falta identificador.\n", aux->num_linea);
        num_errores++;

    } // Fin if PROGRAMA

    printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (PROGRAMA).\n", aux->num_linea);
    num_errores++;

    return num_errores;
}

