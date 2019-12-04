#! /bin/bash

prefix="\033[2;37m[libsdl2.so/setup] - \033[0m"

list=`brew list`;
if [ $? -ne 0 ]
then
	printf "$prefix brew is missing.\n";
	rm -rf $HOME/.brew \
		&& git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew \
		&& echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc \
		&& source $HOME/.zshrc \
		&& brew update;
	printf "$prefix brew installed.\n";
	list=`brew list`;
	if [ $? -ne 0 ]
	then
		printf "$prefix\033[2;31mbrew installation failed.\n\033[0m";
		exit 1;
	fi
fi

ncurses=`echo $list | grep ncurses`
if [ $? -ne 0 ]
then
	printf "$prefix ncurses is missing.\n"
	brew install ncurses 
	if [ $? -ne 0 ]
	then
		printf "$prefix\033[2;31mncurses installation failed.\n\033[0m";
		exit 1;
	fi
	printf "$prefix ncurses installed.\n"
fi
