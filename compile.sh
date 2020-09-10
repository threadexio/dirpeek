#!/bin/sh

if [ ! -d ./binaries ]; then
	mkdir ./binaries
fi

g++ -o ./binaries/dirpeek dirpeek.cpp -std=c++11 -lcpr -lboost_program_options -pthread
