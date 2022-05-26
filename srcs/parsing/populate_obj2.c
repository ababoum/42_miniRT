/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/05/18 14:01:32 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"


void set_Texture(t_data *data, char *filename, unsigned char *texture)
{
	int w;
	int h;
	t_img *img;
	img = mlx_xpm_file_to_image (data->session , filename, &w, &h );

	if (img == 0)
		exit_message(data, "Can't load texture.xpm", 4);
	if (w != TEXTURE_SIZE || h != TEXTURE_SIZE)
		exit_message(data, "Bad texture.xpm size", 4);

	int i = 0;
	while (i < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		texture[i] = *(img->data + 4 * i);
		i++;
	}

}

void	populate_plan(t_data *data, char *line)
{
	char		**tab;
	char		**arg;
	t_plan		*obj;

	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Plan", tab_len(tab));
	obj = new_plan(data);
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect Plan point coordinates");
	obj->point = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect Plan normal coordinates");
	obj->normal = vector_f(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[2], ",");
	check_arg(data, arg, 3, "Incorrect Plan color settings");
	set_rgb(obj->rgb, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	if (BONUS_ON && tab_len(tab) >= 4)
	{
		arg = ft_split(data, tab[3], ",");
		check_arg(data, arg, 3, "Incorrect Sphere color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	} else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (BONUS_ON && tab_len(tab) >= 5)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_Texture(data, tab[4],obj->texture);
	}
	check_int_color("Incorrect Plan color values",obj->rgb);

}
void	populate_sphere(t_data *data, char *line)
{
	char		**tab;
	char		**arg;
	t_sphere	*obj;

	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Sphere", tab_len(tab));
	obj = new_sphere(data);
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect Sphere center coordinates");
	obj->center = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	obj->radius = ft_atof(tab[1]) / 2;
	arg = ft_split(data, tab[2], ",");
	check_arg(data, arg, 3, "Incorrect Sphere color settings");
	set_rgb(obj->rgb, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	if (BONUS_ON && tab_len(tab) >= 4)
	{
		arg = ft_split(data, tab[3], ",");
		check_arg(data, arg, 3, "Incorrect Sphere color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	} else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (BONUS_ON && tab_len(tab) >= 5)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_Texture(data, tab[4],obj->texture);
	}
	check_int_color("Incorrect Sphere color values",obj->rgb);
}

void	populate_cyl(t_data *data, char *line)
{
	char	**tab;
	char	**arg;
	t_cyl	*obj;

	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Cylinder", tab_len(tab));
	obj = new_cylinder(data);
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder point coordinates");
	obj->point = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder direction coordinates");
	obj->dir = vector_f(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	normalize_v(&(obj->dir));
	if (!check_dir_vector(obj->dir))
		exit_message(data, "Incorrect Cylinder direction values", EXIT_FAILURE);
	obj->radius = ft_atof(tab[2]) / 2;
	if (obj->radius <= 0)
		exit_message(data, "Cylinder radius must be > 0", EXIT_FAILURE);
	obj->height = ft_atof(tab[3]);
	arg = ft_split(data, tab[4], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder color settings");
	set_rgb(obj->rgb, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	if (BONUS_ON && tab_len(tab) == 6)
	{
		arg = ft_split(data, tab[5], ",");
		check_arg(data, arg, 3, "Incorrect Sphere color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	} else
		rgb_cpy(obj->rgb, obj->rgb2);
	check_int_color("Incorrect Cylinder color values", obj->rgb);
}
