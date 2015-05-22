#pragma once
#include "stdafx.h"

#include "WaveletMatrix.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "wavelet.h"

void PrepareMatrix(std::vector<std::vector<float>> &matrix, int dimension, const std::vector<float> &system) {
	if (dimension % 2)
		--dimension;

	int row_index = 0;
	int column_index = 0;
	matrix.resize(dimension);
	for (row_index = 0; row_index < dimension; ++row_index) {
		std::vector<float> row;
		row.resize(dimension);
		for (column_index = 0; column_index < dimension; ++column_index)
			row[column_index] = 0;
		matrix[row_index] = row;
	}

	for (row_index = 0; row_index < dimension / 2; ++row_index) {
		for (column_index = 0; column_index < dimension; ++column_index) {
			int index = (column_index + 1) - 2 * (row_index + 1) + 1;
			int system_index;

			if (index < 0)
				system_index = index + dimension;
			else
				system_index = index;
			if (system_index < 0 || system_index >= system.size())
				matrix[row_index][column_index] = 0;
			else
				matrix[row_index][column_index] = system[system_index];
		}
	}

	for (row_index = 0; row_index < dimension / 2; ++row_index) {
		for (column_index = 0; column_index < dimension; ++column_index) {
			int index = 2 * (row_index + 1) - (column_index + 1);
			int system_index;
			if (index < 0)
				system_index = index + dimension;
			else
				system_index = index;
			if (system_index < 0 || system_index >= system.size())
				matrix[row_index + dimension / 2][column_index] = 0;
			else {
				if ((column_index + 2) % 2)
					matrix[row_index + dimension / 2][column_index] = -system[system_index];
				else
					matrix[row_index + dimension / 2][column_index] = system[system_index];
			}
		}
	}
}


std::vector<float> PrepareSystem(int transform_type) {
	std::vector<float> system;
	switch (transform_type) {
	case (TRANSFORM_TYPE_D2) : 
		system.push_back(1);
		system.push_back(1);
		break;
	case (TRANSFORM_TYPE_D4) : 
		system.push_back(0.6830127);
		system.push_back(1.1830127);
		system.push_back(0.3169873);
		system.push_back(-0.1830127);
		break;
	case (TRANSFORM_TYPE_D6) : 
		system.push_back(0.47046721);
		system.push_back(1.14111692);
		system.push_back(0.650365);
		system.push_back(-0.19093442);
		system.push_back(-0.12083221);
		system.push_back(0.0498175);
		break;
	case (TRANSFORM_TYPE_D8) : 
		system.push_back(0.32580343);
		system.push_back(1.01094572);
		system.push_back(0.8922014);
		system.push_back(-0.03957503);
		system.push_back(-0.26450717);
		system.push_back(0.0436163);
		system.push_back(0.0465036);
		system.push_back(-0.01498699);
		break;			
	case (TRANSFORM_TYPE_D10) : 
		system.push_back(0.22641898);
		system.push_back(0.85394354);
		system.push_back(1.02432694);
		system.push_back(0.19576696);
		system.push_back(-0.34265671);
		system.push_back(-0.04560113);
		system.push_back(0.10970265);
		system.push_back(-0.00882680);
		system.push_back(-0.01779187);
		system.push_back(4.71742793e-3);
		break;		
	case (TRANSFORM_TYPE_D12) : 
		system.push_back(0.15774243);
		system.push_back(0.69950381);
		system.push_back(1.06226376);
		system.push_back(0.44583132);
		system.push_back(-0.31998660);
		system.push_back(-0.18351806);
		system.push_back(0.13788809);
		system.push_back(0.03892321);
		system.push_back(-0.04466375);
		system.push_back(7.83251152e-4);
		system.push_back(6.75606236e-3);
		system.push_back(-1.52353381e-3);
		break;		
	case (TRANSFORM_TYPE_D14) : 
		system.push_back(0.11009943);
		system.push_back(0.56079128);
		system.push_back(1.03114849);
		system.push_back(0.66437248);
		system.push_back(-0.20351382);
		system.push_back(-0.31683501);
		system.push_back(0.1008467);
		system.push_back(0.11400345);
		system.push_back(-0.05378245);
		system.push_back(-0.02343994);
		system.push_back(0.01774979);
		system.push_back(6.07514995e-4);
		system.push_back(-2.54790472e-3);
		system.push_back(5.00226853e-4);
		break;	
	case (TRANSFORM_TYPE_D16) : 
		system.push_back(0.07695562);
		system.push_back(0.44246725);
		system.push_back(0.95548615);
		system.push_back(0.82781653);
		system.push_back(-0.02238574);
		system.push_back(-0.40165863);
		system.push_back(6.68194092e-4);
		system.push_back(0.18207636);
		system.push_back(-0.02456390);
		system.push_back(-0.06235021);
		system.push_back(0.01977216);
		system.push_back(0.01236884);
		system.push_back(-6.88771926e-3);
		system.push_back(-5.54004549e-4);
		system.push_back(9.55229711e-4);
		system.push_back(-1.66137261e-4);
		break;	
	case (TRANSFORM_TYPE_D18) : 
		system.push_back(0.05385035);
		system.push_back(0.34483430);
		system.push_back(0.85534906);
		system.push_back(0.92954571);
		system.push_back(0.18836955);
		system.push_back(-0.41475176);
		system.push_back(-0.13695355);
		system.push_back(0.21006834);
		system.push_back(0.043452675);
		system.push_back(-0.09564726);
		system.push_back(3.54892813e-4);
		system.push_back(0.03162417);
		system.push_back(-6.67962023e-3);
		system.push_back(-6.05496058e-3);
		system.push_back(2.61296728e-3);
		system.push_back(3.25814671e-4);
		system.push_back(-3.56329759e-4);
		system.push_back(5.5645514e-5);
		break;	
	case (TRANSFORM_TYPE_D20) : 
		system.push_back(0.03771716);
		system.push_back(0.26612218);
		system.push_back(0.74557507);
		system.push_back(0.97362811);
		system.push_back(0.39763774);
		system.push_back(-0.35333620);
		system.push_back(-0.27710988);
		system.push_back(0.18012745);
		system.push_back(0.13160299);
		system.push_back(-0.10096657);
		system.push_back(-0.04165925);
		system.push_back(0.04696981);
		system.push_back(5.10043697e-3);
		system.push_back(-0.01517900);
		system.push_back(1.97332536e-3);
		system.push_back(2.81768659e-3);
		system.push_back(-9.69947840e-4);
		system.push_back(-1.64709006e-4);
		system.push_back(1.32354367e-4);
		system.push_back(-1.875841e-5);
		break;
	}


	for (int i = 0; i < system.size(); ++i) {
		system[i] = system[i] / std::sqrt(2.0);
	}
	return system;
}


