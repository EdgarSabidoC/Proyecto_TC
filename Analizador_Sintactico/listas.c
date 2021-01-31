#include "listas.h"


//-------------------------FUNCIONES DE LA LISTA DE TOKENS--------------------------


/* 
 * DESCRIPCIÓN:
 * Esta función aparta un bloque de memoria
 * en la memoria dinámica y crea un nodo 
 * de tipo nood_Tok (a partir del token y de su 
 * número de línea) para una lista de tipo listaTok,
 * 
 * ENTRADA: Un puntero de a una cadena (token)
 * 			y un entero sin signo (número de línea del token)
 * 
 * SALIDA: Puntero al nodo.
 * 
 */
nodo_Tok *creaNodoTok(char *token, unsigned int num_linea)
{
    nodo_Tok *apu;

	apu = malloc(sizeof(nodo_Tok)); // Creamos un espacio de memoria del tamaño de la struct nodo_Tok

	if (apu) //Equivalente a apu != NULL
	{
		memcpy(apu->token, token, strlen(token)+1); // Se copia el token en el nodo.	
		apu->num_linea = num_linea; // Se guarda el número de línea del token.

		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".
}

/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por un nodo en una lista
 * de tipo listaTok.
 * 
 * ENTRADA: Un puntero de tipo nodo_Tok (nodo).
 * 
 * SALIDA: 0 si la operación fue exitosa, 
 *         1 si la operación no fue exitosa.
 * 
 */
int liberaNodoTok(nodo_Tok *nodo)
{
    if(nodo) //Equivalente a nodo != NULL
	{
		// Se libera la memoria ocupada por el nodo:
		free(nodo->token); // Se libera la memoria del string del nodo.
		free(nodo); // Se libera la memoria del nodo.
		nodo = NULL;

		// Si la operación fue exitosa:
		return 0;
	}

	// Si no se pudo liberar la memoria del nodo:
	return 1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicializa una lista de tipo
 * listaTok apuntando su raíz a NULL y
 * asignando un tamaño de 0.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaTok.
 * 
 * SALIDA: N/A.
 * 
 */
void iniListaTok(listaTok *Lista)
{
    Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por una lista de tipo
 * listaTok.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaTok.
 * 
 * SALIDA: N/A.
 * 
 */
void liberaListaTok(listaTok *lista)
{

    nodo_Tok *aux; // Apuntador auxiliar
	
	while (lista->raiz) // Mientras la raíz sea diferente de NULL
    {
		aux = lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
	    lista->raiz = lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		
		liberaNodoTok(aux); // Se libera el nodo "aux"
    }

	lista->raiz = NULL;
	lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* 
 * DESCRIPCIÓN:
 * Esta función ingresa un nodo de tipo
 * nodo_Tok al final de una lista de tipo 
 * listaTok con una operación pushBack.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaTok
 * 			y un puntero a un nodo de tipo 
 * 			nodo_Tok (nodo).
 * 
 * SALIDA: N/A.
 * 
 */
void pushBackTok(listaTok *Lista, nodo_Tok *nodo)
{
    if (nodo) //Equivalente a nodo != NULL
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_Tok *apu;

			// Se recorre toda la lista hasta que
			// apu apunte al último nodo.
			apu = Lista->raiz;
			while (apu->sig)
				apu = apu->sig;
				
			// Se inserta nodo despues de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}


/* 
 * DESCRIPCIÓN:
 * Esta función busca un nodo de tipo nodo_Tok
 * dentro de una lista de tipo listaTok y
 * lo retorna si lo encuentra.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaTok
 * 			y un puntero a una cadena (token).
 * 
 * SALIDA: Puntero a un nodo de tipo nodo_Tok.
 * 
 */
nodo_Tok *buscaTok(listaTok *Lista, char *token)
{
    nodo_Tok *apu;
	
	// Se recorre la lista buscando la cadena:
	apu = Lista->raiz;

	while (apu != NULL)
	{
		// Si se encuentra el token en la lista:
		if(strncmp(token, apu->token, strlen(token)+1) == 0) // Compara las cadenas.
		{
			return apu; // Se retorna el puntero al token.
		}
		apu = apu->sig; // Se pasa al nodo siguiente.
	}

	// Si el token no se encuentra en la lista:
	return NULL;	
}

