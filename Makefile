F_NONE		= \033[37m
F_BOLD		= \033[1m
F_ORANGE	= \033[38m
F_RED		= \033[31m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m


CC			= @gcc

CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address -lm -O3

SRCS		= ./srcs/main.c \
				./srcs/image_tools/2D_drawing.c \
				./srcs/memory/frees.c \
				./srcs/memory/memory_log.c \
				./srcs/mlx_tools/mlx_utils.c \
				
INCLUDES	= ./includes/miniRT.h \
				./includes/types.h

OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(MLXPATH)

NAME		= miniRT

LIB_MLX		= ./minilibx-linux/libmlx_Linux.a
MLXPATH		= ./minilibx-linux
MLX_FLAGS	= -lX11 -lXext

$(LIB_MLX):
	$(MAKE) -C ./minilibx-linux

all: $(NAME)

$(NAME): $(LIB_MLX) $(OBJS) $(INCLUDES)
		$(CC) $(CFLAGS) $(OBJS) $(LIB_MLX) -o $(NAME) $(MLX_FLAGS)
		@echo "$(F_GREEN)$(F_BOLD) $(NAME) executable is compiled and ready.$(F_NONE)"

clean:
		@rm -f $(OBJS)
		$(MAKE) -C ./minilibx-linux clean
		@echo "$(F_CYAN)$(F_BOLD) .o files successfully deleted.$(F_NONE)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(F_CYAN)$(F_BOLD) $(NAME) executable successfully deleted.$(F_NONE)"

re:	fclean $(NAME)

.PHONY: clean fclean all re