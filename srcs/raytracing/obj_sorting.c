/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sorting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:35:14 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 19:08:35 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	plan_test(t_ray *ray, t_plan *pl, t_3D_point *p1, t_3D_point *p2)
{
	t_impact	impact;

	if (intersection_impact_pl(ray, pl, &impact))
	{
		if (test_middle(p1, &impact.pt, p2) && \
			distance_3d(*p2, impact.pt) > EPSILON)
			return (1);
	}
	return (0);
}

int	sphere_test(t_ray *ray, t_sphere *sp, t_3D_point *p1, t_3D_point *p2)
{
	t_3D_point	pt;

	if (intersection_pt_sp(ray, sp, &pt))
	{
		if (test_middle(p1, &pt, p2) && distance_3d(*p2, pt) > EPSILON)
			return (1);
	}
	return (0);
}

int	cyl_test(t_ray *ray, t_cyl *cy, t_3D_point *p1, t_3D_point *p2)
{
	t_impact	impact;

	if (intersection_impact_cy(ray, cy, &impact))
	{
		if (test_middle(p1, &(impact.pt), p2) && \
			distance_3d(*p2, impact.pt) > 1 * EPSILON)
			return (1);
	}
	return (0);
}

int	cn_test(t_ray *ray, t_cone *cn, t_3D_point *p1, t_3D_point *p2)
{
	t_impact	impact;

	if (intersection_impact_cone(ray, cn, &impact))
	{
		if (test_middle(p1, &(impact.pt), p2) && \
			distance_3d(*p2, impact.pt) > 1 * EPSILON)
			return (1);
	}
	return (0);
}
