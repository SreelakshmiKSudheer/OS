#!/bin/bash

a=0
b=0
i=1

echo "Enter a number: "
read n

echo "Fibonacci Series: "
while [ $i -le $n ]
do
    echo "$a"
    sum=$((a+b))
    a=$b
    b=$sum
    i=$((i+1))
done