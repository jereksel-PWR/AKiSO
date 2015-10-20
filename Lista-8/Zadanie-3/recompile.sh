#/bin/bash

rm -rf log
rm -rf fuse
gcc -Wall main.c $(pkg-config fuse --cflags --libs) -o fuse
fusermount -u test
./fuse -d archiwum.tar test > log
