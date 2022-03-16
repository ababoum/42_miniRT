/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 19:14:08 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	populate_plan(t_data *data, char *line)
{
	(void)data;
	(void)line;
}

void	populate_sphere(t_data *data, char *line)
{
	char		**tab;
	char		**spc;
	char		**rgb;
	t_sphere	*sp;

	tab = ft_split(data, line, " \t");
	if (tab_len(tab) != 3)
		exit_message(data, "Incorrect 'Sphere' parameters", EXIT_FAILURE);
	sp = new_sphere(data);
	spc = ft_split(data, tab[0], ",");
	if (tab_len(spc) != 3)
		exit_message(data, "Incorrect Sphere center coordinates", EXIT_FAILURE);
	sp->center = dot_3D(ft_atof(spc[0]), ft_atof(spc[1]), ft_atof(spc[2]));
	sp->radius = ft_atof(tab[1]) / 2;
	rgb = ft_split(data, tab[2], ",");
	if (tab_len(rgb) != 3)
		exit_message(data, "Incorrect Sphere color settings", EXIT_FAILURE);
	sp->RGB[0] = ft_atoi(rgb[0]);
	sp->RGB[1] = ft_atoi(rgb[1]);
	sp->RGB[2] = ft_atoi(rgb[2]);
	if (!check_int_color(sp->RGB))
		exit_message(data, "Incorrect Sphere color values", EXIT_FAILURE);
}

void	populate_cyl(t_data *data, char *line)
{
	(void)data;
	(void)line;
}
