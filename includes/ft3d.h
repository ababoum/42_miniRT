/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:27:01 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:23:35 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT3D_H
# define FT3D_H

# include <math.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_point2
{
	float	x;
	float	y;
	float	z;
	float	w;
	int		c;
}	t_point2;

typedef float	t_m4[16];

void	set_identity(t_m4 *mat);
void	set_null(t_m4 *mat);

void	mult_matvec(t_m4 mat, t_point p1, t_point2 *out);

void	set_rotation_x_mat(t_m4 *mat, float angle);
void	set_rotation_y_mat(t_m4 *mat, float angle);
void	set_rotation_z_mat(t_m4 *mat, float angle);

void	rotate_x_mat(t_m4 *mat, float angle);
void	rotate_y_mat(t_m4 *mat, float angle);
void	rotate_z_mat(t_m4 *mat, float angle);

void	set_translation_mat(t_m4 *mat, float x, float y, float z);
void	translate_mat(t_m4 *mat, float x, float y, float z);

void	set_resize_mat(t_m4 *mat, float x, float y, float z);
void	resize_mat(t_m4 *mat, float x, float y, float z);

void	set_perspective_mat(t_m4 *mat, float near, float from);
void	perspective_mat(t_m4 *mat, float near, float from);

void	mult_matmat(t_m4 *m1, t_m4 m2);

t_point	point_new(float x, float y, float z);
void	finalize_point(t_point2 *pt);

#endif //FDF_3D_H
