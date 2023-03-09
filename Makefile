NAME = pipex

SRC=  pipex.c pipex_here_doc.c pipex_bonus.c ft_printf.c ft_split.c ft_strchr.c ft_strjoin.c ft_strncmp.c ft_strtrim.c ft_substr.c ft_strlen.c get_next_line.c get_next_line_utils.c

OBJ= $(SRC:.c=.o)

CC = cc

CFLAGS=  -Wall -Wextra -Werror 

$(RM) = rm -f 
  
all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all