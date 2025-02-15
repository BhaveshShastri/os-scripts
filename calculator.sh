#!/bin/bash

while true; do
    echo "Calculator Menu"
    echo "1.Addition"
    echo "2.Subtraction"
    echo "3.Multiplication"
    echo "4.Division"
    echo "5.Exit"
    echo -n "Enter your choice :"
    read choice
    if [ $choice -eq 5 ]; then
        echo "Exiting ..."
        exit 0
    fi
    echo -n "Enter two numbers :"
    read a b

    case $choice in
    1)
        echo "Result : $((a+b))"
        ;;
    2)
        echo "Result : $((a-b))"
        ;;
    3)
        echo "Result : $((a*b))"
        ;;
    4)
        if [ $b -ne 0 ]; then
            echo "Result : $((a/b))"
        else
            echo "+inf"
        fi
        ;;
    5)
        echo "Exiting ..."
        exit 0
        ;;
    *)
        echo "Invalid Choice, try again."
        ;;
    esac
done