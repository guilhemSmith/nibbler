#! /bin/bash

prefix="\033[2;37m[setup] - \033[0m"

list=`ls dyn_lib`;
for lib in $list
do
	if [ -z $1 ]
	then
		sh dyn_lib/$lib/setup.sh;
		make -C dyn_lib/$lib/;
	else
		make -C dyn_lib/$lib/ $1
	fi
done