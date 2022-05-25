/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:29:05 by mababou           #+#    #+#             */
/*   Updated: 2022/05/25 19:02:11 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/ft3d.h"

void	pt3d_mult_mat(t_3D_point *pt, t_m4 mat)
{
	float	x;
	float	y;
	float	z;

	x = pt->x;
	y = pt->y;
	z = pt->z;
	pt->x = mat[0] * x + mat[1] * y + mat[2] * z + mat[3];
	pt->y = mat[4] * x + mat[5] * y + mat[6] * z + mat[7];
	pt->z = mat[8] * x + mat[9] * y + mat[10] * z + mat[11];
}

void	vec_mult_mat(t_vec *vec, t_m4 mat)
{
	float	x;
	float	y;
	float	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	vec->x = mat[0] * x + mat[1] * y + mat[2] * z + mat[3];
	vec->y = mat[4] * x + mat[5] * y + mat[6] * z + mat[7];
	vec->z = mat[8] * x + mat[9] * y + mat[10] * z + mat[11];
	(void)x;
}

//transform direction to looking at
void	ray_mult_mat(t_ray *ray, t_m4 mat)
{
	ray->dir.x += ray->origin.x;
	ray->dir.y += ray->origin.y;
	ray->dir.z += ray->origin.z;
	pt3d_mult_mat((t_3D_point *)(&ray->dir), mat);
	pt3d_mult_mat(&ray->origin, mat);
	ray->dir.x -= ray->origin.x;
	ray->dir.y -= ray->origin.y;
	ray->dir.z -= ray->origin.z;
}
