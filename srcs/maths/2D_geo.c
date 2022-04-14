/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:57:55 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:01:02 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_2D_point	*dot_2d(float x, float y)
{
	t_2D_point	*point;
	t_data		*data;

	data = get_data(0, 0);
	point = malloc_log(data, sizeof(t_2D_point));
	point->x = x;
	point->y = y;
	return (point);
}
