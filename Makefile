# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubusque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/20 00:20:30 by gubusque          #+#    #+#              #
#    Updated: 2026/02/03 15:36:16 by gubusque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Direcotires \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE_DIR	= include/
LIBFT_DIR	= libft/

# Files \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

SRC	= main.c	\
	  ft_checkers.c	\
	  ft_free.c	\
	  ft_error.c	\
		
# Objects \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

OBJ	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Libreries \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

LIBFT	= $(LIBFT_DIR)libft.a

# Commands && flags \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -g
LDFLAGS	= -L$(LIBFT_DIR)
INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
RM	= rm -rf

# Rules \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\#

all: libft $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)


$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft: 
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	$(RM) $(OBJ) $(OBJ_DIR) $(LIBFT) $(LIBMLX)
	$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus: fclean all

.PHONY: all libft clean fclean re
