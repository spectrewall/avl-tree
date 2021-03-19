all: AVLTree

AVLTree: main.o AVLTree.o
	gcc -o AVLTree main.o AVLTree.o

main.o: main.c AVLTree.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

AVLTree.o: AVLTree.c AVLTree.h
	gcc -o AVLTree.o AVLTree.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ AVLTree
