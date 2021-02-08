all: analex

analex: analex.c lexer.o listas.o
	gcc -g -Wall -I ./ -o analex analex.c lexer.o listas.o

lexer.o: lexer.c
	gcc -g -Wall -I ./ -c lexer.c
	
listas.o: listas.c
	gcc -g -Wall -I ./ -c listas.c
	
clean:
	rm *.o analex