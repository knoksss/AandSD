all: main.exe tests.exe

main.exe: main.o tree.o
	gcc -o main.exe main.o tree.o

tests.exe: tests.o tree.o
	gcc -o tests.exe tests.o tree.o

main.o: main.c
	gcc -c main.c

tests.o: tests.c
	gcc -c tests.c

tree.o: tree.c
	gcc -c tree.c

clean:
	del *.o *.exe