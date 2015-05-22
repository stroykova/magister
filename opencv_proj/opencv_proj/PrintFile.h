#ifndef PRINTFILE_H_
#define PRINTFILE_H_

#include <cv.h>
#include <fstream>

void Print3DMatrix(char file_name[], float ***data_3D_matrix, const int channels_count, const int rows_count, const int columns_count);
void PrintImageChannels(char file_name[], IplImage *in_image);

void PrintCompressedData(char file_name[], std::vector<int> data);
std::vector<int> ReadCompressedData(char file_name[]);


#endif