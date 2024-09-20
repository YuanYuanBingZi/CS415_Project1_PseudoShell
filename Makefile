all : pseudo-shell


pseudo-shell: main.o string_parser.o command.o run.o 
	gcc -o pseudo-shell main.o string_parser.o command.o run.o 

main.o: main.c main.h
	gcc -c main.c main.h

string_parser.o: string_parser.c string_parser.h
	gcc -c string_parser.c

command.o: command.c command.h
	gcc -c command.c

run.o: run.c run.h
	gcc -c run.c



clean:
	rm -f core *.o pseudo-shell
