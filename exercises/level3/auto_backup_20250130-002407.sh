#!/bin/bash

# Check if at least one directory is provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 <dir1> <dir2> ..."
  exit 1
fi

# Get the current timestamp
timestamp=$(date +"%Y%m%d-%H%M%S")

# Create the backup archive filename
backup_filename="backup_$timestamp.tar.gz"

# Create the backup archive
echo "Backing up directories into '$backup_filename'..."
tar -czf "$backup_filename" "$@"

# Verify the backup was successful
if [ $? -eq 0 ]; then
  echo "Backup completed successfully."
else
  echo "Backup failed!"
  exit 1
fi
