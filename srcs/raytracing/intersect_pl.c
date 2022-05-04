/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:02:08 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 11:55:31 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// warning: the ray needs to be normalized
int	intersection_pt_pl(t_ray *ray, t_plan *pl, t_3D_point *pt)
{
	int	disc[2];

	disc[0] = scalar(pl->normal, vector(pl->point, &ray->origin));
	disc[1] = scalar(pl->normal, &ray->dir);
	if (disc[1] == 0 || disc[0] == 0)
		return (0);
	set_3d_point(pt, ray->origin.x + (disc[0] / disc[1]) * ray->dir.x,
		ray->origin.y + (disc[0] / disc[1]) * ray->dir.y,
		ray->origin.z + (disc[0] / disc[1]) * ray->dir.z);
	return (1);
}
