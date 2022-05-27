/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:41:15 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 17:06:15 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

static void	populate_sp_bonus(t_data *data, char **tab, t_sphere *obj)
{
	char	**arg;

	if (BONUS_ON && tab_len(tab) >= 4)
	{
		arg = ft_split(data, tab[3], ",");
		check_arg(data, arg, 3, "Incorrect Sphere color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	}
	else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (BONUS_ON && tab_len(tab) >= 5)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_texture(data, tab[4], obj->texture);
	}
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
	check_int_color("Incorrect Sphere color values", obj->rgb);
	populate_sp_bonus(data, tab, obj);
}
