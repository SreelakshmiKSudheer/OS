if [ ${1,,} = sree ] ; then
	echo "Hey Boss"
elif [ ${1,,} = help ] ; then
	echo "Type your username"
else
	echo "I don't know who you are"
fi
