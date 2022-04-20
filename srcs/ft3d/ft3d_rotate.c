/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:19 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:41:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	rotate_x_mat(t_m4 *mat, float angle)
{
	t_m4	m;

	set_rotation_x_mat(&m, angle);
	mult_matmat(mat, m);
}

void	rotate_y_mat(t_m4 *mat, float angle)
{
	t_m4	m;

	set_rotation_y_mat(&m, angle);
	mult_matmat(mat, m);
}

void	rotate_z_mat(t_m4 *mat, float angle)
{
	t_m4	m;

	set_rotation_z_mat(&m, angle);
	mult_matmat(mat, m);
}
