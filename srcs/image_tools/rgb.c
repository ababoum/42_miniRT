//
// Created by plefevre on 4/25/22.
//

int arr_toRGB(int *rgb)
{
	return rgb[0] + rgb[1] * 256 + rgb[2] * 65536;
}


int rgb_ambiant(int rgb, int *lrgb, float grad)
{
	int r;
	int g;
	int b;

	r = rgb % 256;
	g = (rgb / 256) % 256;
	b = (rgb / 65536) % 256;
	r *= grad * lrgb[0] / 256;
	g *= grad * lrgb[1] / 256;
	b *= grad * lrgb[2] / 256;

	return (r + g * 256 + b * 65536);
}
