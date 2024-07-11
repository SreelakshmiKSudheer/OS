read n
count=1
f=1
if [ $n -eq 0 ]; then
echo $f
elif [ $n -lt 0 ]; then
echo "invalid"
else
while [ $count -le $n ]
do
f=$((f*count))
count=$((count+1))
done
echo $f
fi