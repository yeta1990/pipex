SRCS	=	ft_printf.c ft_putchar_fd.c ft_putnbr_fd.c ft_strlen.c ft_putstr_fd.c ft_putnbr_base.c ft_num_len.c ft_putnbr_base_long.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	libftprintf.a

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -f

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			ar rc $(NAME) $?

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
