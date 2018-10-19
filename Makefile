# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/01 16:40:49 by ghazette     #+#   ##    ##    #+#        #
#    Updated: 2018/03/09 12:41:19 by ghazette    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fractol

SRCS =		srcs/main.c\
			srcs/dealkey.c\
			srcs/mlx.c\
			srcs/mlx2.c\
			srcs/algo.c

HEADERS = 	libft/includes/libft.h includes/fractol.h minilibx/mlx.h

LIBFT =		libft/libft.a

MLX	  =		minilibx/libmlx.a

CFLAGS = 	-Wall -Werror -Wextra -O2

FRAMEWORK = -framework OpenGL -framework AppKit

OBJS = 	$(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(FRAMEWORK) -o $(NAME)

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c -o $@ $<

$(MLX):
	make -C minilibx

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C minilibx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C minilibx fclean

re : fclean all

.PHONY: all clean fclean re
