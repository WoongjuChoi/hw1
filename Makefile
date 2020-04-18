shell : shell.o
	gcc -o shell shell.o
shell.o : shell.c
	gcc -c -o shell.o shell.c
clean:
	rm *.o shell
