F_NONE		= \033[37m
F_BOLD		= \033[1m
F_ORANGE	= \033[38m
F_RED		= \033[31m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m


CC			= @gcc

SRCS		= ./srcs/main.c \
				

INCLUDES	= ./includes/miniRT.h \
			./includes/types.h

OBJS		= $(SRCS:.c=.o)

FLAGS		= -Wall -Wextra -Werror -g -fsanitize=address

NAME		= miniRT

MLXPATH		= ./minilibx_opengl_20191021

all: $(NAME)

$(NAME):	$(OBJS) $(INCL)
		make -C ${MLXPATH}
		$(CC) $(FLAGS) $(SRCS) -o $(NAME) -L ${MLXPATH} -lm -lbsd -lX11 -lXext
		@echo "$(F_GREEN)$(F_BOLD) $(NAME) executable is compiled and ready.$(F_NONE)"

clean:
		@rm -f $(OBJS)
		@echo "$(F_CYAN)$(F_BOLD) .o files successfully deleted.$(F_NONE)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(F_CYAN)$(F_BOLD) $(NAME) executable successfully deleted.$(F_NONE)"

re:	fclean $(NAME)

.PHONY: clean fclean all re