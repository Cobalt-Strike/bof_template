#!/bin/bash

i686-w64-mingw32-gcc -c demo.c -o demo.x86.o
x86_64-w64-mingw32-gcc -c demo.c -o demo.x64.o
