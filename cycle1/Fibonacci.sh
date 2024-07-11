read n
count=0
a=0
b=1
c=1
while [ $count -lt $n ]
do
echo -n $a " "
a=$b
b=$c
c=$((a+b))
count=$((count+1))
done