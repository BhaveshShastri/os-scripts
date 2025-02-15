#!/bin/bash

# Check if the directory is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

directory=$1

# Check if the directory exists
if [ ! -d "$directory" ]; then
  echo "Directory '$directory' not found!"
  exit 1
fi

# Get the current timestamp
timestamp=$(date +"%Y%m%d-%H%M%S")

# Loop through all files in the directory
for file in "$directory"/*; do
  # Check if it's a regular file
  if [ -f "$file" ]; then
    # Get the base name and extension of the file
    base_name=$(basename "$file")
    ext="${base_name##*.}"
    name="${base_name%.*}"

    # Create a new filename by appending the timestamp
    new_name="${name}_${timestamp}.${ext}"

    # Rename the file
    mv "$file" "$directory/$new_name"
    echo "Renamed '$file' to '$new_name'"
  fi
done
