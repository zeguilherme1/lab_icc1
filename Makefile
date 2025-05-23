all: build run

build:
	gcc main.c User.c UserActions.c Utils.c -o main.o

run:
	./main
