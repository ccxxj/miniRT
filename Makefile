# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xxu <xxu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/01 13:12:05 by xxu           #+#    #+#                  #
#    Updated: 2021/05/10 19:46:59 by Xiaojing      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
OBJ =	main.o camera_matrix.o intersection.o vector_utils.o\
		get_next_line.o get_next_line_utils.o parsing.o cylinder.o loop.o sq_intersect.o
	
# OBJ = test.o
FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10
HEADER_FILE = minirt.h

all: $(NAME)

# $(NAME):
# 	gcc $(FLAGS) -o $(NAME) $(SRCS)

#to update

%.o: %.c $(HEADER_FILE)
	# $(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
