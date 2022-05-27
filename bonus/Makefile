F_NONE		= \033[37;0m
F_BOLD		= \033[1m
F_ORANGE	= \033[38m
F_RED		= \033[31m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m


CC			= @gcc

CFLAGS		= -Wall -Wextra -Werror -g -lm -D BONUS_ON=1

SRCS		= ../srcs_bonus/main.c \
				../srcs_bonus/objects/obj_lst.c \
				../srcs_bonus/objects/objects.c \
				../srcs_bonus/objects/light_lst.c \
				../srcs_bonus/objects/objects_bonus.c \
				../srcs_bonus/image_tools/screen.c \
				../srcs_bonus/image_tools/colors.c \
				../srcs_bonus/image_tools/rgb.c \
				../srcs_bonus/image_tools/texture.c \
				../srcs_bonus/memory/frees.c \
				../srcs_bonus/memory/memory_log.c \
				../srcs_bonus/memory/data_access.c \
				../srcs_bonus/mlx_tools/mlx_utils.c \
				../srcs_bonus/mlx_tools/mlx_events.c \
				../srcs_bonus/maths/math_fns.c \
				../srcs_bonus/maths/distance.c \
				../srcs_bonus/maths/3D_geo.c \
				../srcs_bonus/maths/points.c \
				../srcs_bonus/maths/angles.c \
				../srcs_bonus/raytracing/color_sp.c \
				../srcs_bonus/raytracing/color_pl.c \
				../srcs_bonus/raytracing/color_cy.c \
				../srcs_bonus/raytracing/color_cn.c \
				../srcs_bonus/raytracing/rays.c \
				../srcs_bonus/raytracing/intersect_sp.c \
				../srcs_bonus/raytracing/ray_on_obj.c \
				../srcs_bonus/raytracing/intersect_pl.c \
				../srcs_bonus/raytracing/intersect_cy.c \
				../srcs_bonus/raytracing/intersect_cy2.c \
				../srcs_bonus/raytracing/intersect_cone.c \
				../srcs_bonus/raytracing/sorting.c \
				../srcs_bonus/raytracing/obj_sorting.c \
				../srcs_bonus/raytracing/phong.c \
				../srcs_bonus/maths/vectors1.c \
				../srcs_bonus/maths/vectors2.c \
				../srcs_bonus/maths/vectors3.c \
				../srcs_bonus/misc_tools/str_display.c \
				../srcs_bonus/misc_tools/inits.c \
				../srcs_bonus/misc_tools/tab_len.c \
				../srcs_bonus/misc_tools/atof.c \
				../srcs_bonus/misc_tools/atoi.c \
				../srcs_bonus/parsing/get_next_line.c \
				../srcs_bonus/parsing/get_next_line_utils.c \
				../srcs_bonus/parsing/parse_file.c \
				../srcs_bonus/parsing/checks.c \
				../srcs_bonus/parsing/check_params.c \
				../srcs_bonus/parsing/checks_bonus.c \
				../srcs_bonus/parsing/strings_functions.c \
				../srcs_bonus/parsing/split.c \
				../srcs_bonus/parsing/populate_obj.c \
				../srcs_bonus/parsing/populate_sp.c \
				../srcs_bonus/parsing/populate_pl.c \
				../srcs_bonus/parsing/populate_cy.c \
				../srcs_bonus/parsing/populate_cn.c \
				../srcs_bonus/ft3d/ft3d_perspective.c \
				../srcs_bonus/ft3d/ft3d_resize.c \
				../srcs_bonus/ft3d/ft3d_rotate.c \
				../srcs_bonus/ft3d/ft3d_set.c \
				../srcs_bonus/ft3d/ft3d_setrot.c \
				../srcs_bonus/ft3d/ft3d_translate.c \
				../srcs_bonus/ft3d/ft3d.c

INCLUDES	= ../includes/miniRT.h \
				../includes/types.h \
				../includes/ft3d.h

OBJS		= $(SRCS:.c=.o)

NAME		= ../miniRT_bonus

LIB_MLX		= ../minilibx-linux/libmlx_Linux.a
MLXPATH		= ../minilibx-linux
MLX_FLAGS	= -lX11 -lXext -lm

# $(LIB_MLX):
# 	make -C ./minilibx-linux

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES) #$(LIB_MLX)
		$(CC) $(OBJS) $(LIB_MLX) -o $(NAME) $(MLX_FLAGS)
		@echo "$(F_GREEN)$(F_BOLD) miniRT_bonus executable is compiled and ready.$(F_NONE)"

clean:
		@rm -f $(OBJS)
#		$(MAKE) -C ./minilibx-linux clean
		@echo "$(F_CYAN)$(F_BOLD) .o files successfully deleted.$(F_NONE)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(F_CYAN)$(F_BOLD) miniRT_bonus executable successfully deleted.$(F_NONE)"
		
re:	fclean $(NAME)

.PHONY: clean fclean all re