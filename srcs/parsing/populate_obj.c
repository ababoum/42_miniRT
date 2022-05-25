/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/05/25 18:42:39 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	populate_amb(t_data *data, char *line)
{
	char	**tab;
	char	**rgb;

	check_scene_setting(data, AMBIANCE);
	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Ambiance", tab_len(tab));
	data->amb->grad = ft_atof(tab[0]);
	if (data->amb->grad < 0.0 || data->amb->grad > 1.0)
		exit_message(data, "Incorrect 'Ambiance' ratio", EXIT_FAILURE);
	rgb = ft_split(data, tab[1], ",");
	check_arg(data, rgb, 3, "Incorrect 'Ambiance' color settings");
	data->amb->rgb[0] = ft_atoi(rgb[0]);
	data->amb->rgb[1] = ft_atoi(rgb[1]);
	data->amb->rgb[2] = ft_atoi(rgb[2]);
	check_int_color("Incorrect 'Ambiance' color values", data->amb->rgb);
}

void	populate_light(t_data *data, char *line)
{
	char	**tab;
	char	**arg;
	t_light	*lux;

	check_scene_setting(data, LIGHT);
	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Light", tab_len(tab));
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect light source coordinates");
	lux = new_light_src(data);
	lux->src = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	lux->pow = ft_atof(tab[1]);
	if (!is_between(lux->pow, 0, 1))
		exit_message(data, "Incorrect luminosity value", EXIT_FAILURE);
	arg = ft_split(data, tab[2], ",");
	check_arg(data, arg, 3, "Incorrect 'Light' color settings");
	set_rgb(lux->rgb, ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
	check_int_color("Incorrect 'Light' color values", lux->rgb);
}

void	populate_cam(t_data *data, char *line)
{
	char	**tab;
	char	**arg;

	check_scene_setting(data, CAMERA);
	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Camera", tab_len(tab));
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect 'POV' coordinates");
	data->cam->pov = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect direction vector format");
	data->cam->dir = vector_f(ft_atof(arg[0]), \
							ft_atof(arg[1]), ft_atof(arg[2]));
	if (!check_dir_vector(data->cam->dir))
		exit_message(data, "Incorrect direction vector values", EXIT_FAILURE);
	data->cam->fov = ft_atof(tab[2]);
	if (data->cam->fov < 0 || data->cam->fov > 180)
		exit_message(data, "Incorrect FOV value", EXIT_FAILURE);
}
