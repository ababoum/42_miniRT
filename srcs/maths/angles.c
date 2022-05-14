/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:04:50 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 20:40:17 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	get_angle(float dx, float dy)
{
	double	a;

	a = atan(fabs(dy) / fabs(dx));
	if (dx > 0 && dy > 0)
		return (a);
	if (dx < 0 && dy > 0)
		return (-a + (float) M_PI);
	if (dx < 0 && dy < 0)
		return (a + (float) M_PI);
	if (dx > 0 && dy < 0)
		return (-a + 2 * (float) M_PI);
	if (dy == 0)
	{
		if (dx < 0)
			return (M_PI);
		return (0.0f);
	}
	if (dx == 0)
	{
		if (dy > 0)
			return (M_PI / 2.0f);
		return (3.0f * M_PI / 2.0f);
	}
	return (0);
}

float	rad_to_deg(float angle_in_rad)
{
	return ((float)(angle_in_rad / 2 / M_PI * 180.0));
}

float	deg_to_rad(float angle_in_deg)
{
	return (angle_in_deg * M_PI / 180.0f);
}
