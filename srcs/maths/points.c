/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:58:18 by mababou           #+#    #+#             */
/*   Updated: 2022/05/25 18:58:46 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_3D_point	*new_point(float x, float y, float z)
{
	t_3D_point	*point;
	t_data		*data;

	data = get_data(0, 0);
	point = malloc_log(data, sizeof(t_3D_point));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

t_3D_point	point(float x, float y, float z)
{
	t_3D_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

void	set_point(t_3D_point *pt, float x, float y, float z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}
