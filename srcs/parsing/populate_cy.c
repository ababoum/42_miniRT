/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:42:55 by mababou           #+#    #+#             */
/*   Updated: 2022/06/06 16:00:21 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

static void	populate_cy_bonus(t_data *data, char **tab, t_cyl *obj)
{
	char	**arg;

	if (data->bonus && tab_len(tab) == 6)
	{
		arg = ft_split(data, tab[5], ",");
		check_arg(data, arg, 3, "Incorrect Cylinder color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	}
	else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (data->bonus && tab_len(tab) >= 7)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_texture(data, tab[6], obj->texture);
	}
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
	check_int_color("Incorrect Cylinder color values", obj->rgb);
	populate_cy_bonus(data, tab, obj);
}
