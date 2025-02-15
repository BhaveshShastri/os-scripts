#!/bin/bash

# Check if a filename is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
  echo "File $1 not found!"
  exit 1
fi

# Count the number of lines in the file
line_count=$(wc -l < "$1")

echo "The file '$1' has $line_count lines."
