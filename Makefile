# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xxu <xxu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/01 13:12:05 by xxu           #+#    #+#                  #
#    Updated: 2021/06/11 14:51:24 by Xiaojing      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

MLX = libmlx.dylib
OBJ =	main.o minirt.o parsingredo.o parsingredo2.o vector_utils.o get_next_line.o utils.o\
		camera_matrix.o cylinder.o intersection.o light.o loop.o render.o sq_intersect.o\
		buffer.o bmp.o intersection2.o loop2.o utils2.o free.o ft_split.o check_inputfile.o errors.o utils3.o

FLAGS = -Wall -Wextra -Werror
HEADER_FILE = minirt.h

all: library $(NAME)

%.o: %.c $(HEADER_FILE)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJ)
	cp mlx/$(MLX) ./$(MLX)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f *.o
	cd mlx && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm ./$(MLX)

re: fclean all

library:
	cd mlx && $(MAKE) all
