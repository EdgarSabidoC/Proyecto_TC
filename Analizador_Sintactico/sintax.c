// Biblioteca que incluye las funciones necesarias para el uso de listas de tipo listaTok:
#include "listas.c" 

// Contador global de errores del programa:
unsigned int num_errores = 0;

/* 
 * DESCRIPCIÓN:
 * Esta función crea una lista con los tokens del 
 * archivo .lex.
 *
 * La función ignora las indicadores de número de
 * línea de la sentencia (denotados por "~"), así
 * como las líneas en blanco.
 * 
 * NOTA 1: 
 * La función modifica el caracter final de 
 * la línea, cambiando los saltos de línea '\n' 
 * por el caracter nulo '\0'.
 * 
 * NOTA 2: 
 * La función cierra el archivo que se le 
 * pasa como argumento.
 *
 * ENTRADA: Un puntero al archivo .lex y un
 * puntero a una lista de tipo listaTok.
 * 
 * SALIDA: N/A.
 * 
 */
void guardarTokens(FILE *arch_lex, listaTok *lista)
{
    // Contadores del número de líneas de los archivos .mio y .lex:
    unsigned int num_linea_mio = 0; // Número de línea del archivo .mio
    unsigned int num_linea_lex = 0; // Número de línea del archivo .lex

	// Guarda la línea del archivo .lex temporalmente:
	char linea[12];

	// Se recorre el archivo .lex para ir obteniendo cada línea:
    while(fgets(linea, sizeof(linea), arch_lex))
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
    fclose(arch_lex); // Se cierra el archivo.
    arch_lex = NULL; // Se apunta a NULL el puntero del archivo.
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de una palabra reservada del
 * lenguaje MIO.
 * 
 * NOTA: 
 * Las palabras reservadas aceptadas son:
 * PROGRAMA, FINPROG, SI, ENTONCES, SINO, 
 * FINSI, REPITE, VECES, FINREP, IMPRIME
 * y LEE.
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de un operador aritmético: [op_ar] 
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esOpAr(char *cadena) 
{ 
    // Se verifica si es un operador aritmético:
    if(strstr(cadena, "[op_ar]"))
        return 0; // Es un operador aritmético.

    // Si no es un operador aritmético:
    return 1;

}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de un número: [val] 
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de un operador relacional: [op_rel] 
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de texto: [txt]
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata del identificador de una 
 * variable: [id]
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esVariable(char *token)
{
    if(strstr(token,"[id]") != NULL)
        return 0; // Si es variable.
    
    // No es una variable:
    return 1;
    
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * se trata de un elemento, es decir, si se 
 * trata del identificador de una variable o 
 * un valor numérico: [id] o [val]
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esElem(char *token)
{
    if(__esVariable(token) == 0)
        return 0; // Es un elemento, es una variable.
    
    else if(__esVal(token) == 0)
        return 0; // Es un elemento, es un valor.
    
    // No es un elemento:
    return 1;
}

/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (sentencia)
 * a partir del token que se le pase como argumento
 * se trata del una comparación.
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
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
            printf("ERROR de sintaxis en línea [%u] --No es un elemento válido --> %s.\n", nodo->num_linea, nodo->token);
            num_errores++;
            return 1;
        } // Fin if

        // Hubo errores:
        printf("ERROR de sintaxis en línea [%u] --No es un operador relacional --> %s.\n", nodo->num_linea, nodo->token);
        num_errores++;
        return 1;
    } // Fin if

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un identificador --> %s.\n", nodo->num_linea, nodo->token);
    num_errores++;
    return 1;
}

/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada para la lectura: LEE
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esLee(char *token)
{
    if(strncmp(token, "LEE", strlen(token)) == 0)
        return 0; // Es LEE.
    
    // No es LEE:
    return 1;  
}

