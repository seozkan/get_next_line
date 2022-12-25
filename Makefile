# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozkan <seozkan@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 10:17:13 by seozkan           #+#    #+#              #
#    Updated: 2022/12/25 12:54:18 by seozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = $(shell find . ! -name "get_*_bonus.c" -name "get_*.c")
BONUS = $(shell find . -name "get_bonus*.c")
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)


all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) *.o
	@echo "\n$(shell tput setaf 10) $@ built ✅ $(shell tput sgr0)\n"
bonus: $(OBJ) $(BONUS_OBJ)
	@ar rc $(NAME) *.o
	@echo "\n$(shell tput setaf 10) $@ built ✅$(shell tput sgr0)\n"
clean:
	@/bin/rm -f  *.o
	@echo "\n$(shell tput setaf 11) object files removed 👋$(shell tput sgr0)\n"
fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\n$(shell tput setaf 11) executables removed 👋$(shell tput sgr0)\n"

re: fclean all

.PHONY: all bonus clean fclean re