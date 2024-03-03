#!/bin/sh
# Basic IO
echo "What is your name:"
read name
echo "How old are you:"
read age

current_year=2024
readonly current_year   # makes the var a read only done, can't be ovewritten
yob=$((current_year-age))
echo "Hi, $name"
echo "You are born in $yob"
