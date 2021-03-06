# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/06 15:16:06 by gsmith            #+#    #+#              #
#    Updated: 2020/06/14 12:11:37 by guilhem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
.SILENT: 
endif

# Compiling macros

NAME = nibbler

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra

# lib builder and cleaner

SDL2 = dyn_lib/libsdl2/
SFML = dyn_lib/libsfml/
GLFW = dyn_lib/libglfw/
DYN_LIB = $(SDL2) $(SFML) $(GLFW)
DL_LIB = .dl_lib

## directories and files

DIR_SRC = src
DIR_BUILD = build
DIR_DEP = depend
DIR_INC = include

FILES_SRC = \
	main.cpp \
	Arguments.cpp \
	Game.cpp \
	Grid.cpp \
	SnakeBody.cpp \
	SnakeHead.cpp \
	SnakeTail.cpp \
	Obstacle.cpp \
	Apple.cpp \
	Loader.cpp \
	Direction.cpp \
	Position.cpp \
	Score.cpp \
	Blueberry.cpp
FILES_BUILD = $(FILES_SRC:.cpp=.o)
FILES_DEP = $(FILES_SRC:.cpp=.d)

SRC = $(addprefix $(DIR_SRC)/, $(FILES_SRC))
BUILD = $(addprefix $(DIR_BUILD)/, $(FILES_BUILD))
DEP = $(addprefix $(DIR_DEP)/, $(FILES_DEP))
INC = -I $(DIR_INC)

# Color and output macros

BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

S_N = [0;
S_B = [1;
S_D = [2;
S_I = [3;
S_L = [4;

NC = \033[0m

PREFIX = $(subst $(S_N),$(S_D),$(WHITE))[$(NAME)] - $(NC)

# Build all and rebuild

.PHONY: all
all: $(DYN_LIB)
	@make $(NAME)

.PHONY: re
re:
	@make fclean
	@make all

# Binary and object files building

$(NAME): $(BUILD)
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $(subst $(S_N),$(S_B),$(YELLOW))$(NAME)$(YELLOW) binary...$(NC)\r"
endif
	$(CXX) -ldl $(CXXFLAGS) $(INC) -o $@ $^
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)Binary $(subst $(S_N),$(S_B),$(BLUE))$(NAME)$(BLUE) ready.      \n$(NC)"
endif

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $@...$(NC)\r"
endif
	mkdir -p $(DIR_BUILD)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)File $@ compiled.\n$(NC)"
endif

# Depend files building

$(DIR_DEP)/%.d: $(DIR_SRC)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Writing dependency $@...$(NC)\r"
endif
	mkdir -p $(DIR_DEP)
	$(CXX) $(CXXFLAGS) $(INC) -MT $(@:$(DIR_DEP)/%.d=$(DIR_BUILD)/%.o) -MM $< \
		| sed 's,\(.*\)\.o[ :]*,\1.o $@ : ,g' > $@
ifndef VERBOSE
	printf "$(PREFIX)$(CYAN)Dependency $@ updated.  \n$(NC)"
endif

# dyn library building

$(DL_LIB):
	bash $(SDL2)/setup.sh
	bash $(SFML)/setup.sh
	bash $(GLFW)/setup.sh
	touch $@

.PHONY: $(DYN_LIB)
$(DYN_LIB): $(DL_LIB)
	make -s -C $@

# Files cleaning

.PHONY: clean
clean:
	make -s -C $(SDL2) clean
	make -s -C $(SFML) clean
	make -s -C $(GLFW) clean
	@make cleanobj

.PHONY: cleanobj
cleanobj:
ifndef VERBOSE
	printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
endif
	rm -f $(BUILD)
	rm -df $(DIR_BUILD) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"
	printf "$(PREFIX)$(RED)Cleaning dependencies files...$(NC)\r"
endif
	rm -f $(DEP)
	rm -rf $(DIR_DEP) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Dependencies files cleaned.   \n$(NC)"
endif

.PHONY: fclean
fclean:
	make -s -C $(SDL2) fclean
	make -s -C $(SFML) fclean
	make -s -C $(GLFW) fclean
	@make cleanobj
ifndef VERBOSE
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(NAME)$(RED) binary...$(NC)\r"
endif
	rm -f $(NAME)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Binary $(subst $(S_N),$(S_B),$(PURPLE))$(NAME)$(PURPLE) deleted.          \n$(NC)"
endif

# include depend files

-include $(DEP)
