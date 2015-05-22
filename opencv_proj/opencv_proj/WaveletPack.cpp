#include "stdafx.h"
#include <iostream>
#include <omp.h>
//#include <Windows.h>

#include "WaveletPack.h"

#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "wavelet.h"
#include <fstream>
#include <iostream>

#include <stdlib.h> //Для очистки экрана

#include <cstring>
using std::strerror;
#include <cerrno>
#include "WaveletPack.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "../opencv_proj/wavelet.h"

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg(); 
}

float compress(const char* filename, int perc)
{
	printf("[i] file: %s\n", filename);

    // получаем информацию о видео-файле
    CvCapture* capture = cvCreateFileCapture( filename );
	int nFrames = (int) cvGetCaptureProperty( capture , CV_CAP_PROP_FRAME_COUNT );
	std::cout << nFrames << std::endl;

	IplImage *frame = cvQueryFrame( capture ); 

	int nChannels = frame->nChannels;
	std::cout << nChannels << std::endl;
	int height = frame->height;
	std::cout << height << std::endl;
	int width = frame->width;
	std::cout << width << std::endl;

	int totalFileSize = width*height*nChannels*nFrames;
	std::cout << "Total uncompressed file size, bytes:" << std::endl;
	std::cout << totalFileSize << std::endl;

	int sourceFileSize = filesize(filename);

	std::cout << "Source file size, bytes:" << std::endl;
	std::cout << sourceFileSize << "; " << ((float)100*sourceFileSize/totalFileSize) << "%" << std::endl;

	cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, 0);
		
	std::vector<std::vector<int> > blocks;

	//int blockSize = nFrames + 1;
	int blockSize = 1;
	IplImage** block = new IplImage* [blockSize];
	int blockIndex = 0;

	size_t len = strlen(filename);
	char* out = new char[len+8];
	strcpy(out, filename);    
	strcat(out, "out.txt\0");
	printf("[i] out file: %s\n", out);

	do{
		for (int i = 0; i < blockSize; ++i)
		{
			frame = cvQueryFrame( capture ); 
			if (!frame && i == 0 )
				break;

			block[i] = frame ? frame : NULL; 
		}

		std::vector<int> block_data = transform_block(block, blockSize, nChannels, height, width, 4, perc);
		std::cout << block_data[5] <<std::endl;
		blocks.push_back(block_data);
		std::cout << "done" << std::endl;
		++blockIndex;

	}while(frame);

	delete[] block;

	std::ofstream outFile(out, std::ios::binary|std::ios::out);
	if (outFile.fail())          // Check for file creation and return error.
	{
		std::cout << strerror(errno);
		std::cout << "Error opening file for output.\n" << std::endl;
		return 0;
	}

	int system = 4;

	outFile.write((char*)&nChannels,sizeof nChannels);
	outFile.write((char*)&width,sizeof width);
	outFile.write((char*)&height,sizeof height);
	outFile.write((char*)&blockSize,sizeof blockSize);
	outFile.write((char*)&system,sizeof system);

	int totalLength = 0;

	for (int i = 0; i < blocks.size(); ++i){

		size_t size = blocks[i].size();
		outFile.write((char*)&size, sizeof size);

		totalLength += size;
		for (int j = 0; j < size; ++j){
			int part = blocks[i][j];
			outFile.write((char*)&part, sizeof part);
		}
	}

	outFile.close();

	std::cout << "Out file size, bytes:" << std::endl;
	std::cout << totalLength * sizeof(int) << "; " << ((float)100*totalLength /totalFileSize) << "%" << std::endl;
	return ((float)100*totalLength /totalFileSize);
}

void decode(const char* filename)
{
	printf("[i] file: %s\n", filename);

    // окно для отображения картинки

	std::ifstream outFile(filename, std::ios::binary|std::ios::in);
	if (outFile.fail())          // Check for file creation and return error.
	{
		std::cout << "Error opening file for input.\n" << std::endl;
		return;
	}

	int nChannels;
	int height;
	int width;
	int block_size;
	int system;

	outFile.read((char*)&nChannels,sizeof nChannels);
	outFile.read((char*)&width,sizeof width);
	outFile.read((char*)&height,sizeof height);
	outFile.read((char*)&block_size,sizeof block_size);
	outFile.read((char*)&system,sizeof system);

	std::vector<IplImage **> blocks;
	
	int length;
	while (outFile.read((char*)&length,sizeof length)) {
		std::vector<int> out_data;
		int item;
		out_data.resize(length);
		for (int i = 0; i < length; ++i){
			outFile.read((char*)&item,sizeof item);
			out_data[i] = item;
		}

		auto block = decode_block(out_data, block_size, nChannels, height, width, system);

		blocks.push_back(block);
		std::cout << "done" << std::endl;
	}

	outFile.close();

	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	char c;
	while(true)
	{
		int blocks_size = blocks.size();
		for (int i = 0; i < blocks_size; ++i){
			for (int j = 0; j < block_size; ++j){
				cvShowImage( "original", blocks[i][j] ); 
				c = cvWaitKey(33);
				if (c == 27) { //ESC
						break;
				}
			}
		}
		if (c == 27) { //ESC
						break;
				}
	}
    cvDestroyWindow("original");
}


