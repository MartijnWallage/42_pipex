# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 18:11:58 by mwallage          #+#    #+#              #
#    Updated: 2023/07/18 16:05:49 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
SRCDIR	:=	src
SRC		:=	$(SRCDIR)/pipex.c\
			$(SRCDIR)/utils.c
OBJ		:=	$(SRC:.o=.c)
LIBFTDIR	:= Libft
LIBFT	:= $(LIBFTDIR)/libft.a
NAME	:=	pipex

all	: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $@ -L$(LIBFTDIR) -lft

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
