#include "listas.h"

//--------------------------FUNCIONES PARA LISTA DE VARIABLES NUMÉRICAS--------------------------

// Lista de nodos eliminados:
nodo_VarNum *basura_num = NULL;

nodo_VarNum *creaNodoVarNum(char *variable, unsigned int id)
{
	nodo_VarNum *apu;
	
	if (basura_num == NULL) // Equivalente a if (!basura)
		apu = (nodo_VarNum *)malloc(sizeof(nodo_VarNum)); // Creamos un espacio de memoria del tamaño de la struct nodo_VarNum
	else
	{
		apu = basura_num; // Al nodo "apu" le asignamos el nodo "basura".
		basura_num = basura_num->sig; // El nodo "basura" apunta al nodo siguiente.
	}

	if (apu) //Equivalente a apu != NULL
	{
		strncpy(apu->nombre, variable, 16); // Se copia el nombre de la variable.
		apu->ID = id; // Se asigna el valor del ID.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Retornamos el nodo "apu".
}

int liberaNodoVarNum(nodo_VarNum *nodo)
{
	if(nodo) //Equivalente a nodo != NULL
	{
		nodo->sig = basura_num; // el nodo siguiente pasa a ser el nodo basura.
		basura_num = nodo; // basura pasa a convertirse en el nodo
		
		//free (nodo->sig);
		
		return 0;
	}
	return -1;
}

void iniListaVarNum(listaVarNum *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}

void liberaListaVarNum(listaVarNum *Lista)
{
	nodo_VarNum *aux; // Apuntador auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		liberaNodoVarNum(aux); // Se libera el nodo "aux"
	}

	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}

void pushBackVarNum(listaVarNum *Lista, nodo_VarNum *nodo)
{
	if (nodo) //Equivalente a nd != NULL
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_VarNum *apu;

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

nodo_VarNum *buscaVarNum(listaVarNum *Lista, char *nombre)
{	
	nodo_VarNum *apu;
	
	// Se recorre la lista buscando la cadena:
	apu = Lista->raiz;

	while (apu != NULL)
	{
		// Si se encuentra la cadena:
		if(strncmp(nombre, apu->nombre, 17) == 0)
		{
			return apu;
		}
		apu = apu->sig;
	}

	// Si la cadena no se encuentra:
	return NULL;	
}

//int borraNodoVarNum(listaVarNum *Lista, nodo_VarNum *nd);

void imprimeListaVarNum(FILE *archivo, listaVarNum *Lista)
{
	if(archivo) // Equivalente a archivo != NULL
	{
		if(!Lista->tam) // Si la lista esta vacia.
			fprintf(archivo, "[]");
		else
		{
			nodo_VarNum *aux = Lista->raiz; // Nodo auxiliar
	
      		fprintf(archivo, "[");
	  		
			while(aux->sig) //Equivalente a aux != NULL
      		{
    			fprintf (archivo, "%s, ID%u", aux->nombre, aux->ID);
        		aux = aux->sig;
    		}
			fprintf (archivo, "%s, ID%u", aux->nombre, aux->ID); // Se imprime el último nodo.
		}
	}
}


//--------------------------FUNCIONES PARA LISTA DE CADENAS DE TEXTO--------------------------

// Lista de nodos eliminados:
nodo_Txt *basura_txt = NULL;

nodo_Txt *creaNodoText(char *cadena, unsigned int id)
{
	nodo_Txt *apu;

	apu = (nodo_Txt *)malloc(sizeof(nodo_Txt)); // Creamos un espacio de memoria del tamaño de la struct nodo_Txt

	if (apu) //Equivalente a apu != NULL
	{
		// Se crea un arreglo dinámico del tamaño de la cadena:
		apu->cadena = (char *)malloc(strlen(cadena)+1 * sizeof(char));

		strncpy(apu->cadena, cadena, strlen(cadena)+1); // Se copia la cadena en el nodo.
		apu->ID = id; // Se asigna el valor del ID.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".
}

int liberaNodoTxt(nodo_Txt *nodo)
{
	if(nodo) //Equivalente a nodo != NULL
	{
		free(nodo->cadena); // Se libera la memoria del string del nodo.
		//nodo->sig = basura_txt; // el nodo siguiente pasa a ser el nodo basura.
		//basura_txt = nodo; // basura pasa a convertirse en el nodo
		
		return 0;
	}
	return -1;
}

void iniListaTxt(listaText *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}

void liberaListaTxt(listaText*Lista)
{
	nodo_Txt *aux; // Apuntador auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		liberaNodoTxt(aux); // Se libera el nodo "aux"
	}

	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}

void pushBackTxt(listaText *Lista, nodo_Txt *nodo)
{
	if (nodo) //Equivalente a nd != NULL
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_Txt *apu;

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

nodo_Txt *buscaTxt(listaText *Lista, char *cadena)
{
	nodo_Txt *apu;
	
	// Se recorre la lista buscando la cadena:
	apu = Lista->raiz;

	while (apu != NULL)
	{
		// Si se encuentra la cadena:
		if(strncmp(cadena, apu->cadena, 16) == 0)
		{
			return apu;
		}
		apu = apu->sig;
	}

	// Si la cadena no se encuentra:
	return NULL;
}

//int borraNodoTxt(listaText *Lista, nodo_Txt *nd);

void imprimeListaTxt(FILE *archivo, listaText *Lista)
{
	if(archivo) // Equivalente a archivo != NULL
	{
		if(!Lista->tam) // Si la lista esta vacia.
			fprintf(archivo, "[]");
		else
		{
			nodo_Txt *aux = Lista->raiz; // Nodo auxiliar
	
      		fprintf(archivo, "[");
	  		
			while(aux->sig) //Equivalente a aux != NULL
      		{
    			fprintf (archivo, "%s, ID%u", aux->cadena, aux->ID);
        		aux = aux->sig;
    		}
			fprintf (archivo, "%s, ID%u", aux->cadena, aux->ID); // Se imprime el último nodo.
		}
	}
}
