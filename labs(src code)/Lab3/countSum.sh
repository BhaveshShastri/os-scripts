echo -n "Enter numbers (type 'stop' to finish):"
count=0 
sum=0 
while true; do 
    read num 
    if [ "$num" == "stop" ]; then 
        break 
    elif [[ $num =~ ^[0-9]+$ ]]; then 
        sum=$((sum + num)) 
        count=$((count + 1)) 
    else 
        echo "Invalid input. Please enter a number."
    fi
done

echo "You entered $count numbers. The sum is $sum."