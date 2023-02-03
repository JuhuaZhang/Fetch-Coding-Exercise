.PHONEY: build

build: program

program: main.cpp
	g++ -w -std=c++17 main.cpp -o main
