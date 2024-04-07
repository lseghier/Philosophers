# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseghier <lseghier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 00:32:41 by lseghier          #+#    #+#              #
#    Updated: 2024/04/07 02:13:23 by lseghier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -pthread -g3	-I./includes #-fsanitize=thread
NAME 	= philo
SRCS	= ./srcs/dinner.c ./srcs/getters_setters.c ./srcs/init.c ./srcs/main.c \
		  ./srcs/monitor.c ./srcs/parsing.c ./srcs/safe_functions.c ./srcs/synchro_utils.c \
		  ./srcs/utils.c ./srcs/write.c \

OBJS 	= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(SRCS) $(CFLAGS)

clean:
				$(RM) $(OBJS)

fclean:	 		clean
				$(RM) $(NAME)


re:				fclean all

.PHONY:			all clean fclean re
