#!/bin/bash

# Check if a search term is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <filename_or_extension>"
  exit 1
fi

search_term=$1

# Find files that match the given filename or extension, recursively from the current directory
echo "Searching for files with '$search_term' starting from the current directory:"
find . -type f -iname "*$search_term*"  # Case-insensitive search for files