/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada para impresión: IMPRIME
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esImprime(char *token)
{
    // Se verifica si el token es IMPRIME:
    if(strncmp(token, "IMPRIME", strlen(token)+1) == 0)
        return 0; // Es IMPRIME.
            
    // No es IMPRIME:
    return 1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es el símbolo
 * de asignación: =
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esAsig(char *token)
{
    // '=' = 61 en ASCII:
    if(*token == 61)
        return 0; // Es un signo de igual.
    
    // No es un signo de igual :
    return 1;
}

/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada para el ciclo de repetirción: REPITE
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esRepite(char *token)
{
    // Se verifica que el token sea un REPITE:
    if(strncmp(token, "REPITE", strlen(token)+1) == 0)
        return 0; // Es REPITE.
    
    // No es REPITE:
    return 1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada: VECES
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esVeces(char *token)
{   
    // Se verifica si el token es VECES:
    if(strncmp(token,"VECES", strlen(token)+1) == 0)
        return 0; // Es VECES.

    // No es VECES:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada del delimitador del ciclo de
 * repetición: FINREP
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esFinRep(char *token)
{
    // Se verifica si el token es FINREP:
    if(strncmp(token,"FINREP", strlen(token)+1) == 0)
        return 0; // Es FINREP.

    // No es FINREP:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada para las sentencias condicionales: SI
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esSi(char *token)
{   
    // Se verifica si el token es SI:
    if(strncmp(token,"SI", strlen(token)+1) == 0)
        return 0; // Es SI.

    // No es SI:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada para la sentencia condicional: SINO
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esSiNo(char *token)
{   
    // Se verifica si el token es SINO:
    if(strncmp(token,"SINO", strlen(token)+1) == 0)
        return 0; // Es SINO.

    // No es SINO:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la 
 * palabra reservada para las sentencias 
 * condicionales: ENTONCES
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esEntonces(char *token)
{   
    // Se verifica si el token es ENTONCES:
    if(strncmp(token,"ENTONCES", strlen(token)+1) == 0)
        return 0; // Es ENTONCES.

    // No es ENTONCES:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función valida si la cadena (token)
 * que se le pasa como argumento es la palabra
 * reservada del delimitador de las sentencias
 * condicionales: FINSI
 * 
 * ENTRADA: Puntero de tipo char (cadena) del token.
 * 
 * SALIDA: 0 si es verdad, 1 si es falso.
 * 
 */
int __esFinSi(char *token)
{   
    // Se verifica si el token es FINSI:
    if(strncmp(token,"FINSI", strlen(token)+1) == 0)
        return 0; // Es FINSI.

    // No es FINSI:
    return 1; 
}


/* 
 * DESCRIPCIÓN:
 * Esta función identifica si se trata de una sentencia válida 
 * del lenguaje MIO. Para ello va recorriendo los nodos de la 
 * lista partiendo del nodo de la lista que se le pase 
 * y utilizando previsión para identificar los tokens
 * en la secuencia correcta por sentencia.
 * 
 * NOTA: Para recorrer correctamente la lista es necesario el uso
 * de un ciclo y un puntero auxiliar, pues el análisis es por
 * sentencia.
 * 
 * ENTRADA: Un puntero a un nodo_Tok para iniciar el análisis.
 * 
 * SALIDA: Un puntero a un nodo_Tok donde finalizó el análisis.
 * 
 */
nodo_Tok *__esSent(nodo_Tok *nodo)
{   
    unsigned int err_sent = 0; // Bandera que identifica un error de sentencia.
    unsigned int err_var = 0; // Bandera que identifica un error de variable sin utilizar.

    // Si el nodo es nulo:
    if(!nodo)
        return NULL;

    if(__esReservada(nodo->token) == 0)
    {   
        // Si empieza con LEE:
        if(__esLee(nodo->token) == 0)
        {   
            // Se verifica que el token siguiente
            // sea un identificador:
            if((nodo->sig) && __esVariable(nodo->sig->token) == 0)
                nodo = nodo->sig; // Se pasa al nodo.
            
            // Hay error de identificador:
            else
            {
                printf("ERROR de sintaxis en línea [%u] --No es un identificador válido --> %s.\n", nodo->num_linea, nodo->token);
                num_errores++;
            }

            // Si existe un nodo después, se mueve hacia él:
            if(nodo->sig)
                nodo = nodo->sig;    
        } // Fin if __esLee


        // Si empieza con IMPRIME:
        else if(__esImprime(nodo->token) == 0)
        {    
            // Se verifica que el token siguiente sea 
            // un elemento o una cadena:
            if((nodo->sig) && (__esElem(nodo->sig->token) == 0 || __esTexto(nodo->sig->token) == 0)) 
                nodo = nodo->sig; // Se pasa al nodo.

            // Hay un error de indetificador, número o cadena:
            else
            {
                printf("ERROR de sintaxis en línea [%u] --No hay identificador, número o cadena.\n", nodo->num_linea);
                num_errores++;
            }

            // Si hay un nodo después:
            if(nodo->sig)
                 nodo = nodo->sig; // Se pasa al siguiente nodo.  

        } // Fin else if __esImprime

        // Si es repite:
        else if(__esRepite(nodo->token) == 0)
        { 
            // Guarda el número de línea de REPITE:
            unsigned int num_lin_rep = nodo->num_linea;

            // Se verifica que el token sea un elemento:
            if((nodo->sig) && __esElem(nodo->sig->token) == 0)
            {
                nodo = nodo->sig; // Se pasa al nodo.

                    // Se verifica que el token sea VECES:
                    if((nodo->sig) && __esVeces(nodo->sig->token) == 0)
                    {    
                        nodo = nodo->sig; // Se pasa al nodo.

                        // Se verifica que haya un nodo siguiente:
                        if(nodo->sig)
                        {
                            nodo = nodo->sig; // Se pasa al nodo.
                            
                            // Se verifica que
                            // haya un nodo siguiente:
                            if(nodo->sig)
                            { 
                                // Mientras hayan sentencias válidas
                                // se recorren hasta hallar FINREP
                                // o hallar FINPROG
                                while(nodo = __esSent(nodo))
                                {
                                    // Si es FINREP o se llega al final del programa:
                                    if(__esFinRep(nodo->token) == 0 || !nodo->sig)
                                    {   
                                        if(nodo->sig)
                                            nodo = nodo->sig; // Se pasa al siguiente nodo.
                                        break; // No hubo errores.
                                    }
                                }
                           
                                // Se verifica si se llegó al final de la lista:
                                // Si se llegó al final, hubo error, pues falta FINREP:
                                if(!(nodo->sig))
                                {
                                    printf("ERROR de sintaxis en línea [%u] --En declaración REPITE se esperaba --> FINREP.\n", num_lin_rep);
                                    num_errores++;

                                    if(nodo->sig)
                                        nodo = nodo->sig; // Se pasa al siguiente nodo.
                                }
                            } // Fin if nodo = __esSent  
                            else
                                err_sent++; // Hubo un error de sentencia o declaración.
                        } // Fin if nodo->sig.
                        else
                            err_sent++; // Hubo un error de sentencia o declaración.
                          
                    } // Fin if __esVeces.
                    else
                    {                
                        // Hubo error, falta VECES:
                        printf("ERROR de sintaxis en línea [%u] --En declaración REPITE se esperaba --> VECES.\n", nodo->num_linea);
                        num_errores++;
                    }
            } // Fin if __esElem
            else
            {
                // Hubo error, no es un elemento:
                printf("ERROR de sintaxis en línea [%u] --No es un elemento válido --> %s.\n", nodo->num_linea, nodo->token);
                num_errores++;
            }            
        } // Fin de else if de __esRepite

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
                                            printf("ERROR de sintaxis en línea [%u] --No se encuentra --> FINSI.\n", nodo->num_linea);
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
        // Se verifica que el token siguiente sea un signo de '=':
        if((nodo->sig) && __esAsig(nodo->sig->token) == 0)
        {            
            nodo = nodo->sig; // Se pasa al nodo siguiente.

            // Se verifica si el token es un ELEM:
            if((nodo->sig) && __esElem(nodo->sig->token) == 0)
            {
                nodo = nodo->sig; // Se pasa al nodo.  
                
                // Se verifica si el token siguiente es un operador aritmético:
                if((nodo->sig) && __esOpAr(nodo->sig->token) == 0)
                {  
                    nodo = nodo->sig; // Se pasa al nodo.
                    
                    // Se verifica si el token es un ELEM:
                    if((nodo->sig) && __esElem(nodo->sig->token) == 0)
                    {
                        nodo = nodo->sig; // Se pasa al nodo.
                        
                        // Si lo que sigue es realmente una sentencia de
                        // asignación:
                        if(__esAsig(nodo->sig->token) == 0)
                        {
                            printf("ERROR de sintaxis en línea [%u] --No es posible operar una asignación --> %s.\n", nodo->num_linea, nodo->token);
                            num_errores++;
                        }
                        
                        if(nodo->sig)
                            nodo = nodo->sig; // Se pasa al siguiente nodo.
                    }
                    // Si no es un elemento:
                    else
                    {    
                        printf("[ERROR de sintaxis en línea [%u] --Elemento no encontrado --> %s.\n", nodo->num_linea, nodo->token);
                        num_errores++;
                    }   
                } // Fin if __esOpAr.
                else if(nodo->sig)
                    nodo = nodo->sig; // Se pasa al nodo.
            } // Fin if __esElem.
            else
            {    
                printf("ERROR de sintaxis en línea [%u] --Elemento no encontrado --> %s.\n", nodo->num_linea, nodo->token);
                num_errores++;
            }     
        } // Fin if __esAsig
        else
            err_var++;
    } // Fin if __esVariable.

    // Si se encuentra una cadena de texto o una variable sin utilizar:
    if(__esTexto(nodo->token) == 0 || err_var != 0)
    {
        printf("ERROR de sintaxis en línea [%u] --Elemento sin utilizar --> %s.\n", nodo->num_linea, nodo->token);
        num_errores++;
        
        // Si hay un nodo después,
        // entonces se pasa a ese nodo:
        if(nodo->sig)
            nodo = nodo->sig;
    }

    // Si hubo error de sentencia o declaración:
    if(err_sent != 0)
    {    
        printf("ERROR de sintaxis en línea [%u] --No es una sentencia o declaración válida --> %s.\n", nodo->num_linea, nodo->token);
        num_errores++;
        
        // Si hay un nodo después,
        // entonces se pasa a ese nodo:
        if(nodo->sig)
            nodo = nodo->sig; // Se pasa al siguiente nodo.
    }

    // Se retorna el puntero al nodo siguiente
    // si no es el final de la lista:
    if(nodo)
        return nodo;
    else
        return NULL; // Si es el final de la lista
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicia el analizador sintáctico,
 * primero hace una análisis de la estructura
 * principal del programa analizando si posee
 * las palabras reservadas PROGRAMA y el identificador 
 * del nombre del programa.
 * Posteriormente llama a la función __esSent hasta llegar
 * a la palabra reservada FINPROG.
 * 
 * ENTRADA: Una lista de tipo listaTok.
 * 
 * SALIDA: Entero que representa el número de errores 
 * encontrados durante el análisis sintáctico.
 * 
 */
int iniAnalSin(listaTok *lista) 
{
    // Si la lista es NULL:
    if(!lista)
        return num_errores++;

    // Nodo auxiliar para recorrer la lista:
    nodo_Tok *aux = lista->raiz;

    //-----------INICIA EL ANÁLISIS----------

    // Se analiza la estructura principal del programa:

    // Verifica que se halle la palabra reservada PROGRAMA:
    if(strncmp(aux->token, "PROGRAMA", strlen(aux->token)+1) == 0)
         aux = aux->sig;
    
    // Si PROGRAMA no se encuentra:
    else
    {
        printf("ERROR de sintaxis en l%cnea [%u] --No se encuentra palabra reservada --> PROGRAMA.\n", 161, aux->num_linea);
        num_errores++;
    }

    // Verifica que se halle el nombre del programa:
    if(strncmp(aux->token, "[id] ID01", strlen(aux->token)+1) == 0)
        aux = aux->sig;
    
    // Si el nombre del programa no se encuentra:
    else
    {
        printf("ERROR de sintaxis en l%cnea [%u] --No se encuentra --> nombre del programa.\n", 161, aux->num_linea);
        num_errores++;
    }
    
    // Se llama a __esSent para verificar que todas
    // las sentencias de la lista sean válidas:
    while(aux->sig)
    {
        printf("%s\n", aux->token);
        aux = __esSent(aux); // Se continúa el ciclo con el siguiente nodo.
    }    
    
    // Verifica que se halle la palabra reservada FINPROG al final del programa:
    if(strncmp(aux->token, "FINPROG", strlen(aux->token)+1) != 0)
    {
        printf("ERROR de sintaxis en l%cnea [%u] --No se encuentra palabra reservada --> FINPROG.\n", 161, aux->num_linea);
        num_errores++;
    }

    //----------CONCLUYE EL ANÁLISIS----------

    // Retorna copia del contador global num_errores:
    return num_errores;
}

