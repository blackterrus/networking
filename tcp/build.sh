#!/usr/bin/sh

# Builds the tcpserver application
##################################
# g++ - calls compiler
# -I<path> - sets path as inclusion directory for header files
#          - each include directory must be specified
#          - (e.g., a structure with 3 include directories dir1, dir2, and dir3
#            will pass -Idir1/ -Idir2/ -Idir3/ for each to be visible)
# -o <filename> - tells linker to link objects into <filename>.exe
# src/<file> - specifies source where main function resides
##################################

g++ -Iinc/ -o tcpserver src/TCPServer.cpp

# Builds the tcpclient application
##################################
# g++ - calls compiler
# -I/path - sets path as inclusion directory for header files
# -o <filename> - tells linker to compile sources into <filename>.exe
# src/<file> - specifies source where main function resides
##################################

g++ -Iinc/ -o tcpclient src/TCPClient.cpp