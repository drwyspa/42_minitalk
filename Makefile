# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 21:39:13 by pjedrycz          #+#    #+#              #
#    Updated: 2024/07/31 22:27:18 by pjedrycz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= client.c server.c

OBJS	:= $(SRCS:%.c=%.o)

NAME	= minitalk

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

%.o:	%.c
		${CC} ${FLAGS} -Ilibft -Iprintf -c $? -o $@

${NAME}:	server client

server:		server.o
		@make -C libft
		@make -C printf
		${CC} ${FLAGS} $? -Llibft -lft -Lprintf -lftprintf -o server

client:		client.o
		@make -C libft
		@make -C printf
		${CC} ${FLAGS} $? -Llibft -lft -Lprintf -lftprintf -o client

libft:
		make -C libft

printf:
		make -C printf

clean:
			make clean -C libft
			make clean -C printf
			${RM} ${OBJS}

fclean:		clean
			${RM} server client

re:			fclean all

.PHONY:		libft printf