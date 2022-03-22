/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:29:05 by mababou           #+#    #+#             */
/*   Updated: 2022/03/22 15:08:12 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_3D_point	dot_3d(float x, float y, float z)
{
	t_3D_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
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

t_vec	vector(t_3D_point p0, t_3D_point p1)
{
	t_vec	vec;

	vec.x = p1.x - p0.x;
	vec.y = p1.y - p0.y;
	vec.z = p1.z - p0.z;
	return (vec);
}
