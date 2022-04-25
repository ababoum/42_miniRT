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
static float discriminant_sp(t_ray *ray, t_sphere *sp)
{
	int dr[3];
	int disc[3];

	dr[0] = ray->dir->x;
	dr[1] = ray->dir->y;
	dr[2] = ray->dir->z;
	disc[0] = powf(dr[0], 2) + powf(dr[1], 2) + powf(dr[2], 2);
	disc[1] = 2 * (dr[0] * (ray->origin->x - sp->center->x) + \
                    dr[1] * (ray->origin->y - sp->center->y) + \
                    dr[2] * (ray->origin->z - sp->center->z));
	disc[2] = powf(sp->center->x, 2) + powf(sp->center->y, 2) + \
            powf(sp->center->z, 2) + powf(ray->origin->x, 2) + \
            powf(ray->origin->y, 2) + powf(	ray->origin->z, 2) \
 - 2 * (sp->center->x * ray->origin->x + \
            sp->center->y * ray->origin->y + sp->center->z * ray->origin->z) - \
            powf(sp->radius, 2);
	return (powf(disc[1], 2) - 4 * disc[0] * disc[2]);
}

int intersection_pt_sp(t_ray *ray, t_sphere *sp, t_3D_point *pt)
{
	int dr[3];
	int disc[3];
	float d;

	dr[0] = ray->dir->x;
	dr[1] = ray->dir->y;
	dr[2] = ray->dir->z;
	disc[0] = powf(dr[0], 2) + powf(dr[1], 2) + powf(dr[2], 2);
	disc[1] = 2 * (dr[0] * (ray->origin->x - sp->center->x) + \
                    dr[1] * (ray->origin->y - sp->center->y) + \
                    dr[2] * (ray->origin->z - sp->center->z));
	disc[2] = powf(sp->center->x, 2) + powf(sp->center->y, 2) + \
            powf(sp->center->z, 2) + powf(ray->origin->x, 2) + \
            powf(ray->origin->y, 2) + powf(	ray->origin->z, 2) \
 - 2 * (sp->center->x * ray->origin->x + \
            sp->center->y * ray->origin->y + sp->center->z * ray->origin->z) - \
            powf(sp->radius, 2);
	d = (powf(disc[1], 2) - 4 * disc[0] * disc[2]);
	if (d < 0 )
		return (0);
	float x;
	if (disc[0] == 0 && disc[1] == 0)
		return (0);
	else if (disc[0] == 0)
		x = -disc[2] / disc[1];
	else
		x = (-disc[1] - sqrtf(d)) / (2 * disc[0]);

	pt->x = ray->origin->x + x * ray->dir->x;
	pt->y = ray->origin->y + x * ray->dir->y;
	pt->z = ray->origin->z + x * ray->dir->z;

	return (1);
}


float norm(t_3D_point *pt)
{
	float n;

	n = 0;
	n += pt->x * pt->x;
	n += pt->y * pt->y;
	n += pt->z * pt->z;

	return (powf(n,0.5f));

}

void normalize(t_3D_point *pt)
{
	float n;

	n = norm(pt);
	pt->x /= n;
	pt->y /= n;
	pt->z /= n;
}

//For optimization res is in arg, it must have size >= 3
void projection_pt_droite(t_ray *ray, t_3D_point *pt, t_3D_point *res)
{
	float k = ray->dir->x * (pt->x - ray->origin->x)
			  + ray->dir->y * (pt->y - ray->origin->y)
			  + ray->dir->z * (pt->z - ray->origin->z);
	res->x = ray->origin->x + k * ray->dir->x ;
	res->y = ray->origin->y + k * ray->dir->y;
	res->z = ray->origin->z + k * ray->dir->z;
}



int intersect_sp(t_ray *ray, t_sphere *sp)
{
	if (discriminant_sp(ray, sp) < 0)
		return (0);
	return (1);
}
