/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:08:26 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 15:07:11 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	max_vision_axis(float fov)
{
	float	rad;

	rad = M_PI * (fov / 180);
	if (fov == 180)
	{
		return (INT_MAX);
	}
	else
	{
		return (tanf(rad));
	}
}
