.PHONEY: build

build: program

program: main.cpp
	g++ -std=c++17 main.cpp -o main