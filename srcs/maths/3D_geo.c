/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:29:05 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:04:08 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/ft3d.h"

t_3D_point	*dot_3d(float x, float y, float z)
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

int	check_dir_vector(t_3D_point *vector)
{
	if (vector->x < -1 || vector->x > 1 || \
		vector->y < -1 || vector->y > 1 || \
		vector->z < -1 || vector->z > 1)
		return (0);
	return (1);
}

t_vec	*vector(t_3D_point *p0, t_3D_point *p1)
{
	t_vec	*vec;
	t_data	*data;

	data = get_data(0, 0);
	vec = malloc_log(data, sizeof(t_vec));
	vec->x = p1->x - p0->x;
	vec->y = p1->y - p0->y;
	vec->z = p1->z - p0->z;
	return (vec);
}

void 	pt3d_mult_mat(t_3D_point *pt, t_m4 mat)
{
	float x;
	float y;
	float z;

	x = pt->x;
	y = pt->y;
	z = pt->z;

	pt->x = mat[0] * x + mat[1] * y + mat[2] * z + mat[3];
	pt->y = mat[4] * x + mat[5] * y + mat[6] * z + mat[7];
	pt->z = mat[8] * x + mat[9] * y + mat[10] * z + mat[11];
}

void	ray_mult_mat(t_ray *ray, t_m4 mat)
{
	//transform direction to looking at
	ray->dir->x += ray->origin->x;
	ray->dir->y += ray->origin->y;
	ray->dir->z += ray->origin->z;

	pt3d_mult_mat(ray->dir, mat);
	pt3d_mult_mat(ray->origin, mat);

	ray->dir->x -= ray->origin->x;
	ray->dir->y -= ray->origin->y;
	ray->dir->z -= ray->origin->z;
}
