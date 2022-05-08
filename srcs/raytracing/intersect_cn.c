/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:33:10 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 16:04:43 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	discriminant_cn(t_ray *ray, t_cone *cn, t_eq_param *eq_sys)
{
	float	dr[3];
	float	tan_alph;

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	tan_alph = tanf(deg_to_rad(cn->angle));
	eq_sys->a = powf(dr[0], 2) + powf(dr[1], 2) - \
		powf(dr[2] * tan_alph, 2);
	eq_sys->b = 2 * (ray->origin.x * dr[0] + \
		ray->origin.y * dr[1] - \
		tan_alph * ray->origin.z * dr[2]);
	eq_sys->c = powf(ray->origin.x, 2) + \
		powf(ray->origin.y, 2) + \
		powf(ray->origin.z * tan_alph, 2);
	return (powf(eq_sys->b, 2) - 4 * eq_sys->a * eq_sys->c);
}

// We need cn->dir to be aligned with (OY)
static void	prepare_ray_for_cn(t_ray *ray, t_cone *cn)
{
	t_m4	mat;
	float	rot_angles[2];

	set_identity(&mat);
	translate_mat(&mat, -cn->center.x, -cn->center.y, -cn->center.z);
	rot_angles[0] = get_angle(cn->dir.x, cn->dir.y);
	rot_angles[1] = get_angle(sqrtf(cn->dir.x * cn->dir.x + \
						cn->dir.y * cn->dir.y), \
						cn->dir.z);
	rotate_y_mat(&mat, rot_angles[0]);
	rotate_x_mat(&mat, rot_angles[1]);
	ray_mult_mat(ray, mat);
}

static int	dbl_intersection_pt_cn(t_ray *ray, t_cone *cn, t_3D_point *pt, \
	t_eq_param eq_sys)
{
	float	t[2];
	float	t_;

	t[0] = (-eq_sys.b + sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	t[1] = (-eq_sys.b - sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	if (t[0] < 0 && t[1] < 0)
		return (0);
	else if ((t[0] < 0 && t[1] >= 0) || (t[1] < 0 && t[0] >= 0))
		t_ = max(t[0], t[1]);
	else
		t_ = min(t[0], t[1]);
	set_point(pt, ray->origin.x + t_ * ray->dir.x, \
		ray->origin.y + t_ * ray->dir.y, ray->origin.z + t_ * ray->dir.z);
	return (1);
}

int	intersection_pt_cn(t_ray *ray, t_cone *cn, t_3D_point *pt)
{
	t_eq_param	eq_sys;
	float		t[2];

	prepare_ray_for_cn(ray, cn);
	eq_sys.delta = discriminant_cn(ray, cn, &eq_sys);
	if (eq_sys.delta < 0)
		return (0);
	else if (eq_sys.delta == 0)
	{
		t[0] = -eq_sys.b / (2 * eq_sys.a);
		if (t[0] < 0)
			return (0);
		else
		{
			set_point(pt, ray->origin.x + t[0] * ray->dir.x, \
		ray->origin.y + t[0] * ray->dir.y, ray->origin.z + t[0] * ray->dir.z);
			return (1);
		}
	}
	else
		return (dbl_intersection_pt_cn(ray, cn, pt, eq_sys));
}
