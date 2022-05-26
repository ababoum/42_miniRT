/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:17:06 by mababou           #+#    #+#             */
/*   Updated: 2022/05/18 13:55:58 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	verify_file(t_data *data, const char *path)
{
	int	fd;

	if (ft_strlen(path) < 3 || ft_strcmp(path + ft_strlen(path) - 3, ".rt"))
	{
		exit_message(data, "Incorrect filename (extension should be .rt)\n", \
			EXIT_FAILURE);
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
		if (data->light_lst && !BONUS_ON)
			exit_message(data, "One light source allowed", EXIT_FAILURE);
	}
}

int	check_line_args_2(char *type, int argc)
{
	if (!ft_strcmp(type, "Ambiance"))
		return (argc != 2);
	if (!ft_strcmp(type, "Cylinder"))
		return (!(argc == 5 || (BONUS_ON && argc == 6)));
	if ((!ft_strcmp(type, "Sphere")))
		return (!(argc == 3 || (BONUS_ON && argc == 4)|| (BONUS_ON && argc == 5)));
	if ((!ft_strcmp(type, "Plan")))
		return (!(argc == 3 || (BONUS_ON && argc == 4) || (BONUS_ON && argc == 5) ));
	return (argc != 3);
}

void 	check_line_args(t_data *data, char *type, int argc)
{
	if (check_line_args_2(type, argc))
	{
		ft_putstr_fd(type, 2);
		exit_message(data, ": Incorrect number of parameters", EXIT_FAILURE);
	}
}

void	check_arg(t_data *data, char **arg, int argc, char *msg_if_fail)
{
	if (tab_len(arg) != argc)
		exit_message(data, msg_if_fail, EXIT_FAILURE);
}

int	check_dir_vector(t_vec vector)
{
	if (vector.x < -1 || vector.x > 1 || \
		vector.y < -1 || vector.y > 1 || \
		vector.z < -1 || vector.z > 1)
		return (0);
	return (1);
}
