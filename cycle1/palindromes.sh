#!/bin/bash

if [ $# -ne 2 ] ; then
    echo "Usage: $0 <number1> <number2>"
    exit 1
fi

num1=$1
num2=$2

is_palindrome() {
    num=$1
    reverse=$(echo $num | rev)
    if [ $num -eq $everse ] ; then
        return 0
    else
        return 1
    fi
}

echo "Palindrome numbers b/w $num1 and $num2 are: "
i=$num1
while [ $i -le $num2 ]
do 
    if is_palindrome $i ; then
        echo $i
    fi
done