# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriley <mriley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/27 12:36:50 by noobythetur       #+#    #+#              #
#    Updated: 2019/09/20 18:22:57 by mriley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c fdf_one.c fdf_two.c fdf_tree.c fdf_six.c fdf_nine.c fdf_four.c fdf_five.c fdf_ten.c fdf_eleven.c

FLAGS	= -Wall -Wextra -Werror

OBJ = $(SRC:%.c=%.o)

LIB = ./ft_printf_git/

LIB_MLX = ./minilibx_macos/

all: $(NAME)

$(NAME):
	@make -C $(LIB)
	@gcc $(FLAGS) -c $(SRC)
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -L$(LIB) -lftprintf -L$(LIB_MLX) -lmlx -framework OpenGL -framework AppKit

test:
	@gcc -c $(SRC) -g
	@gcc -o $(NAME) $(OBJ) -L$(LIB) -lftprintf -L$(LIB_MLX) -lmlx -framework OpenGL -framework AppKit -g

clean:
	@make -C $(LIB) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIB) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re