/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/03/15 18:29:37 by mababou          ###   ########.fr       */
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
	data->amb->R = ft_atoi(rgb[0]);
	data->amb->G = ft_atoi(rgb[1]);
	data->amb->B = ft_atoi(rgb[2]);
	if (!check_int_color(data->amb->R) || !check_int_color(data->amb->G) || \
		!check_int_color(data->amb->B))
		exit_message(data, "Incorrect 'Ambiance' color values", EXIT_FAILURE);
}

void	populate_light(t_data *data, char *line)
{

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
	data->cam->POV = point_3D();
}
