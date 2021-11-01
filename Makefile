SRCS		= srcs/ft_pipex.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_substr.c srcs/ft_memmove.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_checkers.c srcs/ft_strtrim_full_string.c srcs/ft_split_mod.c srcs/ft_error_handler.c srcs/ft_files.c srcs/ft_path_operations.c srcs/ft_split.c srcs/ft_putstr_fd.c srcs/ft_putchar_fd.c

SRCS_BONUS	= srcs/ft_pipex_bonus.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_substr.c srcs/ft_memmove.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_checkers.c srcs/ft_strtrim_full_string.c srcs/ft_split_mod.c srcs/ft_error_handler_bonus.c srcs/ft_files.c srcs/ft_path_operations.c srcs/ft_split.c srcs/ft_putstr_fd.c srcs/ft_putchar_fd.c

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
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:		$(OBJS_BONUS)
			$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
