#!/bin/bash

i686-w64-mingw32-gcc -c cs_beacon_info.c -o cs_beacon_info.x86.o
x86_64-w64-mingw32-gcc -c cs_beacon_info.c -o cs_beacon_info.x64.o
