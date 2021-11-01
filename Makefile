SRCS		= srcs/ft_pipex.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_substr.c srcs/ft_memmove.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_checkers.c srcs/ft_strtrim_full_string.c srcs/ft_split_mod.c srcs/ft_error_handler.c srcs/ft_files.c srcs/ft_path_operations.c

SRCS_BONUS	= srcs/ft_pipex_bonus.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_substr.c srcs/ft_memmove.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_checkers.c srcs/ft_strtrim_full_string.c srcs/ft_split_mod.c srcs/ft_error_handler_bonus.c srcs/ft_files.c srcs/ft_path_operations.c 

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= pipex

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

RM			=	rm -f

INC			= ./inc

%.o:%.c
		$(CC) $(CFLAGS) -c  $< -o $(<:.c=.o)  -I$(INC) 

$(NAME):	$(OBJS)	
			cd srcs/ftprintf && make && cd ../..
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./srcs/ftprintf/ -lftprintf

bonus:		$(OBJS_BONUS)
			cd srcs/ftprintf && make && cd ../..
			$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) -L./srcs/ftprintf/ -lftprintf

all:		$(NAME)

clean:
			cd srcs/ftprintf && make clean && cd ../..
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			cd srcs/ftprintf && make fclean && cd ../..
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
