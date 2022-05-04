/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:32:06 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 21:00:23 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	discriminant_sp(t_ray *ray, t_sphere *sp, t_eq_param *eq_sys)
{
	float	dr[3];

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	eq_sys->a = powf(dr[0], 2) + powf(dr[1], 2) + powf(dr[2], 2);
	eq_sys->b = -2 * (dr[0] * (sp->center.x - ray->origin.x) \
					+ dr[1] * (sp->center.y - ray->origin.y) \
					+ dr[2] * (sp->center.z - ray->origin.z));
	eq_sys->c = powf(sp->center.x - ray->origin.x, 2) \
				+ powf(sp->center.y - ray->origin.y, 2) \
				+ powf(sp->center.z - ray->origin.z, 2) \
				- powf(sp->radius, 2);
	return (powf(eq_sys->b, 2) - 4 * eq_sys->a * eq_sys->c);
}

int	intersection_pt_sp(t_ray *ray, t_sphere *sp, t_3D_point *pt)
{
	t_eq_param	eq_sys;
	float		t[2];

	eq_sys.delta = discriminant_sp(ray, sp, &eq_sys);
	if (eq_sys.delta < 0)
		return (0);
	if (eq_sys.a == 0 && eq_sys.b == 0)
		return (0);
	else if (eq_sys.a == 0)
		t[0] = -eq_sys.c / eq_sys.b;
	else
	{
		t[1] = (-eq_sys.b - sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
		t[0] = (-eq_sys.b + sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
		if (t[0] > t[1] && t[1] > 0)
			t[0] = t[1];
	}
	if (t[0] < 0)
		return (0);
	set_point(pt, ray->origin.x + t[0] * ray->dir.x, \
		ray->origin.y + t[0] * ray->dir.y, ray->origin.z + t[0] * ray->dir.z);
	return (1);
}

// get info about intersection with a given object (sphere here)
void
analyze_ray_for_sphere(t_ray *ray, t_sphere *sp, int *color, float *distance)
{
	t_data *data;
	t_ray norm;
	t_3D_point pt;
	float dist;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_sp(ray, sp, &pt))
	{
		dist = distance_3d(data->cam->pov, pt);
		if (dist > *distance && *distance >= 0)
			return ;
		*distance = dist;
		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(sp->rgb), \
            data->amb->rgb, data->amb->grad);
		// spot
		set_point(&norm.origin, pt.x, pt.y, pt.z);
		set_vector(&norm.dir, pt.x - sp->center.x, \
            pt.y - sp->center.y, \
            pt.z - sp->center.z);
		normalize_v(&norm.dir);
		if ((fmod(get_angle(pt.x - sp->center.x, \
            pt.y - sp->center.y) * DAMIER_FACTOR / M_PI, 1.0) > 0.5)
			^ (fmod(get_angle(sqrtf(powf(pt.x - sp->center.x, 2) +
									powf(pt.y - sp->center.y, 2)), \
            pt.z - sp->center.z) * DAMIER_FACTOR / M_PI, 1.0) > 0.5))
			*color = add_color(*color, \
                        calc_spot(&norm, ray, data->lum, sp->rgb));
		else
			*color = add_color(*color, \
                        calc_spot(&norm, ray, data->lum, sp->rgb2));
	}
}
