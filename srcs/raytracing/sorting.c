/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:45:05 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 19:08:27 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	test_middle_f(float f1, float f2, float f3)
{
	return ((f1 + EPSILON2 >= f2 && f2 >= f3 - EPSILON2) || \
			(f1 - EPSILON2 <= f2 && f2 <= f3 + EPSILON2));
}

//test if p2 is beetween p2 and p3
int	test_middle(t_3D_point *p1, t_3D_point *p2, t_3D_point *p3)
{
	return (test_middle_f(p1->x, p2->x, p3->x) \
		&& test_middle_f(p1->y, p2->y, p3->y) \
		&& test_middle_f(p1->z, p2->z, p3->z));
}

int	object_between(t_3D_point *p1, t_3D_point *p2, t_data *data)
{
	t_obj		*objs;
	t_ray		ray;

	objs = data->obj_lst;
	while (objs)
	{
		set_point(&(&ray)->origin, p1->x, p1->y, p1->z);
		set_direction_ray_pt(&ray, p2->x, p2->y, p2->z);
		if (objs->type == PLAN)
			if (plan_test(&ray, (t_plan *)objs->ptr, p1, p2))
				return (1);
		if (objs->type == SPHERE)
			if (sphere_test(&ray, (t_sphere *)objs->ptr, p1, p2))
				return (1);
		if (objs->type == CYLINDER)
			if (cyl_test(&ray, (t_cyl *)objs->ptr, p1, p2))
				return (1);
		if (objs->type == CONE)
			if (cn_test(&ray, (t_cone *)objs->ptr, p1, p2))
				return (1);
		objs = objs->next;
	}
	return (0);
}

// For optimization res is in arg, it must have size >= 3
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
