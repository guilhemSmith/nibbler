# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/06 15:16:06 by gsmith            #+#    #+#              #
#    Updated: 2019/11/18 17:18:10 by gsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
.SILENT: 
endif

# Compiling macros

NAME = nibbler
LIBPRINT = libprint.so

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra
LIBFLAGS = -shared -fPIC

## main directories and files

DIR_SRC = src
DIR_BUILD = build
DIR_DEP = depend
DIR_INC = include

FILES_SRC = \
	main.cpp
FILES_BUILD = $(FILES_SRC:.cpp=.o)
FILES_DEP = $(FILES_SRC:.cpp=.d)

SRC = $(addprefix $(DIR_SRC)/, $(FILES_SRC))
BUILD = $(addprefix $(DIR_BUILD)/, $(FILES_BUILD))
DEP = $(addprefix $(DIR_DEP)/, $(FILES_DEP))
INC = -I $(DIR_INC)

## lib directories and files

PR_DIR = print

PR_FILES_SRC = \
	print.cpp
PR_FILES_BUILD = $(PR_FILES_SRC:.cpp=.o)
PR_FILES_DEP = $(PR_FILES_SRC:.cpp=.d)

PR_SRC = $(addprefix $(DIR_SRC)/$(PR_DIR)/, $(PR_FILES_SRC))
PR_BUILD = $(addprefix $(DIR_BUILD)/$(PR_DIR)/, $(PR_FILES_BUILD))
PR_DEP = $(addprefix $(DIR_DEP)/$(PR_DIR)/, $(PR_FILES_DEP))
PR_INC = -I $(DIR_INC)/$(PR_DIR)

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
all: $(NAME)

.PHONY: re
re:
ifndef VERBOSE
	printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
endif
	rm -f $(PR_BUILD)
	rm -df $(DIR_BUILD)/$(PR_DIR) 2>/dev/null || True
	rm -f $(BUILD)
	rm -df $(DIR_BUILD) || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"
endif
ifndef VERBOSE
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(LIBPRINT)$(RED) library...$(NC)\r"
endif
	rm -f $(LIBPRINT)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Library $(subst $(S_N),$(S_B),$(PURPLE))$(LIBPRINT)$(PURPLE) deleted.          \n$(NC)"
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(NAME)$(RED) binary...$(NC)\r"
endif
	rm -f $(NAME)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Binary $(subst $(S_N),$(S_B),$(PURPLE))$(NAME)$(PURPLE) deleted.          \n$(NC)"
endif
	@Make all

# Binary and object files building

## libprint files

$(LIBPRINT): $(PR_BUILD)
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $(subst $(S_N),$(S_B),$(YELLOW))$(LIBPRINT)$(YELLOW) library...$(NC)\r"
endif
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(PR_INC) -o $@ $^
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)Library $(subst $(S_N),$(S_B),$(BLUE))$(LIBPRINT)$(BLUE) ready.      \n$(NC)"
endif

$(DIR_BUILD)/$(PR_DIR)/%.o: $(DIR_SRC)/$(PR_DIR)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $@...$(NC)\r"
endif
	mkdir -p $(DIR_BUILD)
	mkdir -p $(DIR_BUILD)/$(PR_DIR)
	$(CXX) $(CXXFLAGS) $(PR_INC) -c -o $@ $<
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)File $@ compiled.\n$(NC)"
endif

## main program files

$(NAME): $(LIBPRINT) $(BUILD)
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $(subst $(S_N),$(S_B),$(YELLOW))$(NAME)$(YELLOW) binary...$(NC)\r"
endif
	$(CXX) $(CXXFLAGS) $(INC) $(PR_INC) -o $@ $^
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)Binary $(subst $(S_N),$(S_B),$(BLUE))$(NAME)$(BLUE) ready.      \n$(NC)"
endif

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $@...$(NC)\r"
endif
	mkdir -p $(DIR_BUILD)
	$(CXX) $(CXXFLAGS) $(INC) $(PR_INC) -c -o $@ $<
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)File $@ compiled.\n$(NC)"
endif

# Depend files building

## libprint depend files

$(DIR_DEP)/$(PR_DIR)/%.d: $(DIR_SRC)/$(PR_DIR)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Writing dependency $@...$(NC)\r"
endif
	mkdir -p $(DIR_DEP)
	mkdir -p $(DIR_DEP)/$(PR_DIR)
	$(CXX) $(CXXFLAGS) $(PR_INC) -MT $(@:$(DIR_DEP)/%.d=$(DIR_BUILD)/%.o) -MM $< \
		| sed 's,\(.*\)\.o[ :]*,\1.o $@ : ,g' > $@
ifndef VERBOSE
	printf "$(PREFIX)$(CYAN)Dependency $@ updated.  \n$(NC)"
endif

## main depend files

$(DIR_DEP)/%.d: $(DIR_SRC)/%.cpp
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Writing dependency $@...$(NC)\r"
endif
	mkdir -p $(DIR_DEP)
	$(CXX) $(CXXFLAGS) $(INC) $(PR_INC) -MT $(@:$(DIR_DEP)/%.d=$(DIR_BUILD)/%.o) -MM $< \
		| sed 's,$(DIR_INC)/$(PR_DIR)/.*\.hpp,,g' | sed 's,\(.*\)\.o[ :]*,\1.o $@ : ,g' > $@
ifndef VERBOSE
	printf "$(PREFIX)$(CYAN)Dependency $@ updated.  \n$(NC)"
endif

# Files cleaning

.PHONY: clean
clean:
ifndef VERBOSE
	printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
endif
	rm -f $(PR_BUILD)
	rm -df $(DIR_BUILD)/$(PR_DIR) 2>/dev/null || True
	rm -f $(BUILD)
	rm -df $(DIR_BUILD) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"
	printf "$(PREFIX)$(RED)Cleaning dependencies files...$(NC)\r"
endif
	rm -f $(PR_DEP)
	rm -df $(DIR_DEP)/$(PR_DIR) 2>/dev/null || True
	rm -f $(DEP)
	rm -df $(DIR_DEP) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Dependencies files cleaned.   \n$(NC)"
endif

.PHONY: fclean
fclean: clean
ifndef VERBOSE
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(LIBPRINT)$(RED) library...$(NC)\r"
endif
	rm -f $(LIBPRINT)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Library $(subst $(S_N),$(S_B),$(PURPLE))$(LIBPRINT)$(PURPLE) deleted.          \n$(NC)"
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(NAME)$(RED) binary...$(NC)\r"
endif
	rm -f $(NAME)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Binary $(subst $(S_N),$(S_B),$(PURPLE))$(NAME)$(PURPLE) deleted.          \n$(NC)"
endif

# include depend files

-include $(DEP)
-include $(PR_DEP)