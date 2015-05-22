#ifndef PREPARE_DATA_H_
#define PREPARE_DATA_H_

#include <cv.h>
#include <cxcore.h> 
#include <highgui.h>
#include <vector>

float*** AllocateImageMemory(int channels_count, int row_count, int column_count, float ***image_data);
void CopyImageData(IplImage *in_image, float ***image_data, int nChannels, int height, int width);
void WriteImageData(float ***image_data, IplImage *in_image);
void FreeImageMemory(int channels_count, int row_count, int column_count, float ***image_data);

void ConvertArrayToMatrix(std::vector<int> &data, float ****image_data);

#endif