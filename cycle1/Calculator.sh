#!/bin/sh

continue=1

while [ $continue -eq 1 ]
do
    echo -n "Num1: "
    read a
    echo -n "Num2: "
    read b
    echo "Select operation:"
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo -n "Operation: "
    read op

    if [ $op -eq 1 ]; then
        result=$((a + b))
        echo "Result: $result"
    elif [ $op -eq 2 ]; then
        result=$((a - b))
        echo "Result: $result"
    elif [ $op -eq 3 ]; then
        result=$((a * b))
        echo "Result: $result"
    elif [ $op -eq 4 ]; then
        if [ $b -ne 0 ]; then
            result=$((a / b))
            echo "Result: $result"
        else
            echo "Division by zero is not allowed."
        fi
    else
        echo "Invalid operation. Please select between 1-4."
    fi

    echo -n "Continue? (1 for yes, 0 for no): "
    read continue
    if [ $continue -eq 0 ]; then
        exit 0
    fi
done
