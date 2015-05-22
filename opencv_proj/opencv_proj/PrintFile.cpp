#include "stdafx.h"
#include "PrintFile.h"
#include <vector>

void Print3DMatrix(char file_name[], float ***data_3D_matrix, const int channels_count, const int rows_count, const int columns_count)
{
	std::ofstream out_stream;
	out_stream.open(file_name, std::ios::out);
	for (int channel_index = 0; channel_index < channels_count; ++channel_index)
	{
		for (int row_index = 0; row_index < rows_count; ++row_index)
		{
			for (int column_index = 0; column_index < columns_count; ++column_index)
			{
				out_stream << data_3D_matrix[channel_index][column_index][row_index] << " ";
			}
			out_stream << std::endl;
		}
		out_stream << std::endl;
	}
	out_stream << std::endl;
	out_stream.close();
}
void PrintImageChannels(char file_name[], IplImage *in_image)
{
	std::ofstream out_stream;
	out_stream.open(file_name, std::ios::out);

	for (int channel_index = 0; channel_index < in_image->nChannels; ++channel_index)
	{
		for (int row_index = 0; row_index < in_image->height; ++row_index)
		{
			for (int column_index = 0; column_index < in_image->width; ++column_index)
			{
				out_stream << (int)(unsigned char)(in_image->imageData + row_index*in_image->widthStep)[column_index*in_image->nChannels + channel_index] << " ";
			}
			out_stream << std::endl;
		}
		out_stream << std::endl;
	}
	out_stream << std::endl;
	out_stream.close();
}



void PrintCompressedData(char file_name[], std::vector<int> data) {
	std::ofstream out_stream;
    out_stream.open(file_name, std::ios::binary);

	for (int i = 0; i < data.size(); ++i) {
		out_stream.write((char *)&data[i], sizeof(int));

	}
	out_stream.close();
}

std::vector<int> ReadCompressedData(char file_name[]) {
	std::ifstream in_stream;
    in_stream.open(file_name, std::ios::binary);
	int a = 0;
	std::vector<int> data;
	while(in_stream.read((char *)&a, sizeof(int))) {
		data.push_back(a);
	}
	in_stream.close();
	return data;
}

//перенести функции чтения из файла и записи в файл