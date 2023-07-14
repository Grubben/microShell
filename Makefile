NAME		= microshell

CC 			= cc
CFLAGS		= -g3 -Wall -Wextra #-Werror

RM			= rm -rf

SRCS		= $(wildcard *.c)

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all			: $(NAME)

clean		:
				$(RM) $(OBJS)

fclean		: clean
				$(RM) *.out* $(NAME)
				$(RM) *.a

re			: fclean $(NAME)

c			:
				clear

f			: fclean

r			: f c $(NAME)

.PHONY		: re fclean clean all f 
