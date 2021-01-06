#include "listas.h"


//-------------------------FUNCIONES DE LA LISTA DE TOKENS--------------------------



nodo_Tok *creaNodoTok(char *token)
{
    nodo_Tok *apu;

	apu = (nodo_Tok *)malloc(sizeof(nodo_Tok)); // Creamos un espacio de memoria del tamaño de la struct nodo_Txt

	if (apu) //Equivalente a apu != NULL
	{
		// Se crea un arreglo dinámico del tamaño del token:
		apu->token = (char *)malloc(strlen(token)+1 * sizeof(char));

		strncpy(apu->token, token, strlen(token)+1); // Se copia el token en el nodo.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".
}



int liberaNodoTok(nodo_Tok *nodo)
{
    if(nodo) //Equivalente a nodo != NULL
	{
		// Se libera la memoria ocupada por el nodo:
		free(nodo->token); // Se libera la memoria del string del nodo.
		free(nodo); // Se libera la memoria del nodo.

		// Si la operación fue exitosa:
		return 0;
	}

	// Si no se pudo liberar la memoria del nodo:
	return 1;
}



void iniListaTok(listaTok *Lista)
{
    Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}



void liberaListaTok(listaTok *lista)
{

    nodo_Tok *aux; // Apuntador auxiliar
	
	while (lista->raiz) // Mientras la raíz sea diferente de NULL
    {
		aux = lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
	    lista->raiz = lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		
		liberaNodoTok(aux); // Se libera el nodo "aux"
    }

	lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}



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



//-------------------------FUNCIONES DE LA LISTA DE LISTAS--------------------------


/* Crea un nodo de listas */
nodo_List *creaNodoList(listaTok *lista_tok, unsigned int num_linea)
{
    nodo_List *apu;

	apu = (nodo_List *)malloc(sizeof(nodo_List)); // Creamos un espacio de memoria del tamaño de la struct nodo_Txt

	if (apu) //Equivalente a apu != NULL
	{
        apu->raiz_lista_tok->raiz = lista_tok->raiz; // Cada nodo apunta a la raiz de cada lista de tokens.
		apu->num_linea = num_linea; // Cada nodo tiene un número de línea.
		apu->sig_lista = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".   
}



int liberaNodoList(nodo_List *nodo_lista)
{
    if(nodo_lista) //Equivalente a nodo != NULL
	{
		// Se libera la memoria ocupada por el nodo:
		liberaListaTok(nodo_lista->raiz_lista_tok); // Se libera la memoria del string del nodo.
		free(nodo_lista); // Se libera la memoria del nodo.

        nodo_lista = NULL;

		// Si la operación fue exitosa:
		return 0;
	}

	// Si no se pudo liberar la memoria del nodo:
	return 1;
}



void iniListaList(listaList *lista_tok)
{
    lista_tok->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	lista_tok->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}



void liberaListaList(listaList *lista_tok)
{
    nodo_List *aux; // Apuntador auxiliar
	
	while (lista_tok->raiz) // Mientras la raíz sea diferente de NULL
    {
		aux = lista_tok->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
	    lista_tok->raiz = lista_tok->raiz->sig_lista; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		
		liberaNodoList(aux); // Se libera el nodo "aux"
    }

	lista_tok->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}



void pushBackLista(listaList *lista_tok, nodo_List *nodo_lista)
{
    if (nodo_lista) //Equivalente a nd != NULL
	{
		if (!lista_tok->raiz)
		   lista_tok->raiz = nodo_lista;
		else
		{
			nodo_List *apu;

			// Se recorre toda la lista hasta que
			// apu apunte al último nodo.
			apu = lista_tok->raiz;
			while (apu->sig_lista)
				apu = apu->sig_lista;
				
			// Se inserta nodo despues de apu;	
			apu->sig_lista = nodo_lista;
			nodo_lista = NULL;
		}	
		lista_tok->tam++;
	}
}