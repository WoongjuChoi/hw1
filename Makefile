myshell.out:hw1_myshell.o
	gcc -o myshell.out hw1_myshell.o

hw1_myshell.o: hw1_myshell.c
	gcc -c -o hw1_myshell.o hw1_myshell.c

clean:
	rm -f *.o


