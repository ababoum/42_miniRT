/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_perspective.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:11 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:01:29 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	set_perspective_mat(t_m4 *mat, float near, float from)
{
	double	y_scale;
	double	x_scale;

	y_scale = 1.0 / tan(M_PI / 180.0 * 1 / 2);
	x_scale = y_scale / 1;
	set_identity(mat);
	(*mat)[0] = y_scale;
	(*mat)[5] = x_scale;
	(*mat)[10] = -(from + near) / (from - near);
	(*mat)[11] = -2 * from * near / (from - near);
	(*mat)[14] = -1;
	(*mat)[15] = 0;
}

void	perspective_mat(t_m4 *mat, float near, float from)
{
	t_m4	m;

	set_perspective_mat(&m, near, from);
	mult_matmat(mat, m);
}
