# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:51:07 by mwallage          #+#    #+#              #
#    Updated: 2023/08/03 15:46:21 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
AR		:= ar
CFLAGS	:= -Wall -Werror -Wextra
SRCDIR	:= src
PRINTFDIR	:=	Printf
SRC 	:= $(SRCDIR)/ft_isalpha.c \
		$(SRCDIR)/ft_isdigit.c \
		$(SRCDIR)/ft_isalnum.c \
		$(SRCDIR)/ft_isascii.c \
		$(SRCDIR)/ft_isprint.c \
		$(SRCDIR)/ft_strlen.c \
		$(SRCDIR)/ft_memset.c \
		$(SRCDIR)/ft_bzero.c \
		$(SRCDIR)/ft_memcpy.c \
		$(SRCDIR)/ft_memmove.c \
		$(SRCDIR)/ft_strlcpy.c \
		$(SRCDIR)/ft_strlcat.c \
		$(SRCDIR)/ft_toupper.c \
		$(SRCDIR)/ft_tolower.c \
		$(SRCDIR)/ft_strchr.c \
		$(SRCDIR)/ft_strrchr.c \
		$(SRCDIR)/ft_strncmp.c \
		$(SRCDIR)/ft_memchr.c \
		$(SRCDIR)/ft_memcmp.c \
		$(SRCDIR)/ft_strnstr.c \
		$(SRCDIR)/ft_atoi.c \
		$(SRCDIR)/ft_calloc.c \
		$(SRCDIR)/ft_strdup.c \
		$(SRCDIR)/ft_substr.c \
		$(SRCDIR)/ft_strjoin.c \
		$(SRCDIR)/ft_strtrim.c \
		$(SRCDIR)/ft_split.c \
		$(SRCDIR)/ft_itoa.c \
		$(SRCDIR)/ft_strmapi.c \
		$(SRCDIR)/ft_striteri.c \
		$(SRCDIR)/ft_putchar_fd.c \
		$(SRCDIR)/ft_putstr_fd.c \
		$(SRCDIR)/ft_putendl_fd.c \
		$(SRCDIR)/ft_putnbr_fd.c \
		$(SRCDIR)/ft_lstnew.c \
		$(SRCDIR)/ft_lstadd_front.c \
		$(SRCDIR)/ft_lstsize.c \
		$(SRCDIR)/ft_lstlast.c \
		$(SRCDIR)/ft_lstadd_back.c \
		$(SRCDIR)/ft_lstdelone.c \
		$(SRCDIR)/ft_lstclear.c \
		$(SRCDIR)/ft_lstiter.c \
		$(SRCDIR)/ft_lstmap.c \
		$(SRCDIR)/get_next_line.c \
		$(SRCDIR)/get_next_line_utils.c \
		$(PRINTFDIR)/conversions.c \
		$(PRINTFDIR)/conversions_hex.c \
		$(PRINTFDIR)/conversion_utils.c \
		$(PRINTFDIR)/ft_printf.c \
		$(PRINTFDIR)/put_conversions.c \
		$(PRINTFDIR)/read_modifiers.c \
		$(PRINTFDIR)/utils.c
OBJ		:= $(SRC:.c=.o)
NAME	:= libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $@ $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
