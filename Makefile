# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:19:15 by jibot             #+#    #+#              #
#    Updated: 2022/01/13 22:10:27 by jibot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=42

SRCS	= FdF.c FdF_calc.c FdF_pixel_put.c FdF_utils.c ./libft/ft_calloc.c ./libft/ft_split.c get_next_line.c get_next_line_utils.c ./libft/ft_isdigit.c ./libft/ft_pwr.c ./libft/ft_sqrt.c ./libft/ft_atoi.c

OBJS	= ${SRCS:.c=.o}

all:		${NAME}

%.o:	%.c
			${CC} ${CFLAGS} -Imlx -c $< -o $@

${NAME}:	${OBJS} 
			${CC} ${OBJS} -lmlx -framework OpenGL -framework AppKit -o ${NAME}
			
clean: 
			${RM} ${SRCS:.c=.o} ${B_SRCS:.c=.o}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus_re:	fclean bonus

.PHONY:		all clean fclean re
