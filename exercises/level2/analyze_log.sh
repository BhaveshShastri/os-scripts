#!/bin/bash

# Check if both file and keyword are provided
if [ $# -ne 2 ]; then
  echo "Usage: $0 <log_file> <keyword>"
  exit 1
fi

log_file=$1
keyword=$2

# Check if the log file exists
if [ ! -f "$log_file" ]; then
  echo "Log file '$log_file' not found!"
  exit 1
fi

# Extract lines containing the keyword
echo "Lines containing '$keyword' in '$log_file':"
grep -i "$keyword" "$log_file"
