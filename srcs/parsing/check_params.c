/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:34:17 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 16:34:34 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	check_dir_vector(t_vec vector)
{
	if (vector.x < -1 || vector.x > 1 || \
		vector.y < -1 || vector.y > 1 || \
		vector.z < -1 || vector.z > 1)
		return (0);
	return (1);
}

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
