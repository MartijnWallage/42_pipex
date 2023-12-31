# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 14:36:39 by mwallage          #+#    #+#              #
#    Updated: 2023/08/08 16:26:54 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCDIR	:= src
SRCBDIR	:= src_bonus
LIBDIR	:= libft
SRC		:= 	$(SRCDIR)/pipex.c\
			$(SRCDIR)/pipex_utils.c
SRCB	:= 	$(SRCBDIR)/pipex_bonus.c\
			$(SRCBDIR)/pipex_utils_bonus.c
OBJ		:= $(SRC:.c=.o)
OBJB	:= $(SRCB:.c=.o)
NAME	:= pipex
LIBFT	:= $(LIBDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc $(OBJ) -o $@ -L$(LIBDIR) -lft

bonus: $(OBJB) $(LIBFT)
	rm -f $(OBJ)
	cc $(OBJB) -o $(NAME) -L$(LIBDIR) -lft

$(LIBFT): $(LIBDIR)/inc/libft.h
	make -C$(LIBDIR)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	cc -Wall -Wextra -Werror -c $< -o $@ -I$(LIBDIR)/inc

$(SRCBDIR)/%.o: $(SRCBDIR)/%.c
	cc -Wall -Wextra -Werror -c $< -o $@ -I$(LIBDIR)/inc

clean:
	rm -f $(OBJ) $(OBJB)
	make clean -C$(LIBDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C$(LIBDIR)

re: fclean
	all

.PHONY: all bonus clean fclean re
