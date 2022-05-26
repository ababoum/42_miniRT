/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:08:05 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 16:27:36 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	populate_cn(t_data *data, char *line)
{
	char	**tab;
	char	**arg;
	t_cone	*obj;

	tab = ft_split(data, line, SPACES);
	check_line_args_bonus(data, "Cone", tab_len(tab));
	obj = new_cone(data);
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect Cone center coordinates");
	obj->center = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect Cone direction coordinates");
	obj->dir = vector_f(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	if (!check_dir_vector(obj->dir))
		exit_message(data, "Incorrect Cone direction values", EXIT_FAILURE);
	obj->angle = ft_atof(tab[2]);
	if (obj->angle <= 0 || obj->angle >= 90)
		exit_message(data, "Cone angle should be in ]0, 90[", EXIT_FAILURE);
	arg = ft_split(data, tab[3], ",");
	check_arg(data, arg, 3, "Incorrect Cone color settings");
	set_rgb(obj->rgb, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	if (BONUS_ON && tab_len(tab) >= 5)
	{
		arg = ft_split(data, tab[4], ",");
		check_arg(data, arg, 3, "Incorrect Sphere color settings");
		set_rgb(obj->rgb2, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	}
	else
		rgb_cpy(obj->rgb, obj->rgb2);
	if (BONUS_ON && tab_len(tab) >= 6)
	{
		obj->texture = malloc_log(data, TEXTURE_SIZE * TEXTURE_SIZE);
		set_texture(data, tab[5],obj->texture);
	}
	check_int_color("Incorrect Cone color values", obj->rgb);

}