void DirectTransform(float ****image_data, int nChannels, int img_width, int img_height, int img_depth, int width, int height, int depth, int transform_type) {

	std::vector<float> system = PrepareSystem(transform_type);

	//if (height < system.size() && width < system.size() ){
	//	return;
	//}

	if (height < system.size() && width < system.size() && depth < system.size()){
		return;
	}

	if (width >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		
		PrepareMatrix(matrix_ad, width, system);

		omp_set_dynamic(0); 
		omp_set_num_threads(img_height);

		//свернем строки 
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int d = 0; d < img_depth; ++d){
					#pragma omp parallel for 
					for (int row_index = 0; row_index < img_height; ++row_index){
						DirectTransformIteration(image_data, channel_index, width, row_index, d, DIRECTION_ROW, matrix_ad);
					}
			}
		}
		width = width >> 1;
	}

	if (height >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		PrepareMatrix(matrix_ad, height, system);

		omp_set_dynamic(0); 
		omp_set_num_threads(img_width);

		//свернем столбцы 
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int d = 0; d < img_depth; ++d){
				#pragma omp parallel for 
				for (int column_index = 0; column_index < img_width; ++column_index){
					DirectTransformIteration(image_data, channel_index, height, column_index, d, DIRECTION_COLUMN, matrix_ad);
				}
			}
		}
		height = height >> 1;
	}

	if (depth >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		PrepareMatrix(matrix_ad, depth, system);

		omp_set_dynamic(0); 
		omp_set_num_threads(img_width);

		//свернем столбцы 
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int row_index = 0; row_index < img_height; ++row_index){
				#pragma omp parallel for 
				for (int column_index = 0; column_index < img_width; ++column_index){
					DirectTransformIteration(image_data, channel_index, depth, row_index, column_index, DIRECTION_DEPTH, matrix_ad);
				}
			}
		}
		depth = depth >> 1;
	}

	DirectTransform(image_data, nChannels, img_width / 2, img_height / 2, img_depth / 2, width, height, depth, transform_type);
}

void DirectTransformIteration(float ****image_data, int channel_index, int part_count, int index1, int index2, int direction, const std::vector<std::vector<float>> &matrix_ad){
	if (part_count <= 1){
		return;
	}

	if (part_count % 2){
		--part_count;
	}
	MultiplyMatrixVector(matrix_ad, image_data, channel_index, part_count, index1, index2, direction);
}

void InverseTransform(float ****image_data, int nChannels, int img_width, int img_height, int img_depth, int width, int height, int depth, int transform_type) {
	
	std::vector<float> system = PrepareSystem(transform_type);

	if (height < system.size() && width < system.size() && depth < system.size()){
		return;
	}

	InverseTransform(image_data, nChannels, img_width / 2, img_height / 2, img_depth / 2, width / 2, height / 2, depth / 2, transform_type);
	
	if(depth >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		PrepareMatrix(matrix_ad, depth, system);
		TransposeMatrix(matrix_ad);
		omp_set_dynamic(0); 
		omp_set_num_threads(img_width);

		//развернем столбцы по всем каналам
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int row_index = 0; row_index < img_height; ++row_index){
				#pragma omp parallel for 
				for (int column_index = 0; column_index < img_width; ++column_index){
					InverseTransformIteration(image_data, channel_index, depth, row_index, column_index, DIRECTION_DEPTH, matrix_ad);
				}
			}
		}
	}

	if (height >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		PrepareMatrix(matrix_ad, height, system);
		TransposeMatrix(matrix_ad);

		omp_set_dynamic(0); 
		omp_set_num_threads(img_width);

		//развернем столбцы по всем каналам
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int d = 0; d < img_depth; ++d){
				#pragma omp parallel for 
				for (int column_index = 0; column_index < img_width; ++column_index){
					InverseTransformIteration(image_data, channel_index, height, column_index, d, DIRECTION_COLUMN, matrix_ad);
				}
			}
		}
	}
	if(width >= system.size()){
		std::vector<std::vector<float>> matrix_ad;
		PrepareMatrix(matrix_ad, width, system);
		TransposeMatrix(matrix_ad);
		omp_set_dynamic(0); 
		omp_set_num_threads(img_height);

		//развернем строки по всем каналам
		for (int channel_index = 0; channel_index < nChannels; ++channel_index){
			for (int d = 0; d < img_depth; ++d){
				#pragma omp parallel for 
				for (int row_index = 0; row_index < img_height; ++row_index){
					InverseTransformIteration(image_data, channel_index, width, row_index, d, DIRECTION_ROW, matrix_ad);
				}
			}
		}
	}
}

void InverseTransformIteration(float ****image_data, int channel_index, int part_count, int index1, int index2, int direction, const std::vector<std::vector<float>> &matrix_ad){
	if (part_count <= 1){
		return;
	}
	if (part_count % 2){
		--part_count;
	}
	MultiplyMatrixVector(matrix_ad, image_data, channel_index, part_count, index1, index2, direction);
}