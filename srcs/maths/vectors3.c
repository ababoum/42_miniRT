/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:42 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 16:12:21 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vec_prod(t_vec u, t_vec v)
{
	t_vec	prod;

	prod.x = u.y * v.z - u.z * v.y;
	prod.y = u.z * v.x - u.x * v.z;
	prod.z = u.x * v.y - u.y * v.x;
	return (prod);
}

float	vec_dot(t_vec u, t_vec v)
{
	float	dot;

	dot = u.x * v.x;
	dot += u.y * v.y;
	dot += u.z * v.z;
	return (dot);
}
