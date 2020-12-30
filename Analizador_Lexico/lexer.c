#include "lexer.h"

// VARIABLES

typedef struct _variable_numerica 
{
    char nombre[17]; // Nombre del identificador
    char *id; // Clave del identificador
    int valor; // Número
    unsigned int num_linea;
} num_var;

typedef struct _cadena_texto
{
    char nombre[17]; // Nombre del identificador
    char *id; // Clave del identificador
    char *cadena; // Número
    unsigned int num_linea;
} var_txt;

/* TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO */

// operadores relacionales: ">", "<", "=="

// operadores aritméticos: '+', '-', '*', '/'

// asignacion: '='

//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------


/* Valida si la cadena es una palabra reservada */
bool __esReservada(char *str)
{
    unsigned int i = 0;
    char *palabras_reservadas[11] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE"};

    while(i < 11)
    {
        if(strncmp(str, palabras_reservadas[i], sizeof(palabras_reservadas[i])) == 0)
        {   
            return (true);
        }
        i++;
    }
    return (false);
    
}


/* Valida si el token es una variable o una palabra reservada */
bool __esVarValid(char *token, unsigned int num_linea)
{
    // Se verifica si el primer elemento es una letra:
    if (isalpha(*token) != 0)
    {   
        // Se valida si es o no una palabra reservada:
        if(__esReservada(token) == true)
        {
            printf("Es palabra reservada: ");
            return (false);
        }

        // Se valida si es un nombre de variable correcto:
        char *tmp = token;
        
        while(isalpha(*tmp) != 0 || isdigit(*tmp) != 0)
        {
            // El puntero se mueve al siguiente char:
            tmp = tmp + 1;

        } // Fin while

        // Si el char al que apunta tmp es nulo:
        if(*tmp == '\0')
        {   
            printf("Es una variable: ");
            return (true); 
        }
        
        // Si el char al que apunta tmp es un símbolo:
        else
            printf("ERROR en línea [%u] --Caracteres no válidos en variable: ", num_linea);    
    }

    // Si el token inicia con número
    else if(isdigit(*token) != 0)
    {
        printf("ERROR en la línea [%u] --Las variables no pueden iniciar con números: ", num_linea);
    }

    // Si el token inicia con un símbolo:
    else
    {
        printf("ERROR en la línea [%u] --Primer caracter de variable no válido, sólo se admiten letras: ", num_linea);
    }
    
    return (false);
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


/* La función almacena las líneas del archivo dentro de un vector */
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned caracteres, char cadena[lineas][caracteres])
{
    unsigned int i = 0;

    while(1)
    {
        // Se guarda la línea del archivo en el arreglo:
        //if(fgets(cadena[i], chars, archivo) != NULL) 
        if(fgets(cadena[i], sizeof(cadena[i]), archivo) != NULL)
        {
            printf("%s", cadena[i]);
            i++;
        }
        else
        {
            break;
        }
    }
}


/* Genera un archivo .lex e imprime una cadena en él */
void generarLexer(char *cadena)
{
    FILE *lexer = fopen("Programa.lex", "a+");

    // Se imprime la cadena en el archivo .lex:
    fprintf(lexer, "%s", cadena);

    fclose(lexer);
}


/* Retorna 'true' si el char es un OPERADOR ARITMÉTICO. */
bool __esOpAr(char *cadena, unsigned int num_linea) 
{ 
    unsigned int i = 0;
    char *op_ar[4] = {"+","-","*","/"};
    char *asignacion = "=";

    // Se verifica si es un operador aritmético:
    while(i < 4)
    {
        if(strncmp(cadena, op_ar[i], sizeof(op_ar[i])) == 0)
        {       
            printf("Es operador aritmético: ");
            return (true); 
        }
        i++;
    }
    
    // Se verifica si es una asignación:
    if(strncmp(cadena, asignacion, sizeof(asignacion)) == 0)
    {
        printf("Es asignación: ");
        return (false);
    }

	// Se verifica si el primer elemento es una letra:
    else if (isalpha(*cadena) != 0)
    {    
        // Se valida si es un nombre de variable correcto:
        char *tmp = cadena;
        
        while(isalpha(*tmp) != 0 || isdigit(*tmp) != 0)
        {
            // El puntero se mueve al siguiente char:
            tmp = tmp + 1;

        } // Fin while

        if(*tmp == '\0')
            printf("Es una variable: ");        
        else
            printf("ERROR léxico en línea [%u] --Caracteres no válidos en variable: ", num_linea);
        return (false);      
    }

    // Si el primer char es un número:
    else if (isdigit(*cadena) != 0)
    {
        char *tmp = cadena;

        while(isdigit(*tmp) != 0)
            tmp++;
        
        // Si el char al que apunta tmp es nulo:
        if(*tmp == '\0')
            printf("Es un número: ");
        
        // Si el char al que apunta tmp es una letra:
        else if(isalpha(*tmp) != 0)
            printf("ERROR en línea [%u] --Las variables no pueden iniciar con un número: ", num_linea);
        
        // Si el char al que apunta tmp es un símbolo:
        else
            printf("ERROR léxico en línea [%u] --Variable numérica contiene caracteres no válidos: ");
        
        return (false);
    } // Fin else if    

    // Si en la cadena hay un símbolo no válido:
    else
    {
        printf("ERROR léxico en la línea [%u] --Operador o símbolo no válido: ", num_linea);
        return (false);
    }
    
}


