# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 13:29:01 by doreshev          #+#    #+#              #
#    Updated: 2022/08/25 19:46:36 by doreshev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFTDIR = ./libft

MLXDIR = ./mlx

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

SRC =	cube3d.c \
		cube3d_utils.c \
		map_init/init.c \
		map_init/ft_map_init.c \
		map_init/ft_check_param.c \
		game/game.c \
		game/ft_game_start.c \
		game/minimap.c \
		game/ft_keys.c \
		game/raycast.c \
		game/game_utils.c \
		game/raycast_sub.c \
		game/keys_left_right.c \

OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
INCLIBFT = -L./libft -lft
INMLX = -L./mlx -lmlx

.c.o:
	${CC} ${FLAGS} -MMD -MP -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)
	${CC} ${OBJ} ${INCLIBFT} ${INMLX} -framework OpenGL -framework AppKit -o ${NAME}

all: ${NAME}

bonus: all

clean:
	${RM} ${OBJ} ${DEP}
	@cd $(LIBFTDIR) && $(MAKE) clean
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEP)