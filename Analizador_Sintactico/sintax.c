#include "listas.c"

// Contador global de errores del programa:
unsigned int num_errores = 0;

/* Cuenta la cantidad de líneas que hay en un archivo.
   
   Parámetros: Puntero a un archivo.
   
   Retorna: el número (int) de líneas que hay en el archivo.
   En caso de no encontrar el archivo, retorna -1.
*/
/*int __contarLineasArchivo(FILE *archivo)
{
    unsigned int numero_lineas = 0; // Contador del número de líneas del archivo.
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
} */


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

        // Si es una línea en blanco:
        if(linea[0] == '\n')
            continue;

		// Se cambia el salto de línea por el caracter nulo.
		// 10 == '\n' en ASCII
		// 0 == '\0' en ASCII
        if(linea[strlen(linea)-1] == 10)
            linea[strlen(linea)-1] = 0;

		// Se crea y agrega el nodo a la lista:
        nodo_Tok *nodo = creaNodoTok(linea, num_linea_mio);
        pushBackTok(lista, nodo);
    }
    fclose(arch_lex_1); // Se cierra el primer archivo.
    arch_lex_1 = NULL; // Se apunta a nulo el puntero del primer archivo.
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
    if(strncmp(token, "[val]", strlen(token)+1) == 0)
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
    if(strstr(token,"[id]") != NULL)
        return 0; // Si es variable.
    
    // No es una variable:
    return 1;
    
}


