#!/bin/bash

display_usage() {
	echo "Ten skrypt liczy sumę i różnicę mnogościową dwóch podanych plików (będą się one znajdować w plikach 'suma' oraz 'różnica')"
	echo -e "\nUsage:\n$0 [Plik 1] [Plik 2] \n"
	}

	if [  $# -lt 2 ]
	then
		display_usage
		exit 1
	fi


plik_1=$1
plik_2=$2
suma="suma"
roznica="roznica"

sort -u $plik_1 > /tmp/suma_$plik_1
sort -u $plik_2 > /tmp/suma_$plik_2

#comm /tmp/suma_$plik_1 /tmp/suma_$plik_2 | tr -d '\t' > $suma

cat /tmp/suma_$plik_1 /tmp/suma_$plik_2 | sort | uniq > $suma

comm -23 /tmp/suma_$plik_1 /tmp/suma_$plik_2 | tr -d '\t' > $roznica

rm -f /tmp/suma_$plik_1
rm -f /tmp/suma_$plik_2

sed -i '/^$/d' $suma
sed -i '/^$/d' $roznica
