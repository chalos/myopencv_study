// chapter 1.2 The Basic Opencv code test run

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "chap1_2.h"

#define NEW64 "64"
#define INPUT "Input Image"
#define GREY "Show grey"
#define COMPRESS "Compress Image"
#define THRESH "Threst Image"

inline void showImage(IplImage* , char*, int);
inline IplImage* create64x64();
inline IplImage* compress(IplImage* , int);
inline IplImage* grey(IplImage* );
inline IplImage* thresh(IplImage* );

int main(int argc, char **argv)
{
	if(argc != 2) printf("No image name input... \n");

	IplImage *image = 0;
	image = cvLoadImage(argv[1] ,1);
	if(image)
	{
		showImage(create64x64(), NEW64, 1);
		showImage(image, INPUT, 0);
		showImage(compress(image, 1), COMPRESS, 1);
		showImage(grey(compress(image, 1)), GREY, 1);
		showImage(thresh(compress(image,1)), THRESH, 1);
	} else {
		printf("Error reading image \n");
		return 0;
	}
}

inline IplImage* create64x64()
{
	IplImage *newImage = cvCreateImage(cvSize(64,64), 8, 3);
	int i,j;
	for_each_pixel(newImage, i, j)
	{
		pixel_r(newImage,i,j) = rand()%256;
		pixel_g(newImage,i,j) = rand()%256;
		pixel_b(newImage,i,j) = rand()%256;
	}

	return newImage;
}

inline void showImage(IplImage* image, char* winName, int release)
{
	printf("%s's width: %d height: %d depth: %d nchannels:%d \n", 
		winName, image->width, image->height, image->depth, image->nChannels);
	cvNamedWindow(winName, 1);
	cvShowImage(winName, image);
	printf("Press any key to exit... \n");
	cvWaitKey(0);
	cvDestroyWindow(winName);

	if(release == 1) cvReleaseImage(&image);
}

inline IplImage* grey(IplImage* image)
{
	int i,j;
	IplImage* newImage = cvCloneImage(image);

	for_each_pixel(newImage,i,j) {
		int k = (
			pixel_b(newImage,i,j) + pixel_g(newImage,i,j) + pixel_r(newImage,i,j)
			) /newImage->nChannels;
		pixel_r(newImage,i,j) = pixel_g(newImage,i,j) = pixel_b(newImage,i,j) = (unsigned char) k;
	}

	return newImage;
}

inline IplImage* compress(IplImage* image, int level)
{
	int w = image->width/level;
	int h = image->height/level;

	printf("%s's compress: %d width: %d height: %d \n",
		COMPRESS, level, w, h);

	IplImage *newImage = cvCreateImage(cvSize(w, h), image->depth, image->nChannels);
	int i,j;

	for_each_pixel(newImage,i,j) {
		pixel_b(newImage,i,j) = pixel_b(image,i*level,j*level);
		pixel_g(newImage,i,j) = pixel_g(image,i*level,j*level);
		pixel_r(newImage,i,j) = pixel_r(image,i*level,j*level);
	}

	return newImage;
}

inline IplImage* thresh(IplImage* image){
	int i,j;
	long int mean = 0, count = 0;

	IplImage* newImage = cvCloneImage(image);
	
	for_each_pixel(newImage, i, j) {
		int k = (
			pixel_b(newImage,i,j) + pixel_g(newImage,i,j) + pixel_r(newImage,i,j)
			) /newImage->nChannels;
		mean += k;
		//count ++;
	};

	mean = mean / (image->height*image->width); //count;

	for_each_pixel(newImage, i, j) {
		int k = pixel_b(newImage,i,j);
		if(k < mean) {
			k = 0;
		} else {
			k = 255;
		}

		pixel_b(newImage,i,j) = pixel_g(newImage,i,j) = pixel_r(newImage,i,j) = (unsigned char) k;
	};
	return newImage;
}
