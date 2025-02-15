#!/bin/bash

# Create a script that moves files into directories based on their extensions (e.g., .txt
# files into a TextFiles_directory).

# Loop through all files in the current directory
for file in *.*; do
  # Check if it's a regular file
  if [ -f "$file" ]; then
    # Get the file extension
    extension="${file##*.}"
    
    # Move files based on their extension
    case "$extension" in
      txt)
        # Check if the directory exists
        if [ ! -d "TextFiles_directory" ]; then
            mkdir TextFiles_directory
        fi
        cp "$file" TextFiles_directory/
        echo "Moved $file to TextFiles_directory/"
        ;;
      jpg|jpeg|png|gif)
        # Check if the directory exists
        if [ ! -d "ImageFiles_directory" ]; then
            mkdir ImageFiles_directory
        fi
        cp "$file" ImageFiles_directory/
        echo "Moved $file to ImageFiles_directory/"
        ;;
      pdf)
        # Check if the directory exists
        if [ ! -d "PDFFiles_directory" ]; then
            mkdir PDFFiles_directory
        fi
        cp "$file" PDFFiles_directory/
        echo "Moved $file to PDFFiles_directory/"
        ;;
      sh)
        # Check if the directory exists
        if [ ! -d "ShellFiles_directory" ]; then
            mkdir ShellFiles_directory
        fi
        cp "$file" ShellFiles_directory/
        echo "Moved $file to ShellFiles_directory/"
        ;;
      *)
        echo "No action for file: $file (Unknown extension)"
        ;;
    esac
  fi
done

echo "File organization complete."