# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:19:15 by jibot             #+#    #+#              #
#    Updated: 2021/12/30 15:19:21 by jibot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra

SRCS	= FdF.c 

OBJS	= ${SRCS:.c=.o}

all:		${NAME}

%.o:	%.c
			${CC} ${CFLAGS} -Imlx -c $< -o $@

${NAME}:	${OBJS} 
			${CC} ${SRCS} -lmlx -framework OpenGL -framework AppKit -o ${NAME}
			
clean: 
			${RM} ${SRCS:.c=.o} ${B_SRCS:.c=.o}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus_re:	fclean bonus

.PHONY:		all clean fclean re