void MultiplyMatrixVector(const std::vector<std::vector<float>> &matrix, float ****image_data, int channel_index, int part_count, int index1, int index2, int direction) {

	std::vector<float> output;
	output.resize(part_count);
	
	switch (direction) {
	case DIRECTION_ROW:
		for (int out_index = 0; out_index < part_count; ++out_index) {
			output[out_index] = 0;
			#pragma omp parallel for reduction(+:output[out_index])
			for (int column_index = 0; column_index < part_count; ++column_index) {
				output[out_index] += image_data[index2][channel_index][column_index][index1] * matrix[out_index][column_index];
			}
		}

		for (int column_index = 0; column_index < part_count; ++column_index) {
			image_data[index2][channel_index][column_index][index1] = output[column_index];
		}

		break;
	case DIRECTION_COLUMN:
		for (int out_index = 0; out_index < part_count; ++out_index) {
			output[out_index] = 0;
			#pragma omp parallel for reduction(+:output[out_index])
			for (int row_index = 0; row_index < part_count; ++row_index) {
				output[out_index] += image_data[index2][channel_index][index1][row_index] * matrix[out_index][row_index];
			}
		}
		for (int row_index = 0; row_index < part_count; ++row_index) {
			image_data[index2][channel_index][index1][row_index] = output[row_index];
		}
		break;
	case DIRECTION_DEPTH:
		for (int out_index = 0; out_index < part_count; ++out_index) {
			output[out_index] = 0;
			#pragma omp parallel for reduction(+:output[out_index])
			for (int d = 0; d < part_count; ++d) {
				output[out_index] += image_data[d][channel_index][index2][index1] * matrix[out_index][d];
			}
		}
		for (int d = 0; d < part_count; ++d) {
			image_data[d][channel_index][index2][index1] = output[d];
		}
		break;
	} 
}

void TransposeMatrix(std::vector<std::vector<float>> &matrix) {
	float swap;
	for (int i = 0; i < matrix.size() - 1; ++i) {
		for (int j = i + 1; j < matrix.size(); ++j) {
			swap = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = swap;
		}
	}
}