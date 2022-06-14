/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:17:06 by mababou           #+#    #+#             */
/*   Updated: 2022/06/14 12:13:52 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
		if (data->light_lst && !data->bonus)
			exit_message(data, "One light source allowed", EXIT_FAILURE);
	}
}

int	check_line_args_2(char *type, int argc)
{
	t_data	*data;

	data = get_data(0, 0);
	if (!ft_strcmp(type, "Ambiance"))
		return (argc != 2);
	if (!ft_strcmp(type, "Cylinder"))
		return (!(argc == 5 || (data->bonus && argc == 6) || \
				(data->bonus && argc == 7)));
	if ((!ft_strcmp(type, "Sphere")))
		return (!(argc == 3 || (data->bonus && argc == 4) || \
		(data->bonus && argc == 5)));
	if ((!ft_strcmp(type, "Plan")))
		return (!(argc == 3 || (data->bonus && argc == 4) || \
		(data->bonus && argc == 5)));
	return (argc != 3);
}

void	check_line_args(t_data *data, char *type, int argc)
{
	if (check_line_args_2(type, argc))
	{
		if (!ft_strcmp(type, "Ambiance"))
			exit_message(data, "Ambiance: Incorrect number of parameters", 1);
		if (!ft_strcmp(type, "Cylinder"))
			exit_message(data, "Cylinder: Incorrect number of parameters", 1);
		if (!ft_strcmp(type, "Sphere"))
			exit_message(data, "Sphere: Incorrect number of parameters", 1);
		if (!ft_strcmp(type, "Plan"))
			exit_message(data, "Plan: Incorrect number of parameters", 1);
	}
}

void	check_arg(t_data *data, char **arg, int argc, char *msg_if_fail)
{
	if (tab_len(arg) != argc)
		exit_message(data, msg_if_fail, EXIT_FAILURE);
}
