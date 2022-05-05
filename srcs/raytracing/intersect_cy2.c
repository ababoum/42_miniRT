/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:12:49 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 12:15:48 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_cap_intersected(t_ray *ray, t_cyl *cy, float t)
{
	if (powf(ray->origin.x + t * ray->dir.x, 2) + \
		powf(ray->origin.y + t * ray->dir.y, 2) <= powf(cy->radius, 2))
		return (1);
	else
		return (0);
}