/* Valida si la cadena es una PALABRA RESERVADA */
bool __esOpRel(char *cadena, unsigned int num_linea)
{
    unsigned int i = 0;
    char *op_rel[3] = {"<", ">", "=="};

    // Se verifica si es un operador aritmético:
    while(i < 3)
    {
        if(strncmp(cadena, op_rel[i], sizeof(op_rel[i])) == 0)
        {       
            printf("Es operador relacional: ");
            return (true); 
        }
        i++;
    } // Fin while

    // Se verifica si el primer elemento es una letra:
    if (isalpha(*cadena) != 0)
    {    
        // Se valida si es un nombre de variable correcto:
        char *tmp = cadena;
        
        while(isalpha(*tmp) != 0 || isdigit(*tmp) != 0)
        {
            // El puntero se mueve al siguiente char:
            tmp = tmp + 1;

        } // Fin while

        if(*tmp == '\0')
            printf("Es una variable: ");        
        else
            printf("ERROR en línea [%u] --Caracteres no válidos en variable: ", num_linea);
        return (false);      
    }

    // Si el primer char es un número:
    else if (isdigit(*cadena) != 0)
    {
        char *tmp = cadena;

        while(isdigit(*tmp) != 0)
            tmp++;
        
        // Si el char al que apunta tmp es nulo:
        if(*tmp == '\0')
            printf("Es un número: ");
        
        // Si el char al que apunta tmp es una letra:
        else if(isalpha(*tmp) != 0)
            printf("ERROR léxico en línea [%u] --Las variables no pueden iniciar con un número: ", num_linea);
        
        // Si el char al que apunta tmp es un símbolo:
        else
            printf("ERROR léxico en línea [%u] --Variable numérica contiene caracteres no válidos: ");
        
        return (false);
    } // Fin else if    

    // Si en la cadena hay un símbolo no válido:
    else
    {
        printf("ERROR léxico en la línea [%u] --Operador o símbolo no válido: ", num_linea);
        return (false);
    }
}


/* Valida si aparece un operador aritmético en la cadena */
bool __estaOpAr(char *cadena)
{
    unsigned int i = 0;
    char *op_ar = "+-*/";
    
    while(i < 4)
    {
        if(strchr(cadena, op_ar[i]))
        {       
           return (true);
        }
        i++;
    }
    return (false);
}


/* Valida si aparece un operador relacional en la cadalena */
bool __estaOpRel(char *cadena)
{
    unsigned int i = 0;
    char *op_rel[3] = {"<", ">", "=="};
    
    while(i < 3)
    {
        if(strstr(cadena, op_rel[i]))
        {       
           return (true);
        }
        i++;
    }
    return (false);
}


/* Valida si el token es una cadena de texto */
bool __esTexto(char *token, unsigned int num_linea)
{
    // Se verifica si es una palabra reservada:
    if(__esReservada(token) == true)    
    {
        printf("Es palabra reservada: ");
         return (false);
    }

    // Si no es una palabra reservada, entonces es una cadena:
    else 
    {
        printf("Es una cadena de texto: ");
        return (true);
    }
}


/* Verifica si el char que se le pasa es un # */
bool __esComentario(char ch)
{
    char comentario = '#';

    if(ch == comentario)
        return (true);
    return (false);
}


/* Verifica si una variable numérica está en la tabla de símbolos */
bool __estaEnTabSim(char *str, char **tabla_sim)
{
    unsigned int i = 0;

    while(tabla_sim[i])
    {
        if(strncmp(str, tabla_sim[i], sizeof(tabla_sim[i])) == 0)
        {   
            return (true);
        }
        i++;
    }
    return (false);
}


/* Genera los tokens cuando hay strings en la línea VERIFICADA*/
void genTokTex(char *cadena, unsigned int num_linea)
{
    unsigned int cont_txt = 0;
    char *token;

    // Se genera el primer token:
    token = strtok(cadena, " \t");

    // Se elimina el último espacio de la cadena:
    token[strlen(token)-1] = '\0';

    while(token != NULL) 
    {  
        // Se ignora si es comentario:
        if(__esComentario(*token) == true)
        {
            break;
        }
        
        //  Se verifica si es cadena de texto:
        if(__esTexto(token, num_linea) == true)
        {
            printf("%s\n", token);
        }

        // Es palabra reservada:
        else
        {
            printf("%s\n", token);
        }

        // Se genera el token siguiente:
        token = strtok(NULL, "\n");

    }// Fin While
}


