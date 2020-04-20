exefile : myshell.o
	gcc -o exefile myshell.o

myshell.o : myshell.c
	gcc -c -o myshell.o myshell.c

clean:
	rm *.o exefile
