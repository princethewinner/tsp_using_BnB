#!/bin/bash
g++ -Wall -c tsp.cpp
g++ -Wall -c fib_heap.cpp
g++ -Wall -c data.cpp
g++ -Wall main.cpp tsp.o fib_heap.o data.o -o tsp
rm tsp.o
rm fib_heap.o
rm data.o