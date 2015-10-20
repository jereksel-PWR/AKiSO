#!/bin/bash

display_usage() {
  echo "Ten skrypt kopiuje plik w dane miejsce pokazując skopiowaną ilość bajtów, prędkość i ETA"
  echo -e "\nUsage:\n$0 [Plik] [Miejsce docelowe] \n"
  }

  if [  $# -lt 2 ]
  then
    display_usage
    exit 1
  fi


function koniec() {
kill $1 2> /dev/null
rm -rf "$2/$(basename $3)" 2> /dev/null
}


source_file=$1
dest_file=$2

cp $1 $2 &
pid=$!

#trap "kill $pid 2> /dev/null" EXIT

trap "koniec $pid $dest_file $source_file" EXIT

sleep 1

old_size=0

while kill -0 $pid 2> /dev/null; do


  source_size=$(ls -l $1 | cut -d " " -f 5)
  dest_size=$(ls -l $2 | cut -d " " -f 5)


  roznica=$(($source_size - $dest_size))

  # Prędkość w MB/s
  pretkosc=$(bc -l <<< "scale=4;$(($dest_size-$old_size))/1000000")

  #ETA
  eta=$(bc -l <<< "scale=0;($roznica/$pretkosc)/1000000")

  #Czyszczenie linii
  echo -ne "                                                                                                                                          "\\r

  echo -ne "Skopiowana ilość bajtów:" $dest_size "różnica:" $roznica "prędkość" $pretkosc "Mb/s" "ETA:" $eta "s"\\r


  old_size=$dest_size

  sleep 1

done

#Czyszczenie linii
echo -ne "                                                                                                                                          "\\r


trap - EXIT
