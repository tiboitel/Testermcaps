# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/07 01:27:33 by tiboitel          #+#    #+#              #
#    Updated: 2018/05/26 23:25:52 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		 =	bomberman
SRCS 		 = 	main.c \
				termcaps.c \
				game.c \
				player.c \
				maps.c \
				mods.c
INCLUDES	 =	./includes
SRCSPATH 	 =	./srcs/

CC			 = gcc
CFLAGS		 = -Wall -Werror -Wextra -std=gnu99
INCLUDES_O	 = -I $(INCLUDES)
INCLUDES_C	 = -L /usr/lib -ltermcap


SRC			 = $(addprefix $(SRCSPATH), $(SRCS))
OBJS		 = $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C)

%.o: %.c
			$(CC) -o $@ $(INCLUDES_O) -c $< $(CFLAGS)

clean:
			rm -rf $(OBJS)

fclean: 	clean
			rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
			
