#!/bin/bash

# Check if there are any directories in the current path
if [ "$(find . -maxdepth 1 -type d | wc -l)" -le 1 ]; then
  echo "No directories found in the current path."
  exit 1
fi

# Generate disk usage report for each directory
echo "Disk usage report for directories in the current path:"
du -sh */ | sort -h
