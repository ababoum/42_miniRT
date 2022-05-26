/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:14:07 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 18:54:53 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

void	set_texture(t_data *data, char *filename, unsigned char *texture)
{
	int		w;
	int		h;
	t_img	*img;
	int		i;

	img = mlx_xpm_file_to_image(data->session, filename, &w, &h);
	if (img == 0)
		exit_message(data, "Can't load texture.xpm", 4);
	mem_add_back(&(data->mem_lst), new_mem(data, img, IMG_TYPE));
	if (w != TEXTURE_SIZE || h != TEXTURE_SIZE)
		exit_message(data, "Bad texture.xpm size", 4);
	i = -1;
	while (++i < TEXTURE_SIZE * TEXTURE_SIZE)
		texture[i] = *(img->data + 4 * i);
}
