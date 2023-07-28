NAME	:= pipex
SRC		:= ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c pipex_bonus.c
OBJ		:= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $@

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean
	all

.PHONY: all clean fclean re