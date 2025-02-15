#!/bin/bash

echo -n "Enter a number :"
read num

if [ $num -le 1 ]; then
	echo "$num is not a prime number."
	exit
fi

is_Prime=1

for((i=2; i<= num/2; i++)); do
	if [ $((num % i)) -eq 0 ]; then
		is_Prime=0
		break
	fi
done

if [ $is_Prime -eq 1 ]; then
	echo "$num is a prime number."
else
	echo "$num is not a prime number."
fi