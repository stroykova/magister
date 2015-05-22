#ifndef WAVELET_H_
#define WAVELET_H_


#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

std::vector<int> transform_block(IplImage **block, int block_size, int nChannels, int height, int width, int system, int savePerc);
IplImage ** decode_block(std::vector<int> out_data, int block_size, int nChannels, int height, int width, int system);

#endif