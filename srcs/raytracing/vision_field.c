/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:08:26 by mababou           #+#    #+#             */
/*   Updated: 2022/04/29 15:53:57 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	max_vision_axis(float fov_in_degs)
{
	float	rad;

	rad = M_PI * (fov_in_degs / 180.0f);
	if (fov_in_degs == 180)
		return (INT_MAX);
	else
		return (tanf(rad));
}
