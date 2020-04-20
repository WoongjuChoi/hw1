CC = gcc

myshell : 
		gcc -o myshell myshell.c
		
clean :
		rm *.o myshell