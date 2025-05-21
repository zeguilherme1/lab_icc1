all: build run

build:
	gcc main.c User.c UserActions.c Utils.c -o main.exe

run:
	./main.exe
