#!/usr/bin/sh

g++ -Iinc/ -o main test.cpp src/*.cpp

./main

rm main