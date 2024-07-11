#!/bin/sh

continue=1
while [ $continue -eq 1 ]
do
read a
read b
read op
case $op in
1)
result=$((a+b))
echo $result
;;
2)
result=$((a-b))
echo $result
;;
3)
result=$((a*b))
echo $result
;;
4)
if [ $b -ne 0 ]; then
result=$((a/b))
echo $result
else
echo "zero division error"
fi
;;
*)
echo "Invalid operation"
esac
read continue
if [ $continue -eq 0 ]; then
exit
fi
done