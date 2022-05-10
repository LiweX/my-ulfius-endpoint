CFLAGS=-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

lab5: lab5.c
	gcc $(CFLAGS) lab5.c -o lab5 -lulfius