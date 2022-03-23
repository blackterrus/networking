#!/usr/bin/sh

g++ -Iinc/ -o test1 testRecv.cpp src/*.cpp

g++ -Iinc/ -o test2 testSend.cpp src/*.cpp