// Identifica si el token es un elemento 
int __esElem(char *token)
{
    if(__esVariable(token) == 0)
        return 0; // Es un elemento, es una variable.
    
    else if(__esVal(token) == 0)
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
    if(strncmp(token, "LEE", strlen(token)) == 0)
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


// Identifica si es una asignación:
int __esAsig(char *token)
{
    // '=' = 61 en ASCII:
    if(*token == 61)
        return 0; // Es un signo de igual.
    
    // No es un signo de igual :
    return 1;
}


// Identifica si el token es un REPTE:
int __esRepite(char *token)
{
    // Se verifica que el token sea un REPITE:
    if(strncmp(token, "REPITE", strlen(token)+1) == 0)
        return 0; // Es REPITE.
    
    // No es REPITE:
    return 1;
}


// Identifica si el token es un VECES:
int __esVeces(char *token)
{   
    // Se verifica si el token es VECES:
    if(strncmp(token,"VECES", strlen(token)+1) == 0)
        return 0; // Es VECES.

    // No es VECES:
    return 1; 
}


// Identifica si el token es un FINREP:
int __esFinRep(char *token)
{
    // Se verifica si el token es FINREP:
    if(strncmp(token,"FINREP", strlen(token)+1) == 0)
        return 0; // Es FINREP.

    // No es FINREP:
    return 1; 
}


// Identifica si el token es un SI:
int __esSi(char *token)
{   
    // Se verifica si el token es SI:
    if(strncmp(token,"SI", strlen(token)+1) == 0)
        return 0; // Es SI.

    // No es SI:
    return 1; 
}


// Identifica si el token es un SINO:
int __esSiNo(char *token)
{   
    // Se verifica si el token es SINO:
    if(strncmp(token,"SINO", strlen(token)+1) == 0)
        return 0; // Es SINO.

    // No es SINO:
    return 1; 
}


// identifica si el token es un FINSI:
int __esFinSi(char *token)
{   
    // Se verifica si el token es FINSI:
    if(strncmp(token,"FINSI", strlen(token)+1) == 0)
        return 0; // Es FINSI.

    // No es FINSI:
    return 1; 
}


// Identifica si el token es un ENTONCES:
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
    // Bandera que identifica un error de sentencia.
    int err_sent = 0;

    // Si el nodo es nulo:
    if(!nodo)
        return NULL;

    if(__esReservada(nodo->token) == 0)
    {   
        // Si empieza con LEE:
        if(__esLee(nodo->token) == 0)
        {   
            if(nodo->sig)
            {
                nodo = nodo->sig; // Se pasa al nodo siguiente.

                // Se verifica que el token siguiente
                // sea un identificador:
                if(__esVariable(nodo->token) == 0)
                {
                    if(nodo->sig)
                        nodo = nodo->sig;
                }

                // Hay error:
                else
                {
                    // Hubo error:
                    printf("ERROR de sintaxis en línea [%u] --No es un identificador válido.\n", nodo->num_linea);
                    num_errores++;
                }
            }
            // Si es el final de la lista:
            else
                err_sent++; // Hay un error de sentencia.
        }

        // Si empieza con IMPRIME:
        else if(__esImprime(nodo->token) == 0)
        {    
            if(nodo->sig) 
            {    
                nodo = nodo->sig; // Se pasa al token siguiente.
                
                // Se verifica que el token siguiente sea 
                // un elemento o una cadena
                if(__esElem(nodo->token) == 0 || __esTexto(nodo->token) == 0)
                {   
                    if(nodo->sig)
                        nodo = nodo->sig; // Se pasa al siguiente nodo.
                }    
                // Si hay un error:
                else
                {
                    printf("ERROR de sintaxis en línea [%u] --No hay identificador, número o cadena.\n", nodo->num_linea);
                    num_errores++;
                }
            }

            // Si es el final de la lista:
            else
                err_sent++; // Hay un error de sentencia.
        }

        // Si es repite:
        else if(__esRepite(nodo->token) == 0)
        { 
            if(nodo->sig)
            {
                nodo = nodo->sig; // Se pasa al token siguiente.
                
                // Se verifica que el token sea un elemento:
                if(__esElem(nodo->token) == 0)
                {
                    if(nodo->sig)
                    {    
                        nodo = nodo->sig; // Se pasa al nodo siguiente.
                        
                        // Se verifica que el token sea VECES:
                        if(__esVeces(nodo->token) == 0)
                        {
                            // Se verifica que el token sea una sentencia válida:
                            if(nodo->sig)
                            {
                                nodo = nodo->sig; // Se pasa al nodo siguiente.
                                
                                // Se verifica que lo que sigue 
                                // sea una sentencia válida:
                                nodo = __esSent(nodo);
                                
                                // Se verifican los tokens siguientes:
                                if(nodo)
                                {
                                    // Se verifica que el token no sea FINREP:
                                    if(__esFinRep(nodo->token) != 0)
                                    {   
                                        // Se verifica que sea un nodo diferente de NULL y 
                                        // que lo que siga sean sentencias válidas:
                                        while(nodo)
                                        {
                                            nodo = __esSent(nodo);
                                            
                                            // Si es FINREP:
                                            if(__esFinRep(nodo->token) == 0)
                                            {   
                                                if(nodo->sig)
                                                    nodo = nodo->sig; // Se pasa al siguiente nodo.
                                                break; // No hubo errores.
                                            }
                                        }
                            
                                        // Se verifica si se llegó al final de la lista:
                                        // Si se llegó al final, hubo error, pues falta FINREP:
                                        if(!nodo)
                                        {
                                            printf("ERROR de sintaxis en línea [%u] --Falta FINREP.\n", nodo->num_linea);
                                            num_errores++;
                                        }
                                    } // Fin if __esFinRep
                                    else if(nodo->sig)
                                        nodo = nodo->sig; // Se pasa al siguiente nodo.
                                } // Fin if nodo  
                                else
                                {
                                    printf("ERROR de sintaxis en línea [%u] --Falta FINREP.\n", nodo->num_linea);
                                    num_errores++;
                                }
                                
                            } // Fin if.

                            else
                            {
                                // Hubo error, sentencia no válida:
                                printf("REPITE: ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", nodo->num_linea);
                                num_errores++;  
                            }
                        } // Fin if __esVeces.

                        else
                        {                
                            // Hubo error, falta VECES:
                            printf("ERROR de sintaxis en línea [%u] --Falta VECES.\n", nodo->num_linea);
                            num_errores++;
                        }
                    }
                    else
                        err_sent++; // Hay un error de sentencia.
                } // Fin if

                else
                {
                    // Hubo error:
                    printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", nodo->num_linea);
                    num_errores++;
                }
            } // Fin if  
            else
                err_sent++; // Hay un error de sentencia.
        } // Fin de else if de repite

        // Si es condicional si-entonces o si-entonces-sino:
        else if(__esSi(nodo->token) == 0)
        {
            if(nodo->sig)
            {
                nodo = nodo->sig;  // Se pasa al nodo siguiente.

                if(__esCompara(nodo) == 0)
                {   
                    if(nodo->sig)
                    {   
                        nodo = nodo->sig;  // Se pasa al nodo siguiente.

                        if(__esEntonces(nodo->token) == 0)
                        {
                            if(nodo->sig)
                            {
                                nodo = nodo->sig;  // Se pasa al nodo siguiente.
                                
                                // Se verifica que lo que sigue 
                                // sea una sentencia válida:
                                nodo = __esSent(nodo);
                                
                                // Se verifican los tokens siguientes:
                                if(nodo)
                                {   
                                    // Se verifica si ya se llegó al FINSI
                                    // o si hay más sentencias válidas:
                                    if(__esFinSi(nodo->token) != 0)
                                    {    
                                        // Se verifica que sea un nodo diferente de NULL y 
                                        // que lo que siga sean sentencias válidas:
                                        while(nodo)
                                        {
                                            nodo = __esSent(nodo);

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
                                            nodo = nodo->sig;  // Se pasa al nodo siguiente.

                                            // Se verifica que lo que sigue 
                                            // sea una sentencia válida:
                                            nodo = __esSent(nodo);

                                            // Se verifican los siguientes tokens:
                                            if(nodo)
                                            {  
                                                // Se verifica si ya se llegó al FINSI
                                                // o si hay más sentencias válidas:
                                                if(__esFinSi(nodo->token) != 0)
                                                {    
                                                    // Se verifica que sea un nodo diferente de NULL y 
                                                    // que lo que siga sean sentencias válidas:
                                                    while(nodo)
                                                    {
                                                        nodo = __esSent(nodo);

                                                        // Si es FINSI:
                                                        if(__esFinSi(nodo->token) == 0)
                                                        {
                                                            nodo = nodo->sig; // Se pasa al siguiente token.
                                                            break; // No hubo errores.   
                                                        }
                                                    }

                                                    // Se verifica si se llegó al final de la lista:
                                                    // Si se llegó al final, hubo error, pues falta FINSI:
                                                    if(!nodo)
                                                    {
                                                        printf("ERROR de sintaxis en línea [%u] --Falta (FINSI).\n", nodo->num_linea);
                                                        num_errores++;
                                                    }
                                                } // Fin if __esFinSi.    
                                            } // Fin if nodo.
                                            else
                                            {
                                                printf("ERROR de sintaxis en línea [%u] --Falta (FINSI).\n", nodo->num_linea);
                                                num_errores++;
                                            }    
                                        } // Fin else if __esSiNo.
                                    } // Fin if __esFinSi.

                                    else
                                    {
                                        // Hubo error, falta un FINSI:
                                        printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", nodo->num_linea);
                                        num_errores++;
                                    }
                                } // Fin if nodo  
                                else
                                {
                                    // Hubo error, falta un FINSI:
                                    printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", nodo->num_linea);
                                    num_errores++;
                                }
                            } // Fin if
                            else
                                err_sent++; // Hay un error de sentencia.
                        } // Fin if ENTONCES

                        else
                        { 
                            // Hubo error:
                            printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (ENTONCES).\n", nodo->num_linea);
                            num_errores++;
                        }
                    } // Fin if
                    else
                        err_sent++; // Hay un error de sentencia.
                } // Fin if __esCompara

                else
                {
                    // Hubo error, no es una COMPARACIÓN:
                    printf("ERROR de sintaxis en línea [%u] --No es una comparación válida.\n", nodo->num_linea);
                    num_errores++;
                }
            } // Fin if
            else
                err_sent++; // Hay un error de sentencia.
        } // Fin else if de condicional 
        
    } // Fin if __esReservada

    // Se verifica si es una sentencia de asignación:
    else if(__esVariable(nodo->token) == 0)
    {
        if(nodo->sig)
        {    
            nodo = nodo->sig; // Se pasa al nodo siguiente.
        
            // Se verifica que sea un signo de '=':
            if(__esAsig(nodo->token) == 0)
            {
                if(nodo->sig)
                {
                    nodo = nodo->sig; // Se pasa al nodo siguiente.
                
                    // Se verifica si el token es un ELEM:
                    if(__esElem(nodo->token) == 0)
                    {   
                        if(nodo->sig)
                        {  
                            nodo = nodo->sig; // Se pasa al nodo siguiente.

                            // Se verifica si el token siguiente es un operador aritmético:
                            if(__esOpAr(nodo->token) == 0)
                            {
                                if(nodo->sig)
                                {
                                    nodo = nodo->sig; // Se pasa al nodo siguiente.
                                    
                                    // Se verifica si el token es un ELEM
                                    // y que lo que sigue no sea un '=' :
                                    if(__esElem(nodo->token) == 0)
                                    {
                                        // Si lo que sigue es realmente una sentencia de
                                        // asignación:
                                        if(__esAsig(nodo->sig->token) == 0)
                                        {
                                            printf("ERROR de sintaxis en línea [%u] --No es posible operar una asignación.\n");
                                            num_errores++;
                                        }

                                        else if(nodo->sig)
                                            nodo = nodo->sig; // Se pasa al siguiente nodo.
                                    }

                                    // Si no es un elemento:
                                    else
                                    {    
                                        printf("ERROR de sintaxis en línea [%u] --Elemento no encontrado.\n", nodo->num_linea);
                                        num_errores++;
                                    }                                    
                                } // Fin if
                                else
                                    err_sent++; // Hay un error de sentencia.
                            } // Fin if __esOpAr.
                        } // Fin if
                        else
                            err_sent++; // Hay un error de sentencia.
                    } // Fin if __esElem.
                } // Fin if
                else
                    err_sent++; // Hay un error de sentencia.
            } // Fin if __esAsig.
        } // Fin if
        else
            err_sent++; // Hay un error de sentencia.
    } // Fin else if de __esVar de asignación.

    // Si hubo error de sentencia:
    if(err_sent != 0)
    {    
        printf("GENERAL: ERROR de sintaxis en línea [%u] --No es una sentencia válida.\n", nodo->num_linea);
        num_errores++;
    }

    // Se retorna el puntero al nodo siguiente
    // si no es el final de la lista:
    if(nodo)
        return nodo;
    else
        return NULL; // Si es el final de la lista
}


