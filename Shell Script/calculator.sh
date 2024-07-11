x#!bin/bash
echo Choose 
echo 1 - Add
echo 2 - Sub
echo 3 - Mul
echo 4 - Div
echo 5 - Mod
continue=1
while [ $continue = 1 ]
do
echo "Enter num 1: "
read num1
echo "Enter num 2: "
read num2
echo "Choose operation: "
read choice
case $choice in
1)
result=$((a+b))
echo "result = " $result
;;
2)
result=$((a-b))
echo "result = " $result
;;
3)
result=$((a*b))
echo "result = " $result
;;
4)
result=$((a/b))
echo "result = " $result
;;
5)
result=$((a%b))
echo "result = " $result
;;
esac
echo "Do you want to continue? "
read continue
if [ $continue = 0 ] 
then
exit
fi
done
