/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:17:06 by mababou           #+#    #+#             */
/*   Updated: 2022/04/27 19:39:43 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	verify_file(t_data *data, const char *path)
{
	int	fd;

	if (ft_strlen(path) < 3 || ft_strcmp(path + ft_strlen(path) - 3, ".rt"))
	{
		ft_putstr_fd("Incorrect filename (extension should be .rt)\n", 2);
		clear_exit(data, 1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		clear_exit(data, 1);
	}
	return (fd);
}

void	check_scene_setting(t_data *data, int setting_type)
{
	if (setting_type == CAMERA)
	{
		if (!data->cam)
			data->cam = malloc_log(data, sizeof(t_camera));
		else
			exit_message(data, "Only one camera is allowed", EXIT_FAILURE);
	}
	else if (setting_type == AMBIANCE)
	{
		if (!data->amb)
			data->amb = malloc_log(data, sizeof(t_ambiance));
		else
			exit_message(data, "Only one ambiance is allowed", EXIT_FAILURE);
	}
	else if (setting_type == LIGHT)
	{
		if (!data->lum)
			data->lum = malloc_log(data, sizeof(t_light));
		else
			exit_message(data, "Only one light source is allowed", \
				EXIT_FAILURE);
	}
}

void	check_line_args(t_data *data, char *type, int argc)
{
	if (!ft_strcmp(type, "Ambiance") && argc != 2)
	{
		ft_putstr_fd("Ambiance: ", 2);
		exit_message(data, "Incorrect number of parameters", EXIT_FAILURE);
	}
	else if (!ft_strcmp(type, "Cylinder") && argc != 5)
	{
		ft_putstr_fd("Cylinder: ", 2);
		exit_message(data, "Incorrect number of parameters", EXIT_FAILURE);
	}
	else if (ft_strcmp(type, "Ambiance") && ft_strcmp(type, "Cylinder") && \
		argc != 3)
	{
		ft_putstr_fd(type, 2);
		ft_putstr_fd(": ", 2);
		exit_message(data, "Incorrect number of parameters", EXIT_FAILURE);
	}
}

void	check_arg(t_data *data, char **arg, int argc, char *msg_if_fail)
{
	if (tab_len(arg) != argc)
		exit_message(data, msg_if_fail, EXIT_FAILURE);
}

// to delete once everything is vector or point
int	check_dir_vector_p(t_3D_point *point)
{
	if (point->x < -1 || point->x > 1 || \
		point->y < -1 || point->y > 1 || \
		point->z < -1 || point->z > 1)
		return (0);
	return (1);
}

int	check_dir_vector(t_vec *vector)
{
	if (vector->x < -1 || vector->x > 1 || \
		vector->y < -1 || vector->y > 1 || \
		vector->z < -1 || vector->z > 1)
		return (0);
	return (1);
}

