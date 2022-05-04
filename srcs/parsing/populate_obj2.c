/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:00:25 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 14:44:48 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	obj->rgb[0] = ft_atoi(arg[0]);
	obj->rgb[1] = ft_atoi(arg[1]);
	obj->rgb[2] = ft_atoi(arg[2]);
	if (!check_int_color(obj->rgb))
		exit_message(data, "Incorrect Plan color values", EXIT_FAILURE);
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
	obj->rgb[0] = ft_atoi(arg[0]);
	obj->rgb[1] = ft_atoi(arg[1]);
	obj->rgb[2] = ft_atoi(arg[2]);
	if (!check_int_color(obj->rgb))
		exit_message(data, "Incorrect Sphere color values", EXIT_FAILURE);
}

void	populate_cyl(t_data *data, char *line)
{
	char		**tab;
	char		**arg;
	t_cylinder	*obj;

	tab = ft_split(data, line, SPACES);
	check_line_args(data, "Cylinder", tab_len(tab));
	obj = new_cylinder(data);
	arg = ft_split(data, tab[0], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder point coordinates");
	obj->point = point(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	arg = ft_split(data, tab[1], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder direction coordinates");
	obj->dir = vector_f(ft_atof(arg[0]), ft_atof(arg[1]), ft_atof(arg[2]));
	if (!check_dir_vector(obj->dir))
		exit_message(data, "Incorrect Cylinder direction values", EXIT_FAILURE);
	obj->radius = ft_atof(tab[2]) / 2;
	obj->height = ft_atof(tab[3]);
	arg = ft_split(data, tab[4], ",");
	check_arg(data, arg, 3, "Incorrect Cylinder color settings");
	obj->rgb[0] = ft_atoi(arg[0]);
	obj->rgb[1] = ft_atoi(arg[1]);
	obj->rgb[2] = ft_atoi(arg[2]);
	if (!check_int_color(obj->rgb))
		exit_message(data, "Incorrect Cylinder color values", EXIT_FAILURE);
}
