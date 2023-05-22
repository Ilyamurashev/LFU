all:
	gcc main.c test.c io.c insert.c delete.c -o hello
run: all
	./hello