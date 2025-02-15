#!/bin/bash

# Factorial calculation using while Loop 

echo -n "Enter a number:"

read number 

factorial=1 

i=1 

while [ $i -le $number ]; do 

factorial=$((factorial * i)) 

i=$((i + 1)) 

done 

echo "The factorial of $number is $factorial."
