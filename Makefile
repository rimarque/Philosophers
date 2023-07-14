# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 12:57:07 by rimarque          #+#    #+#              #
#    Updated: 2023/07/13 14:29:24 by rimarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------  COLORS  --------------------------------
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#------------------------------------  COMMANDS  ------------------------------
CC = cc
RM = rm -rf

#------------------------------------  FLAGS  ---------------------------------
#CFLAGS	= -Wall -Wextra -Werror -g -pthread #-fsanitize=address
CFLAGS = = -pthread #-fsanitize=address
NPD		= --no-print-directory
CMLX	= -Ilmlx -lXext -lX11 -lm

#-----------------------------------  FILES  --------------------------------
NAME = philo

SRC = philo.c \

#----------------------------------  RULES  ----------------------------------
all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	echo "$(GREEN)Philo program READY!$(RESET)"

clean:
	rm -rf $(OBJ)
	echo "Object files CLEAN"

fclean: clean
	rm -rf $(NAME)
	rm -rf bonus
	echo "All files CLEAN"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
