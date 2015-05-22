#pragma once

#include "stdafx.h"
#include "PrepareData.h"
#include "WaveletPack.h"
#include "Decimator.h"
#include "PrintFile.h"
#include "wavelet.h"

std::vector<int> transform_block(IplImage **block, int block_size, int nChannels, int height, int width, int system, int savePerc)
{
	float ****block_data = new float***[block_size];
	
	for (int i = 0; i < block_size; ++i){
		float ***image_data = NULL;
		image_data = AllocateImageMemory(nChannels, height, width, image_data);
		auto frame = block[i];
		CopyImageData(frame, image_data, nChannels, height, width);
		block_data[i] = image_data;
	}

	DirectTransform(block_data, nChannels, width, height, block_size, width, height, block_size, system);
	
	std::vector<int> out_data = Decimate(block_data, nChannels, width, height, block_size, savePerc);
	//ConvertArrayToMatrix(out_data, block_data);
	//InverseTransform(block_data, nChannels, width, height, block_size, width, height, block_size, system);

	/*for (int i = 0; i < block_size; ++i){
		auto frame = block[i];
		WriteImageData(block_data[i], frame);
	}*/

	for (int i = 0; i < block_size; ++i)
		FreeImageMemory(nChannels, height, width, block_data[i]);

	delete[] block_data;

	return out_data;
}

IplImage ** decode_block(std::vector<int> out_data, int block_size, int nChannels, int height, int width, int system)
{
	float ****block_data = new float***[block_size];
	
	for (int i = 0; i < block_size; ++i){
		float ***image_data = NULL;
		image_data = AllocateImageMemory(nChannels, height, width, image_data);
		CopyImageData(NULL, image_data, nChannels, height, width);
		block_data[i] = image_data;
	}

	ConvertArrayToMatrix(out_data, block_data);
	InverseTransform(block_data, nChannels, width, height, block_size, width, height, block_size, system);
	IplImage** block = new IplImage*[block_size];

	for (int i = 0; i < block_size; ++i){
		IplImage* imgScribble = cvCreateImage(cvSize(width, height), 8, nChannels);
		WriteImageData(block_data[i], imgScribble);
		block[i] = imgScribble;
	}

	for (int i = 0; i < block_size; ++i)
		FreeImageMemory(nChannels, height, width, block_data[i]);

	delete[] block_data;
	return block;
};