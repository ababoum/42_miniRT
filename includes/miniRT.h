/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:35:10 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 12:31:32 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"
# include "../minilibx-linux/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// mlx tools
void		mlx_start(t_data *data);
void		img_init(t_data *data);
void		data_init(t_data *data);
void		mlx_events(t_data *data);

// memory & frees
void		*malloc_log(t_data *data, int size);
void		clear_exit(t_data *data, int exit_code);
void		exit_message(t_data *data, char *message, int exit_code);

// 2D drawing
void		pixel_put(t_data *data, int x, int y, int color);

// 2D geometry
t_2D_point	point_2D(float x, float y);

// maths
float		distance_2D(t_2D_point A, t_2D_point B);

// tests
void		draw_circle(t_data *data, int x_center, int y_center, int radius);

#endif