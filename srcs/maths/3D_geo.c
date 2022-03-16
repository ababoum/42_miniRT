/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:29:05 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 16:46:54 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_3D_point	dot_3D(float x, float y, float z)
{
	t_3D_point	point = {x, y, z};

	return (point);
}

int	check_dir_vector(t_3D_point vector)
{
	if (vector.x < -1 || vector.x > 1 || \
		vector.y < -1 || vector.y > 1 || \
		vector.z < -1 || vector.z > 1)
		return (0);
	return (1);
}
