#!/bin/bash

# Check if an extension is passed as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file-extension>"
    exit 1
fi

extension=$1
echo "Files with extension '$extension' are :"
for file in *.$extension; do
    if [ -f "$file" ]; then
        echo "$file"
    fi
done