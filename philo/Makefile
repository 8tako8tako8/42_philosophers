NAME		:=	philo
CC			:=	gcc
#CFLAGS		:=	-Wall -Wextra -Werror
CFLAGS		:=	
SRC_DIR		:=	./srcs
SRCS		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/eat.c \
				$(SRC_DIR)/get_time.c \
				$(SRC_DIR)/init.c \
				$(SRC_DIR)/libft.c \
				$(SRC_DIR)/philo_life.c \
				$(SRC_DIR)/print.c \
				$(SRC_DIR)/sleep_think.c \
				$(SRC_DIR)/thread.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/watcher.c
INCLUDE		:=	-I./includes
OBJS		:=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDE) $(SRCS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re