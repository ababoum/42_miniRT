/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:35:10 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 18:12:50 by mababou          ###   ########.fr       */
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
void		data_init(t_data *data, const char *path);
void		mlx_events(t_data *data);

// memory & frees
void		*malloc_log(t_data *data, int size);
void		*img_log(t_data *data, int width, int height);
void		clear_exit(t_data *data, int exit_code);
void		exit_message(t_data *data, char *message, int exit_code);

// get next line
int			find_char(char *str, char c);
int			ft_strlen(const char *str);
void		ft_memset(void *ptr, int val, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*get_next_line(int fd);

// strings
int			ft_strcmp(const char *s1, const char *s2);

// strings display
void		ft_putstr_fd(char *str, int fd);

// parsing
void		parse_input(t_data *data, const char *path);
int			verify_file(t_data *data, const char *path);

// 2D drawing
void		pixel_put(t_data *data, int x, int y, int color);

// 2D geometry
t_2D_point	point_2D(float x, float y);

// maths
float		distance_2D(t_2D_point A, t_2D_point B);

// tests
void		draw_circle(t_data *data, t_2D_point center, float radius);

#endif