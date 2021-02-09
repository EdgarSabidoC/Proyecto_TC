all: analex anasin clean

analex: analex.c lexer.o listaslex.o
	gcc -g -Wall -I ./ -o analex analex.c lexer.o listaslex.o

anasin: anasin.c sintax.o listassin.o
	gcc -g -Wall -I ./ -o anasin anasin.c sintax.o listassin.o

lexer.o: lexer.c
	gcc -g -Wall -I ./ -c lexer.c
	
listaslex.o: listaslex.c
	gcc -g -Wall -I ./ -c listaslex.c

sintax.o: sintax.c
	gcc -g -Wall -I ./ -c sintax.c
	
listassin.o: listassin.c
	gcc -g -Wall -I ./ -c listassin.c

# Se borran los archivos objeto:
clean:
	rm  -f *.o *~