#! /bin/sh

cd "$(dirname "$0")"

cd ..;

g++ ./src/graph.cpp main.cpp -o run_me
