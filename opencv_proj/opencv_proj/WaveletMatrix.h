#ifndef WAVELETMATRIX_H_
#define WAVELETMATRIX_H_

#include <vector>

#include "Codes.h"

std::vector<float> PrepareSystem(int transform_type);
void PrepareMatrix(std::vector<std::vector<float>> &matrix, int dimension, const std::vector<float> &system);

void MultiplyMatrixVector(const std::vector<std::vector<float>> &matrix, float ****image_data, int channel_index, int part_count, int index1, int index2, int direction);
void TransposeMatrix(std::vector<std::vector<float>> &matrix);

#endif