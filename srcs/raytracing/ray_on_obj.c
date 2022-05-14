/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_on_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:47:25 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 15:24:13 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// get info about intersection with a given object

void
get_color_sphere(t_ray *ray, t_sphere *sp, int *color, float *distance)
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
                        calc_spot(&norm, ray, data->light_lst, sp->rgb));
		else
			*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, sp->rgb2));
	}
}

void	get_color_plan(t_ray *ray, t_plan *pl, int *color, float *distance)
{
	t_data		*data;
	t_3D_point	pt;
	float		dist;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_pl(ray, pl, &pt))
	{
		// TODO calc distance, backup nearest color, 
		// if distance smaller replace color

		dist = distance_3d(data->cam->pov, pt);
		if (dist > *distance && *distance >= 0)
			return ;
		*distance = dist;
		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(pl->rgb), \
			data->amb->rgb, data->amb->grad);
		// spot ?
	}
}

void	get_color_cyl(t_ray *ray, t_cyl *cy, int *color, float *distance)
{
	t_data		*data;
	t_3D_point	pt;
	t_ray norm;

	float v;
	float		dist;

	data = get_data(0, 0);
	if (intersection_pt_cy(ray, cy, &pt))
	{
		dist = distance_3d(data->cam->pov, pt);
		if (dist > *distance && *distance >= 0)
			return ;
		*distance = dist;
		*color = rgb_ambiant(arr_to_rgb(cy->rgb), \
			data->amb->rgb, data->amb->grad);

		set_point(&norm.origin, pt.x, pt.y, pt.z);
		set_vector(&norm.dir, pt.x - cy->point.x, \
            pt.y - cy->point.y, \
            pt.z - cy->point.z);
	    v = vec_dot(cy->dir, norm.dir);
		norm.dir.x -= v * cy->dir.x;
		norm.dir.y -= v * cy->dir.y;
		norm.dir.z -= v * cy->dir.z;

		normalize_v(&norm.dir);
		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, cy->rgb));
		// spot ?
	}
}
