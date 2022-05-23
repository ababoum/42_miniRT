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

void get_color_sphere(t_ray *ray, t_sphere *sp, int *color, float *distance)
{
	t_data *data;
	t_ray norm;
	t_3D_point pt;
	int *color_obj;
	float dist;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_sp(ray, sp, &pt))
	{
		if ((fmod(get_angle(pt.x - sp->center.x, \
            pt.y - sp->center.y) * DAMIER_FACTOR / M_PI, 1.0) > 0.5)
			^ (fmod(get_angle(sqrtf(powf(pt.x - sp->center.x, 2) +
									powf(pt.y - sp->center.y, 2)), \
            pt.z - sp->center.z) * DAMIER_FACTOR / M_PI, 1.0) > 0.5))
			color_obj = sp->rgb;
		else
			color_obj = sp->rgb2;
		dist = distance_3d(data->cam->pov, pt);
		if (dist > *distance && *distance >= 0)
			return;
		*distance = dist;
		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(color_obj), \
            data->amb->rgb, data->amb->grad);
		// spot
		set_point(&norm.origin, pt.x, pt.y, pt.z);
		set_vector(&norm.dir, pt.x - sp->center.x, \
            pt.y - sp->center.y, \
            pt.z - sp->center.z);
		normalize_v(&norm.dir);

		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, color_obj));
		*color = add_color(*color, \
                        calc_phong(&norm, ray, data->light_lst));
	}
}

void get_color_plan(t_ray *ray, t_plan *pl, int *color, float *distance)
{
	t_data *data;
	t_impact impact;
	t_ray norm;
	float dist;

	set_point(&(impact.pt), 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_impact_pl(ray, pl, &impact))
	{
		// TODO calc distance, backup nearest color, 
		// if distance smaller replace color

		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return;
		*distance = dist;
		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
            data->amb->rgb, data->amb->grad);
		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		set_vector(&norm.dir, -pl->normal.x,
				   -pl->normal.y,
				   -pl->normal.z);
		normalize_v(&norm.dir);
		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, impact.rgb));
		*color = add_color(*color, \
                        calc_phong(&norm, ray, data->light_lst));
	}
}

void get_color_cyl(t_ray *ray, t_cyl *cy, int *color, float *distance)
{
	t_data *data;
	t_impact impact;
	t_ray norm;

	float v;
	float dist;
	int ret;

	data = get_data(0, 0);
	ret = intersection_impact_cy(ray, cy, &impact);
	if (ret)
	{
		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return;
		*distance = dist;
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
            data->amb->rgb, data->amb->grad);

		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		set_vector(&norm.dir, impact.pt.x - cy->point.x, \
            impact.pt.y - cy->point.y, \
            impact.pt.z - cy->point.z);

		if (ret == 2)
		{
			v = vec_dot(cy->dir, norm.dir);
			if (v > 0)
			{
				norm.dir.x = cy->dir.x;
				norm.dir.y = cy->dir.y;
				norm.dir.z = cy->dir.z;
			} else
			{
				norm.dir.x = -cy->dir.x;
				norm.dir.y = -cy->dir.y;
				norm.dir.z = -cy->dir.z;
			}
		} else
		{
			v = vec_dot(cy->dir, norm.dir);
			norm.dir.x -= v * cy->dir.x;
			norm.dir.y -= v * cy->dir.y;
			norm.dir.z -= v * cy->dir.z;
		}
		normalize_v(&norm.dir);
		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, impact.rgb));
		*color = add_color(*color, \
                        calc_phong(&norm, ray, data->light_lst));

	}
}


void get_color_cone(t_ray *ray, t_cone *cone, int *color, float *distance)
{
	t_data *data;
	t_impact impact;
	t_ray norm;
	t_vec tmp1;
	t_vec tmp2;

	float v;
	float dist;
	int ret;

	data = get_data(0, 0);
	ret = intersection_impact_cone(ray, cone, &impact);
	if (ret)
	{
		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return;
		*distance = dist;
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
            data->amb->rgb, data->amb->grad);

		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		v = distance_3d(impact.pt, cone->center);

		set_vector(&tmp1, impact.pt.x -  cone->center.x, \
            impact.pt.y -  cone->center.y, \
            impact.pt.z -  cone->center.z);
		set_vector(&tmp2, - v * cone->dir.x, \
            - v * cone->dir.y, \
            - v * cone->dir.z);
		if(vec_dot(tmp1, tmp2) < 0)
			v *=-1;

		set_vector(&norm.dir, cone->center.x - v * cone->dir.x, \
            cone->center.y - v * cone->dir.y, \
            cone->center.z - v * cone->dir.z);

		norm.dir.x = impact.pt.x - norm.dir.x;
		norm.dir.y = impact.pt.y - norm.dir.y;
		norm.dir.z = impact.pt.z - norm.dir.z;

		normalize_v(&norm.dir);
		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, impact.rgb));

		*color = add_color(*color, \
                        calc_phong(&norm, ray, data->light_lst));
		// spot ?
	}
}