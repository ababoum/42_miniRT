/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:45:05 by mababou           #+#    #+#             */
/*   Updated: 2022/05/03 19:46:13 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	test_middle_f(float f1, float f2, float f3)
{
	return ((f1 >= f2 && f2 >= f3) || (f1 <= f2 && f2 <= f3));
}

//test if p2 is beetween p2 and p3
int	test_middle(t_3D_point *p1, t_3D_point *p2, t_3D_point *p3)
{
	return (test_middle_f(p1->x, p2->x, p3->x)
		&& test_middle_f(p1->y, p2->y, p3->y)
		&& test_middle_f(p1->z, p2->z, p3->z));
}

int	object_between(t_3D_point *p1, t_3D_point *p2, t_ray *ray, t_data *data)
{
	(void) p1;
	(void) p2;
	(void) data;

	t_obj *objs = data->obj_lst;

	while (objs)
	{
		if (objs->type == 0)
		{
			t_sphere *sp = (t_sphere *) objs->ptr;
			t_3D_point pt;

			projection_pt_droite(ray, sp->center, &pt);
//			if (distance_3d(&pt,sp->center) < sp->radius && test_middle(p1, &pt, p2))
			if (test_middle(p1, &pt, p2))
				return (1);
		}
		objs = objs->next;
	}

	return (0);
}
