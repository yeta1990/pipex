SRCS		= ft_pipex.c

SRCS_BONUS	= 0 

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= pipex

BONUS_NAME	= 0

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

RM			=	rm -f

INC			= ./inc

%.o:%.c
		$(CC) $(CFLAGS) -c  $< -o $(<:.c=.o)  -I$(INC) 

$(NAME):	$(OBJS)	
			cd srcs/ftprintf && make && cd ../..
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. -lftprintf

$(BONUS_NAME):	$(OBJS_BONUS)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS_NAME)
	

all:		$(NAME)

bonus:		$(BONUS_NAME)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME) $(BONUS_NAME)

re:			fclean all

san:		fclean 	
			$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -o $(NAME) -I$(INC)

.PHONY:		all clean fclean re bonus
