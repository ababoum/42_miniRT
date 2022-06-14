/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:53:44 by mababou           #+#    #+#             */
/*   Updated: 2022/06/14 12:18:12 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	get_x_y(int *x, int *y, t_3D_point pt, t_sphere *sp)
{
	float	a1;
	float	a2;

	a1 = get_angle(pt.x - sp->center.x, pt.y - sp->center.y);
	a2 = get_angle(sqrtf(powf(pt.x - sp->center.x, 2) + \
		powf(pt.y - sp->center.y, 2)), pt.z - sp->center.z);
	a2 += M_PI_2;
	a2 = fmod(a2, 2 * M_PI);
	*x = a1 / (M_PI * 2) * TEXTURE_SIZE;
	*y = (a2) / (M_PI) * TEXTURE_SIZE;
	*x = *x;
}

static void	sphere_texture(int *x, int *y, t_sphere *sp, t_vec *norm_dir)
{
	float	ax;
	float	ay;
	t_m4	mat;

	get_h(x, y, sp->texture);
	ax = atanf(*x) / 10;
	ay = atanf(*y) / 10;
	set_identity(&mat);
	rotate_x_mat(&mat, ax);
	rotate_z_mat(&mat, ay);
	vec_mult_mat(norm_dir, mat);
}

static void	prepare_sphere_spot(t_sphere *sp,
		t_3D_point *pt, t_ray *norm, int *x_y)
{
	set_point(&norm->origin, pt->x, pt->y, pt->z);
	set_vector(&norm->dir, pt->x - sp->center.x, \
		pt->y - sp->center.y, \
		pt->z - sp->center.z);
	if (sp->texture)
		sphere_texture(&x_y[0], &x_y[1], sp, &norm->dir);
	normalize_v(&norm->dir);
}

static void	chess_or_texture(t_sphere *sp, int *x_y, int *color_obj)
{
	if (\
		((DAMIER_FACTOR * x_y[0] / (512) + DAMIER_FACTOR * x_y[1] / (512)) % 2))
		rgb_cpy(sp->rgb, color_obj);
	else
		rgb_cpy(sp->rgb2, color_obj);
}

void	get_color_sphere(t_ray *ray, t_sphere *sp, int *color, float *distance)
{
	t_data		*data;
	t_ray		norm;
	t_3D_point	pt;
	int			color_obj[3];
	int			x_y[2];

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_sp(ray, sp, &pt))
	{
		get_x_y(&x_y[0], &x_y[1], pt, sp);
		chess_or_texture(sp, x_y, color_obj);
		if (distance_3d(data->cam->pov, pt) > *distance && *distance >= 0)
			return ;
		*distance = distance_3d(data->cam->pov, pt);
		*color = rgb_ambiant(arr_to_rgb(color_obj), \
			data->amb->rgb, data->amb->grad);
		prepare_sphere_spot(sp, &pt, &norm, x_y);
		*color = add_color(*color, \
			calc_spot(&norm, ray, data->light_lst, color_obj));
	}
}
