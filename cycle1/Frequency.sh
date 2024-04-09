#!/bin/sh

# Check whether the filename and word are given
echo "Enter the filename: "
read filename
echo "Enter a word whose occurrence has to be counted: "
read word

if [ ! -f "$filename" ]; then
    echo "File $filename does not exist"
    exit 1
fi

# search for occurrences
occurrences=$(grep -o -i -w "$word" "$filename" | wc -l)
echo "The word '$word' occurs $occurrences time(s) in the file"
