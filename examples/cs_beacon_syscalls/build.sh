#!/bin/bash

i686-w64-mingw32-gcc -c cs_beacon_syscalls_info.c -o cs_beacon_syscalls_info.x86.o
x86_64-w64-mingw32-gcc -c cs_beacon_syscalls_info.c -o cs_beacon_syscalls_info.x64.o

i686-w64-mingw32-gcc -c cs_beacon_syscalls_test.c -o cs_beacon_syscalls_test.x86.o
x86_64-w64-mingw32-gcc -c cs_beacon_syscalls_test.c -o cs_beacon_syscalls_test.x64.o
