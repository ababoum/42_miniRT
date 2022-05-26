/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:23:31 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 16:03:25 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void discriminant_cone_2(t_ray *ray, t_cone *cone, t_eq_param *eq_sys)
{
	float dr[3];
	float ang = tan(cone->angle / 180.0 * M_PI);
	ang *= ang;
	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	eq_sys->a = powf(dr[0], 2) + powf(dr[2], 2) - powf(dr[1], 2) * ang;
	eq_sys->b = 2 * ray->origin.x * dr[0] +
				2 * ray->origin.z * dr[2] -
				2 * ray->origin.y * dr[1] * ang;
	eq_sys->c = powf(ray->origin.x, 2) + powf(ray->origin.z, 2) - \
                powf(ray->origin.y, 2) * ang;

	(*eq_sys).delta = (powf(eq_sys->b, 2) - 4 * eq_sys->a * eq_sys->c);
}


// I need cone->dir to be aligned with (OY)
static void prepare_ray_for_cone(t_ray *ray, t_cone *cone)
{
	t_m4 mat;
	float rot_angles[2];

	set_identity(&mat);

	rot_angles[0] = get_angle(cone->dir.x, cone->dir.y) + M_PI_2;
	rot_angles[1] = get_angle(sqrtf(cone->dir.x * cone->dir.x + \
                        cone->dir.y * cone->dir.y), \
                        cone->dir.z);
//	rotate_z_mat(&mat, M_PI);
	rotate_x_mat(&mat, rot_angles[1]);
	rotate_z_mat(&mat, -rot_angles[0]);
	translate_mat(&mat, -cone->center.x, -cone->center.y, -cone->center.z);
	ray_mult_mat(ray, mat);
}

void reverse_op_cone(t_cone *cone, t_3D_point *pt)
{
	t_m4 mat;
	float rot_angles[2];

	set_identity(&mat);

	rot_angles[0] = get_angle(cone->dir.x, cone->dir.y) + M_PI_2;
	rot_angles[1] = get_angle(sqrtf(cone->dir.x * cone->dir.x + \
                        cone->dir.y * cone->dir.y), \
                        cone->dir.z);
//	rotate_z_mat(&mat, M_PI);
	translate_mat(&mat, cone->center.x, cone->center.y, cone->center.z);
	rotate_z_mat(&mat, rot_angles[0]);
	rotate_x_mat(&mat, -rot_angles[1]);
	pt3d_mult_mat(pt, mat);
}


#define CAPS_ON 1

int dbl_intersection_pt_cone(t_ray *ray, t_cone *cone, t_impact *impact, \
    t_eq_param eq_sys)
{
	float t[2];
	float t_;


	t[0] = (-eq_sys.b + sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	t[1] = (-eq_sys.b - sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	if (t[0] < 0 && t[1] < 0)
		return (0);
	else if ((t[0] < 0 && t[1] >= 0) || (t[1] < 0 && t[0] >= 0))
		t_ = max(t[0], t[1]);
	else
		t_ = min(t[0], t[1]);

	set_point(&(impact->pt), ray->origin.x + t_ * ray->dir.x, \
    ray->origin.y + t_ * ray->dir.y, ray->origin.z + t_ * ray->dir.z);
	if ((fmod(get_angle(impact->pt.x, impact->pt.z) * DAMIER_FACTOR / M_PI,
			  1.0) > 0.5)
		^ (fmod((fabs(impact->pt.y)) / 2 * DAMIER_FACTOR / M_PI, 1.0) > 0.5))
		impact->rgb = cone->rgb;
	else
		impact->rgb = cone->rgb2;
	impact->tx =
			get_angle(impact->pt.x, impact->pt.z) / (M_PI * 2) * TEXTURE_SIZE;
	impact->ty = impact->pt.y;
	reverse_op_cone(cone, &(impact->pt));
	return (1);

}

int intersection_impact_cone(t_ray *ray, t_cone *cone, t_impact *impact)
{
	t_eq_param eq_sys;

	prepare_ray_for_cone(ray, cone);
	discriminant_cone_2(ray, cone, &eq_sys);
	if (eq_sys.delta < 0)
		return (0);
	return (dbl_intersection_pt_cone(ray, cone, impact, eq_sys));
}
