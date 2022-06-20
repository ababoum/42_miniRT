/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:39:36 by mababou           #+#    #+#             */
/*   Updated: 2022/06/20 18:00:42 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	max(float n1, float n2)
{
	if (n1 >= n2)
		return (n1);
	else
		return (n2);
}

float	min(float n1, float n2)
{
	if (n2 <= n1)
		return (n2);
	else
		return (n1);
}

float	switch_val(float n, float n1, float n2)
{
	if (n == n1)
		return (n2);
	else if (n == n2)
		return (n1);
	else
		return (n);
}

int	is_between(float nb, float min, float max)
{
	if (nb >= min && nb <= max)
		return (1);
	else
		return (0);
}
