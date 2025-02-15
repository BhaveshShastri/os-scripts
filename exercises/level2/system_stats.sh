#!/bin/bash

# Disk usage
echo "Disk usage:"
df -h

echo ""

# Memory usage
echo "Memory usage:"
free -h

echo ""

# Uptime
echo "System uptime:"
uptime

echo ""

# Number of logged-in users
echo "Number of logged-in users:"
who | wc -l
