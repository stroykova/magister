#ifndef DECIMATOR_H_
#define DECIMATOR_H_

#include <vector>

std::vector<int> Decimate(float ****image_data, int nChannels, int width, int height, int depth, char decimation_ratio);

#endif