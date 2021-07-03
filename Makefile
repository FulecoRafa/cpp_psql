all: build run

run: build
	./usp_viagens

build:
	g++ -g -fsanitize=address src/main.cpp -o usp_viagens -lpqxx -lpq
