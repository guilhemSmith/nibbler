#! /bin/bash

prefix="\033[2;37m[libglfw.so/setup] - \033[0m"

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

glfw=`echo $list | grep glfw`
if [ $? -ne 0 ]
then
	printf "$prefix glfw is missing.\n"
	brew install glfw
	if [ $? -ne 0 ]
	then
		printf "$prefix\033[2;31mglfw installation failed.\n\033[0m";
		exit 1;
	fi
	printf "$prefix glfw installed.\n"
fi

glew=`echo $list | grep glew`
if [ $? -ne 0 ]
then
	printf "$prefix glew is missing.\n"
	brew install glew
	if [ $? -ne 0 ]
	then
		printf "$prefix\033[2;31mglew installation failed.\n\033[0m";
		exit 1;
	fi
	printf "$prefix glew installed.\n"
fi