/* Genera los tokens cuando hay declaración y asignación de variables numéricas en la línea VERIFICADA*/
void genTokVar(char *cadena, unsigned int num_linea)
{
    unsigned int cont_var;
    char *token;

    // Se genera el primer token:
    token = strtok(cadena, " \n\t");
        
    while(token != NULL) 
    {  
        // Se ignoran los comentarios:
        if(__esComentario(*token) == true)
        {
            break;
        }

        __esVarValid(token, num_linea);

        // Se imprime el token en pantalla:
        printf("%s\n", token);

        // Se generan los tokens siguientes:
        token = strtok(NULL, " \n\t");

    }// Fin While
}


/* Genera los tokens cuando hay un operador relacional en la línea */
void genTokRel(char *cadena, unsigned int num_linea)
{
    char *token;

    // Se genera el primer token:
    token = strtok(cadena, " \n\t");
        
    while(token != NULL) 
    {  
        // Se ignoran los comentarios:
        if(__esComentario(*token) == true)
        {
            break;
        }

        if(__esOpRel(token, num_linea) == true)
        {
            printf("%s\n", token);
        }

        else printf("%s\n", token);

        // Se generan los tokens siguientes:
        token = strtok(NULL, " \n\t");

    }// Fin While
}


/* Genera los tokens cuando hay un operador aritmético en la línea VERIFICADA*/
void genTokAr(char *cadena, unsigned int num_linea)
{
    char *token;

    // Se genera el primer token:
    token = strtok(cadena, " \n\t");
        
    while(token != NULL) 
    {  
        // Se ignoran los comentarios:
        if(__esComentario(*token) == true)
        {
            break;
        }

        __esOpAr(token, num_linea);

        // Se imprime el token en pantalla:
        printf("%s\n", token);

        // Se generan los tokens siguientes:
        token = strtok(NULL, " \n\t");

    }// Fin While 
}


/* Genera los tokens cuando no hay cadenas ni declaración/asignación de variables en la línea */
void genTok(char *cadena, unsigned int num_linea)
{
    char *token;

    // Se genera el primer token:
    token = strtok(cadena, " \n\t");
        
    while(token != NULL) 
    {  
        // Se ignora si es comentario:
        if(__esComentario(*token) == true)
        {
            break;
        }

        // Si es variable:
        if(__esVarValid(token, num_linea) == true)
        {
            printf("%s\n", token);
        }

        // Si es palabra reservada:
        else printf("%s\n", token);

        // Se genera el token siguiente:
        token = strtok(NULL, " \n\t");

    }// Fin While
}


/* Analizador léxico, aquí se generan los tokens del programa y también se generan los archivos .lex y .sim */
void anaLex(unsigned int lineas, unsigned int chars, char cadena[lineas][chars])
{
    unsigned int i; 
    char *token;

    // Se recorre cada línea:
    for(i = 0; i < lineas; i++)
    {
        // Se ignora si es comentario:
        if(__esComentario(cadena[i][0]) == true)
        {
            continue;
        }

        /* Si hay un string en la linea */
        else if(strchr(cadena[i], '\"') != 0)
        {  
            // Se generan los tokens:
            genTokTex(cadena[i], i+1);
            continue;

        }// Fin else if  

        /* Si hay un operador relacional en la línea */
        else if(__estaOpRel(cadena[i]) == true)
        {
            // Se generan los tokens:
            genTokRel(cadena[i], i+1);
            continue;

        } // Fin else if

        // Si hay un operador aritmético en la línea:
        else if(__estaOpAr(cadena[i]) == true)
        {
            // Se generan los tokens:
            genTokAr(cadena[i], i+1);
            continue;

        }// Fin else if

        /* Si hay una asignación en la línea */
        else if(strchr(cadena[i], '='))
        {   
            // Se generan los tokens:
            genTokAr(cadena[i], i+1);
            continue;

        } // Fin else if

        // Si sólo son palabras dentro de la línea (reservadas o variables):
        else
        {
            // Se generan el resto de los tokens:
            genTok(cadena[i], i+1);

        } // Fin else
        
    } // Fin for
}


/* La función imprime un arreglo con las líneas del archivo */
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars])
{
    unsigned int i;

    for(i = 0; i < lineas; i++)
        printf("\n%s", arreglo[i]);
}


/* Función principal */
int main(int argc, char **argv)
{   
    if (argc>1)
    {
        char *punto = strchr(argv[1], '.');
        char *mio = ".mio";

        // Se verifica que la extensión sea .mio
        if(strncmp(punto, mio, sizeof(".mio")))
        {
            printf("ERROR, no se encontró archivo .mio\n\n");
            return -1;
        }

        // Puntero al archivo:
        FILE *archivo = fopen(argv[1], "r");
    
        // Se cuenta la cantidad de líneas del archivo:
        unsigned int lineas;
        lineas = __contarLineasArchivo(archivo);
        fclose(archivo); // Se cierra el archivo

        // Cantidad de caracteres máximos de cada archivo:
        unsigned int caracteres = 256;

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
        anaLex(lineas, caracteres, array);

        // Se genera el archivo .lex:
        //generarLexer(lineas, array);

        // Se imprime la última línea del archivo:
        //printf("\nEl numero de caracteres de la ultima linea es: %d", strlen(array[lineas-1]));
        
    }
    return 0;
}
