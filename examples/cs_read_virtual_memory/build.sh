#!/bin/bash

i686-w64-mingw32-gcc -c cs_read_virtual_memory.c -o cs_read_virtual_memory.x86.o
x86_64-w64-mingw32-gcc -c cs_read_virtual_memory.c -o cs_read_virtual_memory.x64.o
