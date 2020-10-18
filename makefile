mycomp: main.o run.o firstPass.o passMila.o secondpass.o
	gcc -g -ansi -Wall -pedantic main.o run.o firstPass.o passMila.o secondpass.o -o mycomp -lm

main.o: main.c
	gcc -c -ansi -Wall -pedantic main.c -o main.o -lm

run.o: run.c
	gcc -c -ansi -Wall -pedantic run.c -o run.o -lm

firstPass.o: firstPass.c
	gcc -c -ansi -Wall -pedantic firstPass.c -o firstPass.o -lm

secondpass.o: secondpass.c
	gcc -c -ansi -Wall -pedantic secondpass.c -o secondpass.o -lm   
     
passMila.o: passMila.c
	gcc -c -ansi -Wall -pedantic passMila.c -o passMila.o -lm
