# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:19:15 by jibot             #+#    #+#              #
#    Updated: 2022/03/25 16:13:34 by jibot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

CC		= gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42

MLX		= -lmlx -framework OpenGL -framework Appkit

RM		= rm -f

FILE	= FdF.c

ifdef AVEC_BONUS
	FILE = FdF_bonus.c
endif

SRCS	= ${FILE} FdF_draw.c FdF_handle.c FdF_calc.c FdF_pixel_put.c FdF_utils.c get_next_line.c get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

all:		${NAME}

bonus:		
			@make AVEC_BONUS=1 all

%.o:	%.c
			${CC} ${CFLAGS} -Imlx -c $< -o $@

${NAME}:	${OBJS}
			make all -C ./libft
			${CC} -o ${NAME} ${OBJS} ${MLX} libft/libft.a
			
clean: 
			${RM} ${SRCS:.c=.o} FdF_bonus.o

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus_re:	fclean bonus

.PHONY:		all clean fclean re
