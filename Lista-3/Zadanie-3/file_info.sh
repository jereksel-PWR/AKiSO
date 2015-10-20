#!/bin/bash

file="$1"

md5=$(md5sum "$1" | awk '{ print $1 }')
size=$(stat -c %s "$1")

echo -e "$md5\t$size\t$1"
