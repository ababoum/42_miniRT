#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

void set_texture(t_data *data, char *filename, unsigned char *texture)
{
	int w;
	int h;
	t_img *img;
	img = mlx_xpm_file_to_image (data->session , filename, &w, &h );

	if (img == 0)
		exit_message(data, "Can't load texture.xpm", 4);
	if (w != TEXTURE_SIZE || h != TEXTURE_SIZE)
		exit_message(data, "Bad texture.xpm size", 4);

	int i = 0;
	while (i < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		texture[i] = *(img->data + 4 * i);
		i++;
	}
}