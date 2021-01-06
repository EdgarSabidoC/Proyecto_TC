#include "sintax.h"

/* Crea una lista de los tokens de una línea */
listaTok *crearListaToks();


/* Valida si la cadena es una palabra reservada */
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


/* Valida si la cadena es un OPERADOR ARITMÉTICO. */
int __esOpAr(char *cadena) 
{ 
    // Se verifica si es un operador aritmético:
    if(strstr(cadena, "[op_ar]"))
    {       
        return 0; // Si es operador aritmético.
    }

    // Si no es un operador aritmético:
    return 1;
}


/* Valida si la cadena es un NÚMERO */
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


/* Valida si la cadena es un OPERADOR RELACIONAL */
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


/* Valida si la cadena se trata de una variable */
int __esVariable(char *token)
{
    if(strstr(token,"[id]"))
        return 0; // Si es variable.
    
    // Si no es una variable:
    return 1;
    
}


/* Identifica si el token es un elemento */
int __esElem(char *token)
{
    if(__esVariable(token))
        return 0; // Es un elemento, es una variable.
    
    else if(__esVal(token))
        return 0; // Es un elemento, es un valor.
    
    // No es un elemento:
    return 1;
}


/* Identifica si es una comparación */
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


/* Identifica si la sentencia es de lectura */
int __esLee(char *token, unsigned int num_linea)
{
    if(__esVariable(token) == 0)
            return 0; // No hubo errores.

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un identificador válido", num_linea);   
    return 1;
    
}


/* Identifica si la sentencia es de impresión */
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


/* Identifica si la sentencia es de repite */
int __esRepite(nodo_Tok *nodo, unsigned int num_linea)
{
    if(__esElem(nodo->token) == 0)
    {
        // Se pasa al token siguiente:
        nodo = nodo->sig;

        if(strncmp(nodo->token,"VECES", strlen(nodo->token)+1) == 0)
        {
            // Se pasa al token siguiente:
            nodo = nodo->sig;

            if(__esSents(nodo) == 0)
            {
                // Se pasa al token siguiente:
                nodo = nodo->sig;

                if(strncmp(nodo->token,"FINREP", strlen(nodo->token)+1) == 0)
                    return 0; // No hubo errores.

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

    // Hubo errores:
    printf("ERROR de sintaxis en línea [%u] --No es un elemento válido.\n", num_linea);
    return 1;
}


/* Identifica si la sentencia es de Si-Entonces o un Si-Entonces-Sino */
int __esSiEnt(nodo_Tok *nodo, unsigned int num_linea)
{
    if(__esCompara(nodo, num_linea) == 0)
    {
        nodo = nodo->sig; // Se pasa al nodo siguiente.

        if(strncmp(nodo->token, "ENTONCES", strlen(nodo->token)+1) == 0)
        {
            nodo = nodo->sig; // Se pasa al nodo siguiente.

            if(nodo = __esSents(nodo) == 0)
            {
                nodo = nodo->sig; // Se pasa al nodo siguiente.
                
                // Finaliza en FINSI:
                if(strncmp(nodo->token, "FINSI", strlen(nodo->token)+1) == 0)
                    return 0; // No hubo errores.

                // Es un SI-ENTONCES-SINO:
                else if(strncmp(nodo->token, "SINO", strlen(nodo->token)+1) == 0)
                {
                    nodo = nodo->sig; // Se pasa al nodo siguiente.

                    if(nodo = __esSents(nodo))
                    {
                        nodo = nodo->sig; // Se pasa al nodo siguiente.

                        if(strncmp(nodo->token, "FINSI", strlen(nodo->token)+1) == 0)
                            return 0; // No hubo errores.
                        
                        // Hubo error, falta FINSI:
                        printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", num_linea);
                        return 1;
                    
                    } // Fin if

                    // Hubo error, sentencia no válida:
                    printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", num_linea);
                    return 1;

                } // Fin else if

                // Hubo error, falta FINSI:
                printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (FINSI).\n", num_linea);
                return 1;

            } // Fin if

            // Hubo error, sentencia no válida:
            printf("ERROR de sintaxis en línea [%u] --Sentencia no válida.\n", num_linea);
            return 1;

        } // Fin if

        // Hubo error, sentencia no válida:
        printf("ERROR de sintaxis en línea [%u] --Falta palabra reservada (ENTONCES).\n", num_linea);
        return 1;

    } // Fin if

    // Hubo error, sentencia no válida:
    printf("ERROR de sintaxis en línea [%u] --No es una comparación.\n", num_linea);
    return 1;
}


/* Identifica si es una asginación */
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


/* Identifica si la cadena es una operación aritmética */
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


/* Identifica si se trata de una sentencia válida */
int __esSent(listaTok *lista, unsigned int num_linea)
{
    nodo_Tok *aux = lista->raiz;
    
    unsigned int error = 0;

    if(__esReservada(aux->token) == 0)
    {   
        // Si empieza con LEE:
        if(strncmp(aux->token,"LEE", strlen(aux->token)+1) == 0)
        {   
            // Se pasa al token siguiente:
            aux = aux->sig;
            
            error = __esLee(aux->token, num_linea);

            return error; // Se retorna el valor de error.
        }

        // Si empieza con IMPRIME:
        else if(strncmp(aux->token, "IMPRIME", strlen(aux->token)+1) == 0)
        {
            // Se pasa al token siguiente:
            aux = aux->sig;

            error = __esImprime(aux->token, num_linea);

            return error; // Se retorna el valor de error.
        }

        // Si es repite:
        else if(strncmp(aux->token, "REPITE", strlen(aux->token)+1) == 0)
        {   
            // Se pasa al token siguiente:
            aux = aux->sig;
            
            error = __esRepite(aux, num_linea);

            return error; // Se retorna el valor de error.

        } // Fin de else if de repite

        // Si es condicional si-entonces o si-entonces-sino:
        else if(strncmp(aux->token, "SI", strlen(aux->token)+1) == 0)
        {
            // Se pasa al token siguiente:
            aux = aux->sig;  

            error = __esSiEnt(aux, num_linea); 

            return error; // Se retorna el valor de error.

        } // Fin else if de condicional 

    } // Fin if


    // Si es una asignación:
    else if((error = __esVariable(aux->token)) == 0)
    {
        aux = aux->sig; // Se pasa al token siguiente.

        if ((error = __esAsig(aux, num_linea)) == 0)
        {
            aux = aux->sig;

            if(aux) // Si hay otro nodo después:
                error = __esOperArit(aux, num_linea);
        
        } // Fin if

        return error; // Se retorna el valor de error.

    } // Fin else if de asignación

    // Hubo errores
    printf("ERROR de sintaxis en línea [%u] --No es una sentencia válida.\n", num_linea);
    error = 1;

    // Se retorna el resultado del error, 0 si no hubo, 1 si hubo:
    return error;
}


/* Identifica si es SENTS */
int __esSents(nodo_List *lista)
{
    nodo_List *aux = lista->raiz_lista_tok;

    if(__esSent(lista->raiz_lista_tok, lista->num_linea) == 0)
    {
        aux = aux->sig_lista; // Se pasa al siguiente nodo (sublista).

        if(aux) // Si la sublista no está vacía.
            if(__esSents(aux->sig_lista) == 0)
                printf("Hola MUndo");
    }
}