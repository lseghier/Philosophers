CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -pthread -g3	-I./includes
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
