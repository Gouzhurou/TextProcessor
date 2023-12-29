all: main.o menu.o additional.o inputOutput.o textProcessing.o
	gcc main.o menu.o additional.o inputOutput.o textProcessing.o -o main

main.o: main.c Text.h menu.h additional.h inputOutput.h textProcessing.h
	gcc -c main.c

menu.o: menu.c menu.h Text.h inputOutput.h textProcessing.h
	gcc -c -std=c99 menu.c

additional.o: additional.c additional.h Text.h
	gcc -c -std=c99 additional.c

inputOutput.o: inputOutput.c inputOutput.h additional.h Text.h
	gcc -c -std=c99 inputOutput.c

textProcessing.o: textProcessing.c textProcessing.h additional.h Text.h
	gcc -c -std=c99 textProcessing.c

clean:
	rm -rf *.o main