/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:15:48 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 18:40:04 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	check_int_color(int RGB[3])
{
	if (RGB[0] < 0 || RGB[0] > 255 || \
		RGB[1] < 0 || RGB[1] > 255 || \
		RGB[2] < 0 || RGB[2] > 255)
		return (0);
	return (1);
}

int	RGB_to_int(int RGB[3])
{
	return (0xFFFF * RGB[0] + 0xFF * RGB[1] + RGB[2]);
}
