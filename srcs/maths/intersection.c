/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:32:06 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 17:04:09 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// check if a ray intersects with a sphere
static float	discriminant_sp(t_ray *ray, t_sphere *sp)
{
	int	dr[3];
	int	disc[3];

	dr[0] = ray->dir->x - ray->origin->x;
	dr[1] = ray->dir->y - ray->origin->y;
	dr[2] = ray->dir->z - ray->origin->z;
	disc[0] = powf(dr[0], 2) + powf(dr[1], 2) + powf(dr[2], 2);
	disc[1] = 2 * (dr[0] * (ray->origin->x - sp->center->x) + \
					dr[1] * (ray->origin->y - sp->center->y) + \
					dr[2] * (ray->origin->z - sp->center->z));
	disc[2] = powf(sp->center->x, 2) + powf(sp->center->y, 2) + \
			powf(sp->center->z, 2) + powf(ray->origin->x, 2) + \
			powf(ray->origin->y, 2) + powf(ray->origin->z, 2) \
			- 2 * (sp->center->x * ray->origin->x + \
			sp->center->y * ray->origin->y + sp->center->z * ray->origin->z) - \
			powf(sp->radius, 2);
	return (powf(disc[1], 2) - 4 * disc[0] * disc[2]);
}

int	intersect_sp(t_ray *ray, t_sphere *sp)
{
	if (discriminant_sp(ray, sp) < 0)
		return (0);
	return (1);
}
