#! /bin/bash

prefix="\033[2;37m[libsfml.so/setup] - \033[0m"

function mac_setup() {
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

	sfml=`echo $list | grep sfml`
	if [ $? -ne 0 ]
	then
		printf "$prefix sfml is missing.\n"
		brew install SFML
		if [ $? -ne 0 ]
		then
			printf "$prefix\033[2;31msfml installation failed.\n\033[0m";
			exit 1;
		fi
		printf "$prefix sfml installed.\n"
	fi
}

function linux_setup() {
	sudo apt install libsfml-dev;
}

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    linux_setup;
elif [[ "$OSTYPE" == "darwin"* ]]; then
    mac_setup;
fi