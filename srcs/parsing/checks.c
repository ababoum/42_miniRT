/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:17:06 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:31:50 by mababou          ###   ########.fr       */
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

void	check_cam(t_data *data)
{
	if (!data->cam)
		data->cam = malloc_log(data, sizeof(t_camera));
	else
		exit_message(data, "Only one camera is allowed", EXIT_FAILURE);
}

void	check_amb(t_data *data)
{
	if (!data->amb)
		data->amb = malloc_log(data, sizeof(t_ambiance));
	else
		exit_message(data, "Only one ambiance is allowed", EXIT_FAILURE);
}

void	check_lum(t_data *data)
{
	if (!data->lum)
		data->lum = malloc_log(data, sizeof(t_light));
	else
		exit_message(data, "Only one light source is allowed", EXIT_FAILURE);
}
