/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:28 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 14:58:31 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// constructor
t_vec	vector(t_3D_point p0, t_3D_point p1)
{
	t_vec	vec;

	vec.x = p1.x - p0.x;
	vec.y = p1.y - p0.y;
	vec.z = p1.z - p0.z;
	return (vec);
}

t_vec	*new_vector(t_3D_point p0, t_3D_point p1)
{
	t_vec	*vec;
	t_data	*data;

	data = get_data(0, 0);
	vec = malloc_log(data, sizeof(t_vec));
	vec->x = p1.x - p0.x;
	vec->y = p1.y - p0.y;
	vec->z = p1.z - p0.z;
	return (vec);
}

// constructor with coordinates
t_vec	vector_f(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec	*new_vector_f(float x, float y, float z)
{
	t_vec	*vec;
	t_data	*data;

	data = get_data(0, 0);
	vec = malloc_log(data, sizeof(t_vec));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

void	set_vector(t_vec *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
