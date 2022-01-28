#!/bin/bash


CC_x64="x86_64-w64-mingw32-gcc"
CC_x86="i686-w64-mingw32-gcc"
archs="x64 x86"

compile() {
   for arch in ${archs} ; do
      if [ ! -f obj/${1}.${arch}.o -o src/${1}.c -nt obj/${1}.${arch}.o ] ; then
         echo "Compile obj/$1.${arch}.o"
         if [ "${arch}" == "x64" ] ; then
            ${CC_x64} -o obj/${1}.${arch}.o -c src/${1}.c -masm=intel -Wall -I../
         else
            ${CC_x86} -o obj/${1}.${arch}.o -c src/${1}.c -masm=intel -Wall -I../
         fi
      fi
   done
}


# main

# check for a cross-compiler
if [ ! $(command -v ${CC_x64}) ]; then
        echo "No cross-compiler detected. Try: apt-get install mingw-w64"
        exit
fi

[ -d obj ] || mkdir obj

files=$(find src -name \*.c)
for f in ${files} ; do
   compile $(basename ${f%.*})
done

