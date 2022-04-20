/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:19:32 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 00:56:54 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"
#include "../../includes/types.h"

t_point	point_new(float x, float y, float z)
{
	t_point	result;

	result.x = x;
	result.y = y;
	result.z = z;

	return (result);
}

void	finalize_point(t_point2 *pt)
{
	pt->x /= pt->w;
	pt->y /= pt->w;
	pt->x += WIN_WIDTH / 2;
	pt->y += WIN_HEIGHT / 2;
}

void	mult_matvec(t_m4 mat, t_point p1, t_point2 *out)
{
	out->x = mat[0] * p1.x + mat[1] * p1.y + mat[2] * p1.z + mat[3];
	out->y = mat[4] * p1.x + mat[5] * p1.y + mat[6] * p1.z + mat[7];
	out->z = mat[8] * p1.x + mat[9] * p1.y + mat[10] * p1.z + mat[11];
	out->w = mat[12] * p1.x + mat[13] * p1.y + mat[14] * p1.z + mat[15];
}

void	matcpy(t_m4 *m1, t_m4 m2)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		(*m1)[i] = m2[i];
		i++;
	}
}

void	mult_matmat(t_m4 *m1, t_m4 m2)
{
	t_m4	res;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			res[i + j * 4] = 0;
			while (k < 4)
			{
				res[i + j * 4] += (*m1)[k + j * 4] * m2[i + k * 4];
				k++;
			}
			j++;
		}
		i++;
	}
	matcpy(m1, res);
}
