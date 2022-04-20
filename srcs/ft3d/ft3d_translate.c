/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:34 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:41:36 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	set_translation_mat(t_m4 *mat, float x, float y, float z)
{
	set_identity(mat);
	(*mat)[3] = x;
	(*mat)[7] = y;
	(*mat)[11] = z;
}

void	translate_mat(t_m4 *mat, float x, float y, float z)
{
	t_m4	m;

	set_translation_mat(&m, x, y, z);
	mult_matmat(mat, m);
}
