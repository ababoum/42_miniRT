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

void get_x_y(int *x, int *y, t_3D_point pt, t_sphere *sp)
{

	float a1 = get_angle(pt.x - sp->center.x, \
            pt.y - sp->center.y);
	float a2 = get_angle(sqrtf(powf(pt.x - sp->center.x, 2) +
							   powf(pt.y - sp->center.y, 2)), \
            pt.z - sp->center.z);

	a2 += M_PI_2;
	a2 = fmod(a2, 2 * M_PI);

	*x = a1 / (M_PI * 2) * TEXTURE_SIZE;
	*y = (a2) / (M_PI) * TEXTURE_SIZE;
	*x = *x;

}

int calc_coord(int x, int y)
{
	x %= TEXTURE_SIZE;
	y %= TEXTURE_SIZE;
	if (x < 0)
		x += 512;
	if (y < 0)
		y += 512;
	return (y * 512 + x);

}

void get_h(int *x, int *y, unsigned char *texture)
{
	int lx;
	int ly;
	int sx;
	int sy;

	lx = *x;
	ly = *y;
	sx = texture[calc_coord(lx - 1, ly + 1)] / 2 +
		 texture[calc_coord(lx - 1, ly)] +
		 texture[calc_coord(lx - 1, ly - 1)] / 2 -
		 texture[calc_coord(lx + 1, ly + 1)] / 2 -
		 texture[calc_coord(lx + 1, ly)] -
		 texture[calc_coord(lx + 1, ly - 1)] / 2;
	sy = texture[calc_coord(lx - 1, ly + 1)] / 2 +
		 texture[calc_coord(lx, ly + 1)] +
		 texture[calc_coord(lx + 1, ly + 1)] / 2 -
		 texture[calc_coord(lx - 1, ly - 1)] / 2 -
		 texture[calc_coord(lx, ly - 1)] -
		 texture[calc_coord(lx + 1, ly - 1)] / 2;
	*x = sx;
	*y = -sy;
}

void get_color_sphere(t_ray *ray, t_sphere *sp, int *color, float *distance)
{
	t_data *data;
	t_ray norm;
	t_3D_point pt;
	int color_obj[3];
	float dist;

	int x;
	int y;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_sp(ray, sp, &pt))
	{
		get_x_y(&x, &y, pt, sp);
		if (!sp->texture || 1)
		{
			if (((DAMIER_FACTOR * x / (512) + DAMIER_FACTOR * y / (512)) % 2))
				rgb_cpy(sp->rgb, color_obj);
			else
				rgb_cpy(sp->rgb2, color_obj);
		} else
		{
			float f = (float) sp->texture[y * 512 + x] / 256.0f;
			color_obj[0] = (int) ((float) sp->rgb[0] * f +
								  (float) sp->rgb2[0] * (1 - f));
			color_obj[1] = (int) ((float) sp->rgb[1] * f +
								  (float) sp->rgb2[1] * (1 - f));
			color_obj[2] = (int) ((float) sp->rgb[2] * f +
								  (float) sp->rgb2[2] * (1 - f));
		}
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

		if (sp->texture)
		{
			get_h(&x, &y, sp->texture);
			float ax = atanf(x) / 40;
			float ay = atanf(y) / 40;
			t_m4 mat;
			set_identity(&mat);
			rotate_x_mat(&mat, ax);
			rotate_z_mat(&mat, ay);
			vec_mult_mat(&norm.dir, mat);
		}

		normalize_v(&norm.dir);


		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, color_obj));

	}
}

void get_color_plan(t_ray *ray, t_plan *pl, int *color, float *distance)
{
	t_data *data;
	t_impact impact;
	t_ray norm;
	float dist;

	int x;
	int y;

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
		set_vector(&norm.dir, pl->normal.x,
				   pl->normal.y,
				   pl->normal.z);

		if (pl->texture)
		{
			x = (int) (impact.tx * 40);
			y = (int) (impact.ty * 40);
			get_h(&x, &y, pl->texture);
			float ax = atanf(x) / 8;
			float ay = atanf(y) / 8;
			t_m4 mat;
			set_identity(&mat);
			rotate_x_mat(&mat, ax);
			rotate_z_mat(&mat, ay);
			vec_mult_mat(&norm.dir, mat);
		}

		normalize_v(&norm.dir);
		*color = add_color(*color,
						   calc_spot(&norm, ray, data->light_lst, impact.rgb));
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

		set_vector(&tmp1, impact.pt.x - cone->center.x, \
            impact.pt.y - cone->center.y, \
            impact.pt.z - cone->center.z);
		set_vector(&tmp2, -v * cone->dir.x, \
            -v * cone->dir.y, \
            -v * cone->dir.z);
		if (vec_dot(tmp1, tmp2) < 0)
			v *= -1;

		set_vector(&norm.dir, cone->center.x - v * cone->dir.x, \
            cone->center.y - v * cone->dir.y, \
            cone->center.z - v * cone->dir.z);

		norm.dir.x = impact.pt.x - norm.dir.x;
		norm.dir.y = impact.pt.y - norm.dir.y;
		norm.dir.z = impact.pt.z - norm.dir.z;

		normalize_v(&norm.dir);
		*color = add_color(*color, \
                        calc_spot(&norm, ray, data->light_lst, impact.rgb));
		// spot ?
	}
}
