#!/bin/bash

i686-w64-mingw32-gcc -c hello.c -o hello.x86.o
x86_64-w64-mingw32-gcc -c hello.c -o hello.x64.o
