#pragma once
#include "stdafx.h"



#include "median.h"
#include "Codes.h"
#include <stdio.h>
#include <stdlib.h> //Для очистки экрана
#include <fstream>
#include <iostream>
std::vector<int> Decimate(float ****image_data, int nChannels, int width, int height, int depth, char decimation_ratio) {
	
	std::vector<int> out_data;
	
	if (decimation_ratio > 100 || decimation_ratio < 0){
		return out_data;
	}

	std::vector<float> numbers;
	numbers.resize(nChannels*width*height*depth);
	int positive_count = 0;

	float image_data_cell;
	for (int channel_index = 0; channel_index < nChannels; ++channel_index){
		for (int d = 0; d < depth; ++d){
			for (int row_index = 0; row_index < height; ++row_index){
				for (int column_index = 0; column_index < width; ++column_index){
					image_data_cell = image_data[d][channel_index][column_index][row_index];
					numbers[d * nChannels * width * height + channel_index*width*height+width*row_index+column_index] = image_data_cell;
					if (std::abs(image_data_cell) > eps) {
						++positive_count;
					}
				}
			}
		}
	}

	int positive_decimation_count = decimation_ratio * positive_count / 100;

	if (positive_decimation_count == 0) {
		++positive_decimation_count;
	}

	float max_number = 0;

	if (decimation_ratio == 100)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] > max_number)
				max_number = numbers[i];
		}

		max_number = 5 * max_number / 100;
		std::cout << "max: " << max_number<< std::endl;
	}
	else
	{
		max_number = std::abs(RandomizedSelect(numbers, 0, numbers.size() - 1, positive_decimation_count));
		std::cout << "max: " << max_number<< std::endl;
	}

	out_data.push_back(nChannels);
	out_data.push_back(width);
	out_data.push_back(height);
	out_data.push_back(depth);
	int index = 4;

	for (int channel_index = 0; channel_index < nChannels; ++channel_index){
		for (int d = 0; d < depth; ++d){
			for (int row_index = 0; row_index < height; ++row_index){
				for (int column_index = 0; column_index < width; ++column_index){
					if (std::abs(image_data[d][channel_index][column_index][row_index]) >= max_number){
						out_data.push_back(d * nChannels * width * height + channel_index*width*height+width*row_index+column_index);
						//++index;
						out_data.push_back( (int)image_data[d][channel_index][column_index][row_index]);
					}
				} 
			}
		}
	}
	
	return out_data;
};
