all: analex

analex: analex.c lexer.o listaslex.o
	gcc -g -Wall -I ./ -o analex analex.c lexer.o listaslex.o

lexer.o: lexer.c
	gcc -g -Wall -I ./ -c lexer.c
	
listaslex.o: listaslex.c
	gcc -g -Wall -I ./ -c listaslex.c
	
clean:
	rm *.o analex