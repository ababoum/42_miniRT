/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:23:31 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 17:48:46 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	discriminant_cy(t_ray *ray, t_cylinder *cy, t_eq_param *eq_sys)
{
	float	dr[3];

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	disc[0] = powf(dr[0], 2) + powf(dr[1], 2);
	disc[1] = ray->origin.y * powf(dr[0], 2) + \
				ray->origin.x * powf(dr[1], 2) + \
				2 * ray->origin.x * powf(dr[0], 2) + \
				2 * ray->origin.y * powf(dr[1], 2));
	disc[2] = powf(ray->origin.x, 2) + powf(ray->origin.y, 2) - \
				powf(cy->radius, 2);
	return (powf(disc[1], 2) - 4 * disc[0] * disc[2]);
}

static void	prepare_ray_for_cy(t_ray *ray, t_cylinder *cy)
{
	t_m4	mat;
	float	rot_angles[2];

	set_identity(&mat);
	translate_mat(&mat, -cy->point.x, -cy->point.y, -cy->point.z);
	rot_angles[0] = get_angle(cy->dir.x, cy->dir.y);
	rot_angles[1] = get_angle(sqrtf(cy->dir.x * cy->dir.x + \
						cy->dir.y * cy->dir.y), \
						cy->dir.z);
	rotate_y_mat(&mat, rot_angles[0]);
	rotate_x_mat(&mat, rot_angles[1]);
	ray_mult_mat(ray, mat);
}

static int	dbl_intersection_pt_cy(t_ray *ray, t_cylinder *cy, t_3D_point *pt, \
	t_eq_param eq_sys)
{
	float	t[2];

	t[0] = (-eq_sys.b + sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	t[1] = (-eq_sys.b - sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	if (t[0] < 0 && t[1] < 0)
		return (0);
	
}

int	intersection_pt_cy(t_ray *ray, t_cylinder *cy, t_3D_point *pt)
{
	t_eq_param	eq_sys;
	float		d;
	float		t[2];

	prepare_ray_for_cy(ray, cy);
	eq_sys.delta = discriminant_cy(ray, cy, &eq_sys);
	if (d < 0)
		return (0);
	else if (d == 0)
	{
		t[0] = -eq_sys.b / (2 * eq_sys.a);
		if (ray->origin.z + ray->dir.z * t[0] > cy->height / 2 || \
			ray->origin.z + ray->dir.z * t[0] < cy->height / 2)
			return (0);
		else if (t[0] < 0)
			return (0);
		else
		{
			set_point(pt, ray->origin.x + t[0] * ray->dir.x, \
		ray->origin.y + t[0] * ray->dir.y, ray->origin.z + t[0] * ray->dir.z);
			return (1);
		}
	}
	else
		return (dbl_intersection_pt_cy(ray, cy, pt, eq_sys));
}
