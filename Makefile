F_NONE		= \033[37;0m
F_BOLD		= \033[1m
F_ORANGE	= \033[38m
F_RED		= \033[31m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m


CC			= @gcc

#Remove -O3 -fsanitize=address for debuging
CFLAGS		= -Wall -Wextra -Werror -g -lm


SRCS		= ./srcs/main.c \
				./srcs/image_tools/2D_drawing.c \
				./srcs/image_tools/obj_lst.c \
				./srcs/image_tools/objects.c \
				./srcs/image_tools/colors.c \
				./srcs/image_tools/rgb.c \
				./srcs/memory/frees.c \
				./srcs/memory/memory_log.c \
				./srcs/memory/data_access.c \
				./srcs/mlx_tools/mlx_utils.c \
				./srcs/mlx_tools/mlx_events.c \
				./srcs/maths/math_fns.c \
				./srcs/maths/distance.c \
				./srcs/maths/3D_geo.c \
				./srcs/maths/intersect_sp.c \
				./srcs/maths/intersect_pl.c \
				./srcs/maths/vectors1.c \
				./srcs/maths/vectors2.c \
				./srcs/maths/vision_field.c \
				./srcs/misc_tools/str_display.c \
				./srcs/misc_tools/inits.c \
				./srcs/misc_tools/tab_len.c \
				./srcs/misc_tools/atof.c \
				./srcs/misc_tools/atoi.c \
				./srcs/parsing/get_next_line.c \
				./srcs/parsing/get_next_line_utils.c \
				./srcs/parsing/parse_file.c \
				./srcs/parsing/checks.c \
				./srcs/parsing/strings_functions.c \
				./srcs/parsing/split.c \
				./srcs/parsing/populate_obj.c \
				./srcs/parsing/populate_obj2.c \
				./srcs/ft3d/ft3d_perspective.c \
				./srcs/ft3d/ft3d_resize.c \
				./srcs/ft3d/ft3d_rotate.c \
				./srcs/ft3d/ft3d_set.c \
				./srcs/ft3d/ft3d_setrot.c \
				./srcs/ft3d/ft3d_translate.c \
				./srcs/ft3d/ft3d.c \


INCLUDES	= ./includes/miniRT.h \
				./includes/types.h \
				./includes/ft3d.h

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

LIB_MLX		= ./minilibx-linux/libmlx_Linux.a
MLXPATH		= ./minilibx-linux
MLX_FLAGS	= -lX11 -lXext -lm

# $(LIB_MLX):
# 	make -C ./minilibx-linux

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES) #$(LIB_MLX)
		$(CC) $(CFLAGS) $(OBJS) $(LIB_MLX) -o $(NAME) $(MLX_FLAGS)
		@echo "$(F_GREEN)$(F_BOLD) $(NAME) executable is compiled and ready.$(F_NONE)"

clean:
		@rm -f $(OBJS)
#		$(MAKE) -C ./minilibx-linux clean
		@echo "$(F_CYAN)$(F_BOLD) .o files successfully deleted.$(F_NONE)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(F_CYAN)$(F_BOLD) $(NAME) executable successfully deleted.$(F_NONE)"

re:	fclean $(NAME)

.PHONY: clean fclean all re