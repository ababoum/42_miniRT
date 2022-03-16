/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 19:10:34 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	populate_amb(t_data *data, char *line)
{
	char	**tab;
	char	**rgb;

	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 2)
		exit_message(data, "Incorrect 'Ambiance' parameters", EXIT_FAILURE);
	data->amb->grad = ft_atof(tab[0]);
	if (data->amb->grad < 0.0 || data->amb->grad > 1.0)
		exit_message(data, "Incorrect 'Ambiance' ratio", EXIT_FAILURE);
	rgb = ft_split(data, tab[1], ",");
	if (tab_len(rgb) != 3)
		exit_message(data, "Incorrect 'Ambiance' color settings", EXIT_FAILURE);
	data->amb->RGB[0] = ft_atoi(rgb[0]);
	data->amb->RGB[1] = ft_atoi(rgb[1]);
	data->amb->RGB[2] = ft_atoi(rgb[2]);
	if (!check_int_color(data->amb->RGB))
		exit_message(data, "Incorrect 'Ambiance' color values", EXIT_FAILURE);
}

void	populate_light(t_data *data, char *line)
{
	char	**tab;
	char	**src;
	char	**rgb;
	
	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 3)
		exit_message(data, "Incorrect 'Light' parameters", EXIT_FAILURE);
	src = ft_split(data, tab[0], ",");
	if (tab_len(src) != 3)
		exit_message(data, "Incorrect light source coordinates", EXIT_FAILURE);
	data->lum->src = dot_3D(ft_atof(src[0]), ft_atof(src[1]), ft_atof(src[2]));
	data->lum->pow = ft_atof(tab[1]);
	if (data->lum->pow < 0 || data->lum->pow > 1)
		exit_message(data, "Incorrect luminosity value", EXIT_FAILURE);
	rgb = ft_split(data, tab[2], ",");
	if (tab_len(rgb) != 3)
		exit_message(data, "Incorrect 'Light' color settings", EXIT_FAILURE);
	data->lum->RGB[0] = ft_atoi(rgb[0]);
	data->lum->RGB[1] = ft_atoi(rgb[1]);
	data->lum->RGB[2] = ft_atoi(rgb[2]);
	if (!check_int_color(data->lum->RGB))
		exit_message(data, "Incorrect 'Light' color values", EXIT_FAILURE);
}

void	populate_cam(t_data *data, char *line)
{
	char	**tab;
	char	**POV;
	char	**dir;

	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 3)
		exit_message(data, "Incorrect 'Camera' parameters", EXIT_FAILURE);
	POV = ft_split(data, tab[0], ",");
	if (tab_len(POV) != 3)
		exit_message(data, "Incorrect 'POV' coordinates", EXIT_FAILURE);
	data->cam->POV = dot_3D(ft_atof(POV[0]), ft_atof(POV[1]), ft_atof(POV[2]));
	dir = ft_split(data, tab[1], ",");
	if (tab_len(dir) != 3)
		exit_message(data, "Incorrect direction vector format", EXIT_FAILURE);
	data->cam->dir = dot_3D(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2]));
	if (!check_dir_vector(data->cam->dir))
		exit_message(data, "Incorrect direction vector values", EXIT_FAILURE);
	data->cam->FOV = ft_atof(tab[2]);
	if (data->cam->FOV < 0 || data->cam->FOV > 180)
		exit_message(data, "Incorrect FOV value", EXIT_FAILURE);
}
