/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:32:06 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 15:06:41 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// check if a ray intersects with a sphere
static float	discriminant_sp(t_ray *ray, t_sphere *sp, float disc[3])
{
	float	dr[3];

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	disc[0] = powf(dr[0], 2) + powf(dr[1], 2) + powf(dr[2], 2);

	disc[1] = -2 * (dr[0] * (sp->center.x - ray->origin.x) \
					+ dr[1] * (sp->center.y - ray->origin.y) \
					+ dr[2] * (sp->center.z - ray->origin.z) \
	);

	disc[2] = powf(sp->center.x - ray->origin.x, 2) \
				+ powf(sp->center.y - ray->origin.y, 2) \
				+ powf(sp->center.z - ray->origin.z, 2) \
				- powf(sp->radius, 2);

	return (powf(disc[1], 2) - 4 * disc[0] * disc[2]);
}

static int	intersection_pt_sp(t_ray *ray, t_sphere *sp, t_3D_point *pt)
{
	float	disc[3];
	float	d;
	float	x;
	float	x2;

	d = discriminant_sp(ray, sp, disc);
	if (d < 0)
		return (0);
	if (disc[0] == 0 && disc[1] == 0)
		return (0);
	else if (disc[0] == 0)
		x = -disc[2] / disc[1];
	else
	{
		x2 = (-disc[1] - sqrtf(d)) / (2 * disc[0]);
		x = (-disc[1] + sqrtf(d)) / (2 * disc[0]);
		if (x > x2 && x2 > 0)
			x = x2;
	}
	if (x < 0)
		return (0);
	set_point(pt, ray->origin.x + x * ray->dir.x, \
		ray->origin.y + x * ray->dir.y, ray->origin.z + x * ray->dir.z);
	return (1);
}

//For optimization res is in arg, it must have size >= 3
void	projection_pt_droite(t_ray *ray, t_3D_point *pt, t_3D_point *res)
{
	float	k;

	k = ray->dir.x * (pt->x - ray->origin.x) \
		+ ray->dir.y * (pt->y - ray->origin.y) \
		+ ray->dir.z * (pt->z - ray->origin.z);
	res->x = ray->origin.x + k * ray->dir.x;
	res->y = ray->origin.y + k * ray->dir.y;
	res->z = ray->origin.z + k * ray->dir.z;
}

// get info about intersection with a given object (sphere here)
void	analyze_ray_for_sphere(t_ray *ray, t_sphere *sp, int *color)
{
	t_data		*data;
	t_ray		norm;
	t_3D_point	pt;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_sp(ray, sp, &pt))
	{
		// TODO calc distance, backup nearest color, 
		// if distance smaller replace color

		//Ambiant light
		*color = rgb_ambiant(arr_to_rgb(sp->rgb), \
			data->amb->rgb, data->amb->grad);
		//spot
		set_point(&norm.origin, pt.x, pt.y, pt.z);
		set_vector(&norm.dir, pt.x - sp->center.x, \
			pt.y - sp->center.y, \
			pt.z - sp->center.z);
		normalize_v(&norm.dir);
		*color = add_color(*color, \
						calc_spot(&norm, ray, data->lum, sp->rgb));

	}
}
