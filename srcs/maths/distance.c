/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:52:09 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:05:34 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	distance_2d(t_2D_point *A, t_2D_point *B)
{
	return (sqrtf(\
		powf(A->x - B->x, 2) + \
		powf(A->y - B->y, 2) \
		));
}

float	distance_3d(t_3D_point *A, t_3D_point *B)
{
	return (sqrtf(\
			powf(A->x - B->x, 2) + \
			powf(A->y - B->y, 2) + \
			powf(A->z - B->z, 2) \
			));
}
