# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/05/04 00:56:59 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEADER_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CC = cc
CFLAGS = -g -Werror -Wextra -Wall -pedantic -I$(HEADER_DIR) -Imlx_linux -O3 #-fsanitize=address
MLXFLAGS = -lmlx_Linux -lXext -lX11 -lm -lz -lft
LIB = libft.a
LIB_DIR = lib
MLX_DIR = mlx_linux
LIB_PATH = $(LIB_DIR)/$(LIB)

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -I$(HEADER_DIR) -Imlx_linux -O3 -c $< -o $@

$(LIB_PATH):
	@echo "Running libft make"
	@(cd $(LIB_DIR) && make)

clean:
	@echo "Removing all object files"
	@rm -rf $(OBJ_DIR)
	@(cd $(LIB_DIR) && make clean)

fclean: clean
	@echo "Removing all object files and executable"
	@rm -rf $(NAME)
	@(cd $(LIB_DIR) && make fclean)

re:	fclean all

.PHONY: all clean fclean re
