#ifndef WAVELETPACK_H_
#define WAVELETPACK_H_
#include "stdafx.h"
#include <vector>
#include "Codes.h"
#include "WaveletMatrix.h"

void DirectTransform(float ****image_data, int nChannels, int img_width, int img_height, int img_depth, int width, int height, int depth, int transform_type);
void DirectTransformIteration(float ****image_data, int channel_index, int part_count, int index1, int index2, int direction, const std::vector<std::vector<float>> &matrix_ad);
void InverseTransform(float ****image_data, int nChannels, int img_width, int img_height, int img_depth, int width, int height, int depth, int transform_type);
void InverseTransformIteration(float ****image_data, int channel_index, int part_count, int index1, int index2, int direction, const std::vector<std::vector<float>> &matrix_ad);

float compress(const char* filename, int perc);
void decode(const char* filename);

#endif