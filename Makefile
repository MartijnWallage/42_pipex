# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 18:11:58 by mwallage          #+#    #+#              #
#    Updated: 2023/07/28 16:19:42 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
SRCDIR	:=	src
SRC		:=	$(SRCDIR)/pipex.c\
			$(SRCDIR)/utils.c
SRC_BONUS := $(SRCDIR)/pipex_bonus.c\
			$(SRCDIR)/utils.c
OBJ		:=	$(SRC:.c=.o)
OBJ_BONUS := $(SRC_BONUS:.c=.o)
LIBFTDIR	:= Libft
LIBFT	:= $(LIBFTDIR)/libft.a
NAME	:=	pipex
BONUS	:=	pipex_bonus

all	: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(SRCDIR)/pipex.h
	$(CC) $(OBJ) -o $@ -L$(LIBFTDIR) -lft

bonus: $(BONUS)

$(BONUS): $(OBJ_BONUS) $(LIBFT)
	$(CC) $(OBJ_BONUS) -o $@ -L$(LIBFTDIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFTDIR)

$(LIBFT):
	make -C$(LIBFTDIR)
	
clean:
	rm -f $(SRCDIR)/*.o
	make clean -C$(LIBFTDIR)

fclean: clean
	make fclean -C$(LIBFTDIR)
	rm $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
