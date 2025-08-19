# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 19:44:31 by lgertrud          #+#    #+#              #
#    Updated: 2025/08/19 14:12:33 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g

#directories
SRC_DIR = src
I_DIR = includes

#includes
INCLUDES = -I$(I_DIR)

#sources
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/init_args.c $(SRC_DIR)/utils.c $(SRC_DIR)/functions.c

#objects
OBJS = $(SRC:.c=.o)

# Colors
YELLOW = \e[93m
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

#Banners
INTRO = @echo "\n$(BLUE)🚀 Starting compilation of the $(YELLOW)Philosophers$(RESET) $(BLUE)project by $(YELLOW)lgertrud$(RESET)...\n\
--------------------------------------------------------------"
END = @echo "$(GREEN)✔ Compilation complete!$(RESET)\n\n\
To run the program:\n\
  $(BLUE)<./pipex infile cmd1 cmd2 outfile>$(RESET)\n\n\
Example:\n\
  $(BLUE)./pipex Makefile \"grep all\" rev out.txt$(RESET)\n\n\
Enjoy 🚀"

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)OK!!!$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.c
	@echo "$(YELLOW)[.o]$(RESET)Compiling $<..."
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@rm -f $(OBJS)

fclean:
	@echo "$(RED)[FCLEAN]$(RESET) Removing all generated files..."
	@rm -f $(NAME)
	@rm -f $(OBJS)

re: fclean all
