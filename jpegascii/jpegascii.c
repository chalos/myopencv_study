#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "myTool.h"

inline void showImage(IplImage* image, char* winName, int release);
inline IplImage* compress(IplImage* image, int level); 
inline IplImage* grey(IplImage* image);
inline char* asciify(IplImage* image, const char* asciimap);
inline void writeToFile(char* asciiresult, char* fileName);

#ifndef COARSE
	const char GREYMAP[] = GREYMAP_FINE;
#else
	const char GREYMAP[] = GREYMAP_COARSE;
#endif

int main(int argc, char **argv)
{
	if(argc < 4) {
		printf("Usage: %s jpegName outputTxtName compress_ratio \n", argv[0]);
		printf("E.g: \n >> %s ../map2.png output.txt 3 \n", argv[0]);
		return 0;
	}

	char *asciiresult;
	IplImage *image = 0, *image_grey = 0;
	image = cvLoadImage(argv[1] ,1);
	if(image)
	{
		image_grey = grey(compress(image, atoi(argv[3])));
		//showImage(image_grey, "Grey", 0);
		asciiresult = asciify(image_grey, GREYMAP);
		
		writeToFile(asciiresult, argv[2]);
	} else {
		printf("Error reading image \n");
		return 0;
	}
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

inline IplImage* compress(IplImage* image, int level)
{
	int w = image->width/level;
	int h = image->height/level;

	printf("compress: %d width: %d height: %d \n",
		level, w, h);

	IplImage *newImage = cvCreateImage(cvSize(w, h), image->depth, image->nChannels);
	int i,j;

	for_each_pixel(newImage,i,j) {
		pixel_b(newImage,i,j) = pixel_b(image,i*level,j*level);
		pixel_g(newImage,i,j) = pixel_g(image,i*level,j*level);
		pixel_r(newImage,i,j) = pixel_r(image,i*level,j*level);
	}

	return newImage;
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

inline char* asciify(IplImage* image, const char* asciimap)
{
	char* output;
	unsigned int sizeAsciiMap = strlen(asciimap);
	unsigned int outputWidth = image->width + 1;
	unsigned int outputHeight = image->height;
	unsigned char k;

	output = malloc(outputHeight*outputWidth);
	
	int i,j;
	for_each_pixel(image, i, j) {
		unsigned long int index = i * outputWidth + j;
		k = pixel_r(image,i,j);
		k = BOUNDRY_MAP(k, 0, 255, 0, sizeAsciiMap-1);
		output[index] = asciimap[k];	
	}

	// put \n at each end of line
	for(i=outputWidth-1; i<outputHeight*outputWidth; i+=outputWidth) {
		output[i] = '\n';
	}

	return output;
}

inline void writeToFile(char* asciiresult, char* fileName) 
{
	FILE *output;
	output = fopen(fileName, "w+");
	fwrite(asciiresult, sizeof(char), strlen(asciiresult), output);
	fclose(output);
}
