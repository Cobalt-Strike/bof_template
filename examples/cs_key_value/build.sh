#!/bin/bash

i686-w64-mingw32-gcc -c cs_key_value.c -o cs_key_value.x86.o
x86_64-w64-mingw32-gcc -c cs_key_value.c -o cs_key_value.x64.o
