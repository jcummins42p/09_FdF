# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2023/12/13 18:39:51 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADER = ft_printf.h
CC = cc
CFLAGS = -g -Werror -Wextra -Wall
SRCS = ft_printf.c ft_printf_nformats.c ft_printf_cformats.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -r $@ $?

%.o:	%.c
	$(CC) -c -fPIC $(CFLAGS) $?

clean:
	@echo "Removing all object files"
	@rm -rf $(OBJS)
	@rm -rf *.so

fclean: clean
	@echo "Removing all object files and library"
	@rm -rf $(NAME)
	@rm -rf *.out

re:	fclean all
