/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:33:24 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	populate_amb(t_data *data, char *line)
{
	char	**tab;
	char	**rgb;

	check_amb(data);
	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 2)
		exit_message(data, "Incorrect 'Ambiance' parameters", EXIT_FAILURE);
	data->amb->grad = ft_atof(tab[0]);
	if (data->amb->grad < 0.0 || data->amb->grad > 1.0)
		exit_message(data, "Incorrect 'Ambiance' ratio", EXIT_FAILURE);
	rgb = ft_split(data, tab[1], ",");
	if (tab_len(rgb) != 3)
		exit_message(data, "Incorrect 'Ambiance' color settings", EXIT_FAILURE);
	data->amb->rgb[0] = ft_atoi(rgb[0]);
	data->amb->rgb[1] = ft_atoi(rgb[1]);
	data->amb->rgb[2] = ft_atoi(rgb[2]);
	if (!check_int_color(data->amb->rgb))
		exit_message(data, "Incorrect 'Ambiance' color values", EXIT_FAILURE);
}

void	populate_light(t_data *data, char *line)
{
	char	**tab;
	char	**src;
	char	**rgb;

	check_lum(data);
	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 3)
		exit_message(data, "Incorrect 'Light' parameters", EXIT_FAILURE);
	src = ft_split(data, tab[0], ",");
	if (tab_len(src) != 3)
		exit_message(data, "Incorrect light source coordinates", EXIT_FAILURE);
	data->lum->src = dot_3d(ft_atof(src[0]), ft_atof(src[1]), ft_atof(src[2]));
	data->lum->pow = ft_atof(tab[1]);
	if (data->lum->pow < 0 || data->lum->pow > 1)
		exit_message(data, "Incorrect luminosity value", EXIT_FAILURE);
	rgb = ft_split(data, tab[2], ",");
	if (tab_len(rgb) != 3)
		exit_message(data, "Incorrect 'Light' color settings", EXIT_FAILURE);
	data->lum->rgb[0] = ft_atoi(rgb[0]);
	data->lum->rgb[1] = ft_atoi(rgb[1]);
	data->lum->rgb[2] = ft_atoi(rgb[2]);
	if (!check_int_color(data->lum->rgb))
		exit_message(data, "Incorrect 'Light' color values", EXIT_FAILURE);
}

void	populate_cam(t_data *data, char *line)
{
	char	**tab;
	char	**pov;
	char	**dir;

	check_amb(data);
	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 3)
		exit_message(data, "Incorrect 'Camera' parameters", EXIT_FAILURE);
	pov = ft_split(data, tab[0], ",");
	if (tab_len(pov) != 3)
		exit_message(data, "Incorrect 'pov' coordinates", EXIT_FAILURE);
	data->cam->pov = dot_3d(ft_atof(pov[0]), ft_atof(pov[1]), ft_atof(pov[2]));
	dir = ft_split(data, tab[1], ",");
	if (tab_len(dir) != 3)
		exit_message(data, "Incorrect direction vector format", EXIT_FAILURE);
	data->cam->dir = dot_3d(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2]));
	if (!check_dir_vector(data->cam->dir))
		exit_message(data, "Incorrect direction vector values", EXIT_FAILURE);
	data->cam->fov = ft_atof(tab[2]);
	if (data->cam->fov < 0 || data->cam->fov > 180)
		exit_message(data, "Incorrect fov value", EXIT_FAILURE);
}
