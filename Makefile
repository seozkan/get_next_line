# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozkan <seozkan@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 10:17:13 by seozkan           #+#    #+#              #
#    Updated: 2022/12/19 12:44:04 by seozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

SOURCES = get_next_line.c get_next_line_utils.c
BONUS_SOURCES = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)
$(NAME): $(OBJECTS)
	$(AR) -r $@ $?
%.o: %.c
	$(CC) -c $(CFLAGS) $?
bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) -r $(NAME) $?
clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean bonus fclean re