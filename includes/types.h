/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:34:43 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 17:07:52 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define SPACES		"\t\n\v\f\r "

# define RED_TXT	"\e[31;1m"
# define RESET_TXT	"\e[0m"

# define MEM_TYPE	1
# define IMG_TYPE	2

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

# define ESC_KEY		65307
# define ARROW_LEFT		65361
# define ARROW_UP		65362
# define ARROW_RIGHT	65363
# define ARROW_DOWN		65364

# define X_CLOSE		17

# define BUFFER_SIZE	42

# define EPSILON		0.00005

# define SPHERE			0
# define PLAN			1
# define CYLINDER		2

typedef struct s_memlog {
	void			*ptr;
	struct s_memlog	*next;
	int				type;
}	t_memlog;

typedef struct s_obj {
	void			*ptr;
	struct s_obj	*next;
	int				type;
}	t_obj;

typedef struct s_2D_point {
	float	x;
	float	y;
}	t_2D_point;

typedef struct s_3D_point {
	float	x;
	float	y;
	float	z;
}	t_3D_point;

typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_ambiance {
	float	grad;
	int		rgb[3];
}	t_ambiance;

typedef struct s_camera {
	t_3D_point	*pov;
	t_3D_point	*dir;
	float		fov;
}	t_camera;

typedef struct s_light {
	t_3D_point	*src;
	float		pow;
	int			rgb[3];
}	t_light;

typedef struct s_data {
	void		*session;
	void		*win;
	t_img		*img;
	t_memlog	*mem_lst;
	t_obj		*obj_lst;
	t_ambiance	*amb;
	t_camera	*cam;
	t_light		*lum;
}	t_data;

typedef struct s_ray {
	t_3D_point	*origin;
	t_3D_point	*dir;
}	t_ray;

typedef struct s_sphere {
	t_3D_point	*center;
	float		radius;
	int			rgb[3];
}	t_sphere;

typedef void	(*t_pop_fn)(t_data *, char *);

#endif