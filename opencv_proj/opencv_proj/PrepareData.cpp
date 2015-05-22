#include "stdafx.h"

#include "PrepareData.h"

float*** AllocateImageMemory(int channels_count, int row_count, int column_count, float ***image_data) {
	image_data = new float**[channels_count]; 
	for (int channel_index = 0; channel_index < channels_count; ++channel_index){
		image_data[channel_index] = new float*[column_count]; 
		for (int column_index = 0; column_index < column_count; ++column_index){
			image_data[channel_index][column_index] = new float[row_count]; 
		}
	}
	return image_data;
}

void CopyImageData(IplImage *in_image, float ***image_data, int nChannels, int height, int width) {
	for (int channel_index = 0; channel_index < nChannels; ++channel_index) {
		for (int column_index = 0; column_index < width; ++column_index) {
			for (int row_index = 0; row_index < height; ++row_index) {
				image_data[channel_index][column_index][row_index] = in_image ? (unsigned char)(in_image->imageData + row_index*in_image->widthStep)[column_index*in_image->nChannels + channel_index] : 0;
			}
		}
	}
}

void WriteImageData(float ***image_data, IplImage *in_image) {
	if (!in_image)
		return;

	for (int channel_index = 0; channel_index < in_image->nChannels; ++channel_index) {
		for (int column_index = 0; column_index < in_image->width; ++column_index) {
			for (int row_index = 0; row_index < in_image->height; ++row_index) {
				
				float cell = std::ceil(image_data[channel_index][column_index][row_index]);
				if (cell > 255) {
					cell=255;
				}
				else if (cell < 0) {
					cell=0;
				}
				//else {
					(in_image->imageData + row_index*in_image->widthStep)[column_index*in_image->nChannels + channel_index] = cell;
				//}
			}
		}
	}
}

void FreeImageMemory(int channels_count, int row_count, int column_count, float ***image_data) {
	for (int channel_index = 0; channel_index < channels_count; ++channel_index){
		for (int column_index = 0; column_index < column_count; ++column_index){
			delete[] image_data[channel_index][column_index];
		}
		delete[] image_data[channel_index];
	}
	delete[] image_data;
}

void ConvertArrayToMatrix(std::vector<int> &data, float ****image_data) {
	
	int nChannels = data[0];
	int width = data[1];
	int height = data[2];
	int depth = data[3];

	for (int channel_index = 0; channel_index < nChannels; ++channel_index){
		for (int d = 0; d < depth; ++d){
			for (int row_index = 0; row_index < height; ++row_index){
				for (int column_index = 0; column_index < width; ++column_index){
					image_data[d][channel_index][column_index][row_index] = 0;
				}
			}
		}
	}

	int row_index = 0;
	int ch_index = 0;
	int col_index = 0;
	int d = 0;

	for (int i = 4; i < data.size(); i+=2) {
		d = data[i] / (nChannels * width * height);
		int part = d != 0 ? data[i] % (d * nChannels * width * height) : data[i];
		ch_index =  part / (width * height);
		row_index = (part % (width * height)) / width;
		col_index = (part % (width * height)) % width;
		image_data[d][ch_index][col_index][row_index] = data[i + 1];
	}
}