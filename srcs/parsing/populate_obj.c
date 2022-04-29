/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/04/29 16:42:45 by mababou          ###   ########.fr       */
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
	if (!check_int_color(data->amb->rgb))
		exit_message(data, "Incorrect 'Ambiance' color values", EXIT_FAILURE);
}

void	populate_light(t_data *data, char *line)
{
	char	**tab;
	char	**arg;

	check_scene_setting(data, LIGHT);
	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Light", tab_len(tab));
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect light source coordinates");
	data->lum->src = dot_3d(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	data->lum->pow = ft_atof(tab[1]);
	if (data->lum->pow < 0 || data->lum->pow > 1)
		exit_message(data, "Incorrect luminosity value", EXIT_FAILURE);
	arg = ft_split(data, tab[2], ",");
	check_arg(data, arg, 3, "Incorrect 'Light' color settings");
	data->lum->rgb[0] = ft_atoi(arg[0]);
	data->lum->rgb[1] = ft_atoi(arg[1]);
	data->lum->rgb[2] = ft_atoi(arg[2]);
	if (!check_int_color(data->lum->rgb))
		exit_message(data, "Incorrect 'Light' color values", EXIT_FAILURE);
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
	data->cam->pov = dot_3d(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect direction vector format");
	data->cam->dir = dot_3d(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	if (!check_dir_vector_p(data->cam->dir))
		exit_message(data, "Incorrect direction vector values", EXIT_FAILURE);
	data->cam->fov = ft_atof(tab[2]);
	if (data->cam->fov < 0 || data->cam->fov > 180)
		exit_message(data, "Incorrect FOV value", EXIT_FAILURE);
}
