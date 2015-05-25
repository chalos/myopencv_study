#ifndef _MY_TOOL
#define _MY_TOOL
#include <string.h>

#define for_each_pixel(img,i,j) \
	for(i=0; i<img->height; i++)	\
		for(j=0; j<img->width; j++)

#define pixel_r(img,i,j) \
	(img->imageData + (i)*img->widthStep)[(j)*img->nChannels+2]

#define pixel_g(img,i,j) \
	(img->imageData + (i)*img->widthStep)[(j)*img->nChannels+1]

#define pixel_b(img,i,j) \
	(img->imageData + (i)*img->widthStep)[(j)*img->nChannels+0]

#define BOUNDRY_MAP(old, old_min, old_max, new_min, new_max) 	\
	((float)(old - old_min)/(old_max-old_min)*(new_max-new_min)+new_min)

#define GREYMAP_FINE "$@B%%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

#define GREYMAP_COARSE "@%%#*+=-:. "

#endif