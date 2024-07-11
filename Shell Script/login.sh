#!bin/bash

case ${1,,} in
	sree | admin)
		echo "Boss"
	;;
	help)
		echo "User"
	;;
	*)
		echo "Who"
esac
