all: build run

build:
	gcc main.c Usuario.c -o main.exe

run:
	./main.exe
