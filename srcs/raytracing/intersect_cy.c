/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:23:31 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 12:11:50 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	discriminant_cy(t_ray *ray, t_cyl *cy, t_eq_param *eq_sys)
{
	float	dr[3];

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	eq_sys->a = powf(dr[0], 2) + powf(dr[1], 2);
	eq_sys->b = ray->origin.y * powf(dr[0], 2) + \
				ray->origin.x * powf(dr[1], 2) + \
				2 * ray->origin.x * powf(dr[0], 2) + \
				2 * ray->origin.y * powf(dr[1], 2);
	eq_sys->c = powf(ray->origin.x, 2) + powf(ray->origin.y, 2) - \
				powf(cy->radius, 2);
	return (powf(eq_sys->b, 2) - 4 * eq_sys->a * eq_sys->c);
}

static void	prepare_ray_for_cy(t_ray *ray, t_cyl *cy)
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

static int	intersection_cy_caps(t_ray *ray, t_cyl *cy, t_3D_point *pt)
{
	float	t_top;
	float	t_bot;
	float	t_;

	t_top = ((cy->height / 2) - ray->origin.z) / ray->dir.z;
	t_bot = ((-cy->height / 2) - ray->origin.z) / ray->dir.z;
	if (powf(ray->origin.x + t_top * ray->dir.x, 2) + \
		powf(ray->origin.y + t_top * ray->dir.y, 2) <= powf(cy->radius, 2) && \
		powf(ray->origin.x + t_bot * ray->dir.x, 2) + \
		powf(ray->origin.y + t_bot * ray->dir.y, 2) <= powf(cy->radius, 2))
	{
		if (t_top * t_bot < 0)
			t_ = max(t_top, t_bot);
		else if (t_top < 0)
			return (0);
		else
			t_ = min(t_top, t_bot);
	}
	else if (powf(ray->origin.x + t_bot * ray->dir.x, 2) + \
		powf(ray->origin.y + t_bot * ray->dir.y, 2) <= powf(cy->radius, 2))
	{
		set_point(pt, ray->origin.x + t_bot * ray->dir.x, \
		ray->origin.y + t_bot * ray->dir.y, ray->origin.z + t_bot * ray->dir.z);
		return (1);
	}
	else
		return (0);
}

static int	dbl_intersection_pt_cy(t_ray *ray, t_cyl *cy, t_3D_point *pt, \
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
	if (is_between(ray->origin.z + ray->dir.z * t_, \
						-cy->height / 2, cy->height / 2))
	{
		set_point(pt, ray->origin.x + t_ * ray->dir.x, \
		ray->origin.y + t_ * ray->dir.y, ray->origin.z + t_ * ray->dir.z);
		return (1);
	}
	t_ = switch_val(t_, t[0], t[1]);
	if (is_between(ray->origin.z + ray->dir.z * t_, \
						-cy->height / 2, cy->height / 2))
		return (intersection_cy_caps(ray, cy, pt));
	return (0);
}

int	intersection_pt_cy(t_ray *ray, t_cyl *cy, t_3D_point *pt)
{
	t_eq_param	eq_sys;
	float		t[2];

	prepare_ray_for_cy(ray, cy);
	eq_sys.delta = discriminant_cy(ray, cy, &eq_sys);
	if (eq_sys.delta < 0)
		return (intersection_cy_caps(ray, cy, pt));
	else if (eq_sys.delta == 0)
	{
		t[0] = -eq_sys.b / (2 * eq_sys.a);
		if (ffabs(ray->origin.z + ray->dir.z * t[0]) > cy->height / 2)
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
