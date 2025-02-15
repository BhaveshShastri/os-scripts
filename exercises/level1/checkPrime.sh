#!/bin/bash

# Check if a number is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Get the number from the argument
number=$1

# Check if the number is less than 2
if [ "$number" -lt 2 ]; then
  echo "$number is not a prime number."
  exit 1
fi

# Loop through numbers from 2 to the square root of the number
for ((i = 2; i <= $number/2; i++)); do
  if (($number % i == 0)); then
    echo "$number is not a prime number."
    exit 0
  fi
done

echo "$number is a prime number."