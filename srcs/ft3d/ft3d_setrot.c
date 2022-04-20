/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_setrot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:28 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:41:30 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	set_rotation_x_mat(t_m4 *mat, float angle)
{
	set_identity(mat);
	(*mat)[5] = cosf(angle);
	(*mat)[6] = -sinf(angle);
	(*mat)[9] = sinf(angle);
	(*mat)[10] = cosf(angle);
}

void	set_rotation_y_mat(t_m4 *mat, float angle)
{
	set_identity(mat);
	(*mat)[0] = cosf(angle);
	(*mat)[1] = sinf(angle);
	(*mat)[4] = -sinf(angle);
	(*mat)[5] = cosf(angle);
}

void	set_rotation_z_mat(t_m4 *mat, float angle)
{
	set_identity(mat);
	(*mat)[0] = cosf(angle);
	(*mat)[2] = -sinf(angle);
	(*mat)[8] = sinf(angle);
	(*mat)[10] = cosf(angle);
}
