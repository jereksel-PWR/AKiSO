#!/bin/bash

display_usage() {
  echo "Ten skrypt sprawdza co podaną ilość sekund czy strona się zmieniła"
  echo -e "\nUsage:\n$0 [Strona] [Ilość sekund] \n"
  }

  if [  $# -lt 2 ]
  then
    display_usage
    exit 1
  fi

stronka=$1
czas=$2

temp=/tmp/webtrace

mkdir $temp

poprzednie=$(cat /dev/urandom | tr -cd 'a-z0-9' | head -c 32)

#Pierwsze pobieranie
wget $stronka -q -O $temp/$poprzednie

sleep $czas

while true; do


  nowe=$(cat /dev/urandom | tr -cd 'a-z0-9' | head -c 32)
  wget $stronka -q -O $temp/$nowe



  roznica=$(diff $temp/$poprzednie $temp/$nowe)


  if [ -n "$roznica" ]; then

    zenity --info --text="Nastąpiła zmiana"

    exit 0

  fi


  poprzednie=$nowe


  sleep $czas

done
