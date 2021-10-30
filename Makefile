SRCS		= srcs/ft_pipex.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_substr.c srcs/ft_memmove.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_checkers.c srcs/ft_strtrim_full_string.c srcs/ft_split_mod.c srcs/ft_error_handler.c srcs/ft_files.c

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
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./srcs/ftprintf/ -lftprintf

$(BONUS_NAME):	$(OBJS_BONUS)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS_NAME)
	

all:		$(NAME)

bonus:		$(BONUS_NAME)

clean:
			cd srcs/ftprintf && make clean && cd ../..
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			cd srcs/ftprintf && make fclean && cd ../..
			$(RM) $(NAME) $(BONUS_NAME)

re:			fclean all

san:		fclean 	
			cd srcs/ftprintf && make && cd ../..
			$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -o $(NAME) -I$(INC)  -L./srcs/ftprintf/ -lftprintf


.PHONY:		all clean fclean re bonus
