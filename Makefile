shell : shellhw.c
		gcc -o shell shellhw.c

main.o : shellhw.c
	  	gcc -c shellhw.c
