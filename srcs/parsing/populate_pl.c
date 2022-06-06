/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:42:27 by mababou           #+#    #+#             */
/*   Updated: 2022/06/06 16:00:25 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

static void	populate_pl_bonus(t_data *data, char **tab, t_plan *obj)
{
	char	**arg;

	if (data->bonus && tab_len(tab) >= 4)
	{
		arg = ft_split(data, tab[3], ",");
		check_arg(data, arg, 3, "Incorrect Plan color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	}
	else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (data->bonus && tab_len(tab) >= 5)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_texture(data, tab[4], obj->texture);
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
	check_int_color("Incorrect Plan color values", obj->rgb);
	populate_pl_bonus(data, tab, obj);
}
