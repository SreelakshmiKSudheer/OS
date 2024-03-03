#!/bin/sh
# Command line args
# the "$*" special parameter takes the entire list as one argument with spaces between
# "$@" special parameter takes the entire list and separates it into separate arguments.
echo "File name: $0"
echo "First parameter: $1"
echo "Second parameter: $2"
echo "Quaoted values: $@"
echo "Quoted values: $*"
echo "Total no. parameter: $#"

for TOKEN in $*
do
    echo $TOKEN
done
