F_NONE			= \033[37;0m
F_BOLD			= \033[1m
F_ORANGE		= \033[38m
F_RED			= \033[31m
F_YELLOW		= \033[33m
F_GREEN			= \033[32m
F_CYAN			= \033[36m
F_BLUE			= \033[34m


CC				= @gcc

CFLAGS			= -Wall -Wextra -Werror -g -lm

SRCS			= srcs/main.c \
				srcs/objects/obj_lst.c \
				srcs/objects/objects.c \
				srcs/objects/light_lst.c \
				srcs/objects/objects_bonus.c \
				srcs/image_tools/screen.c \
				srcs/image_tools/colors.c \
				srcs/image_tools/rgb.c \
				srcs/image_tools/texture.c \
				srcs/memory/frees.c \
				srcs/memory/memory_log.c \
				srcs/memory/data_access.c \
				srcs/mlx_tools/mlx_utils.c \
				srcs/mlx_tools/mlx_events.c \
				srcs/maths/math_fns.c \
				srcs/maths/distance.c \
				srcs/maths/3D_geo.c \
				srcs/maths/points.c \
				srcs/maths/angles.c \
				srcs/raytracing/color_sp.c \
				srcs/raytracing/color_pl.c \
				srcs/raytracing/color_cy.c \
				srcs/raytracing/color_cn.c \
				srcs/raytracing/rays.c \
				srcs/raytracing/intersect_sp.c \
				srcs/raytracing/ray_on_obj.c \
				srcs/raytracing/intersect_pl.c \
				srcs/raytracing/intersect_cy.c \
				srcs/raytracing/intersect_cy2.c \
				srcs/raytracing/intersect_cone.c \
				srcs/raytracing/sorting.c \
				srcs/raytracing/obj_sorting.c \
				srcs/raytracing/phong.c \
				srcs/maths/vectors1.c \
				srcs/maths/vectors2.c \
				srcs/maths/vectors3.c \
				srcs/misc_tools/str_display.c \
				srcs/misc_tools/inits.c \
				srcs/misc_tools/tab_len.c \
				srcs/misc_tools/atof.c \
				srcs/misc_tools/atoi.c \
				srcs/parsing/get_next_line.c \
				srcs/parsing/get_next_line_utils.c \
				srcs/parsing/parse_file.c \
				srcs/parsing/checks.c \
				srcs/parsing/check_params.c \
				srcs/parsing/checks_bonus.c \
				srcs/parsing/strings_functions.c \
				srcs/parsing/split.c \
				srcs/parsing/populate_obj.c \
				srcs/parsing/populate_sp.c \
				srcs/parsing/populate_pl.c \
				srcs/parsing/populate_cy.c \
				srcs/parsing/populate_cn.c \
				srcs/ft3d/ft3d_perspective.c \
				srcs/ft3d/ft3d_resize.c \
				srcs/ft3d/ft3d_rotate.c \
				srcs/ft3d/ft3d_set.c \
				srcs/ft3d/ft3d_setrot.c \
				srcs/ft3d/ft3d_translate.c \
				srcs/ft3d/ft3d.c
				

SRCS_MANDATORY	=  srcs/mandatory.c
SRCS_BONUS		=  srcs/bonus.c

INCLUDES		= includes/miniRT.h \
				includes/types.h \
				includes/ft3d.h

OBJS			= $(SRCS:.c=.o)
OBJS_MANDATORY	= $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

NAME			= miniRT
NAME_BONUS		= miniRT_bonus

LIB_MLX			= minilibx-linux/libmlx_Linux.a
MLXPATH			= minilibx-linux
MLX_FLAGS		= -lX11 -lXext -lm


all: $(NAME)

$(NAME): $(OBJS) $(OBJS_MANDATORY) $(INCLUDES)
		make -C ./minilibx-linux
		$(CC) $(OBJS) $(OBJS_MANDATORY) $(LIB_MLX) -o $(NAME) $(MLX_FLAGS)
		@echo "$(F_GREEN)$(F_BOLD) $(NAME) executable is compiled and ready.$(F_NONE)"

clean:
		@rm -f $(OBJS)
		@rm -f $(OBJS_MANDATORY) $(OBJS_BONUS)
		make -C ./minilibx-linux clean
		@echo "$(F_CYAN)$(F_BOLD) .o files successfully deleted.$(F_NONE)"

fclean:	clean
		@rm -f $(NAME)
		@rm -f $(NAME_BONUS)
		@rm -f $(LIB_MLX)
		@echo "$(F_CYAN)$(F_BOLD) $(NAME) executable(s) successfully deleted.$(F_NONE)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(OBJS_BONUS) $(INCLUDES)
		make -C ./minilibx-linux
		$(CC) $(OBJS) $(OBJS_BONUS) $(LIB_MLX) -o $(NAME)_bonus $(MLX_FLAGS)
		@echo "$(F_GREEN)$(F_BOLD) $(NAME_BONUS) executable is compiled and ready.$(F_NONE)"
		
re:	fclean $(NAME)

.PHONY: clean fclean all re bonus