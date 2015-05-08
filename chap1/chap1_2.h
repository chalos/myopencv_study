#ifndef CHAP1_2_H
#define CHAP1_2_H

#define for_each_pixel(img,i,j) \
	for(i=0; i<img->height; i++)	\
		for(j=0; j<img->width; j++)

#define pixel_r(img,i,j) \
	(img->imageData + i*img->widthStep)[j*img->nChannels+2]

#define pixel_g(img,i,j) \
	(img->imageData + i*img->widthStep)[j*img->nChannels+1]

#define pixel_b(img,i,j) \
	(img->imageData + i*img->widthStep)[j*img->nChannels+0]

#endif