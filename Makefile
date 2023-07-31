# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 14:36:39 by mwallage          #+#    #+#              #
#    Updated: 2023/07/31 14:45:10 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCDIR	:= src
SRCBDIR	:= src_bonus
SRC		:= $(SRCDIR)/ft_split.c\
			$(SRCDIR)/ft_strjoin.c\
			$(SRCDIR)/ft_strncmp.c\
			$(SRCDIR)/ft_strlen.c\
			$(SRCDIR)/pipex.c\
			$(SRCDIR)/pipex_utils.c\
			$(SRCDIR)/ft_putstr_fd.c\
			$(SRCDIR)/get_next_line.c\
			$(SRCDIR)/get_next_line_utils.c
SRCB	:= $(SRCBDIR)/ft_split.c\
			$(SRCBDIR)/ft_strjoin.c\
			$(SRCBDIR)/ft_strncmp.c\
			$(SRCBDIR)/ft_strlen.c\
			$(SRCBDIR)/pipex_bonus.c\
			$(SRCBDIR)/pipex_utils_bonus.c\
			$(SRCBDIR)/ft_putstr_fd.c\
			$(SRCBDIR)/get_next_line.c\
			$(SRCBDIR)/get_next_line_utils.c
OBJ		:= $(SRC:.c=.o)
OBJB	:= $(SRCB:.c=.o)
NAME	:= pipex
NAMEB	:= pipex_bonus

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $@

bonus: $(NAMEB)

$(NAMEB): $(OBJB)
	cc $(OBJB) -o $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	cc -Wall -Wextra -Werror -c $< -o $@ 

$(SRCBDIR)/%.o: $(SRCBDIR)/%.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean
	all

.PHONY: all bonus clean fclean re
