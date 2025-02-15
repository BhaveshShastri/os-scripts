#!/bin/bash

# Check if at least two arguments are passed

if [ $# -lt 2 ]; then
	echo "Usage: $0 num1 num2 [num3 ...]"
	exit 1
fi

#Initialize the ;argest number with the first argument
largest=$1

#Loop through all arguments
for num in "$@"; do
	if [ $num -gt $largest ]; then
		largest=$num
	fi
done

echo "The largest number is $largest."
