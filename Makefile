all: build run

run: build
	./usp_viagens

build:
	g++ src/main.cpp -o usp_viagens -lpqxx -lpq
