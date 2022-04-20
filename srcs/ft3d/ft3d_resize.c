/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_resize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:16 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:41:18 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	set_resize_mat(t_m4 *mat, float x, float y, float z)
{
	set_identity(mat);
	(*mat)[0] = x;
	(*mat)[5] = y;
	(*mat)[10] = z;
}

void	resize_mat(t_m4 *mat, float x, float y, float z)
{
	t_m4	m;

	set_resize_mat(&m, x, y, z);
	mult_matmat(mat, m);
}