// Inicia el analizador sintáctico: 
int iniAnalSin(listaTok *lista) 
{
    // Si la lista es NULL:
    if(!lista)
        return num_errores++;

    // Nodo auxiliar para recorrer la lista:
    nodo_Tok *aux = lista->raiz;

    // Se analiza la estructura principal del programa:
    if(strncmp(aux->token, "PROGRAMA", strlen(aux->token)+1) == 0)
         aux = aux->sig;
    
    // Si PROGRAMA no se encuentra:
    else
    {
        printf("ERROR de sintaxis en línea [%u] --No se encuentra palabra reservada: PROGRAMA.\n", aux->num_linea);
        num_errores++;
    }

    if(strncmp(aux->token, "[id] ID01", strlen(aux->token)+1) == 0)
        aux = aux->sig;
    
    // Si el nombre del programa no se encuentra:
    else
    {
        printf("ERROR de sintaxis en línea [%u] --No se encuentra: Nombre del programa.\n", aux->num_linea);
        num_errores++;
    }
    

    // Se llama a __esSent para verificar que todas
    // las sentencias de la lista sean válidas:
    while(aux->sig)
    {
        //printf("[%s] --{%u}--\n", aux->token, aux->num_linea);
        aux = __esSent(aux); // Se continúa el ciclo con el siguiente nodo.
    }
    
    if(strncmp(aux->token, "FINPROG", strlen(aux->token)+1) != 0)
    {
        printf("ERROR de sintaxis en línea [%u] --No se encuentra palabra reservada: FINPROG.\n", aux->num_linea);
        num_errores++;
    }

    // Retorna copia del contador global num_errores:
    return num_errores;
}

