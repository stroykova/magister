#include "stdafx.h"
#include "median.h"

float RandDbl() {
	return rand() / ((float)RAND_MAX + 1.0);
}

int RandInt(int n){
	return (int)(n * RandDbl());
}

int Partition(std::vector<float> &numbers, int left, int right) {
	float x = std::abs(numbers[right]);
	int i = left - 1;
	for (int j = left; j < right; ++j) {
		if (std::abs(numbers[j]) >= x) {
			++i;
			float temp;
			temp = numbers[i];
			numbers[i] = numbers[j];
			numbers[j] = temp;
		}
	}

	float temp;
	temp = numbers[i+1];
	numbers[i+1] = numbers[right];
	numbers[right] = temp;
	return i+1;
}

int RandomizedPartition(std::vector<float> &numbers, int left, int right) {
	int i = RandInt(right - left + 1) + left;
	float temp;
	temp = numbers[right];
	numbers[right] = numbers[i];
	numbers[i] = temp;
	return Partition(numbers, left, right);
}


float RandomizedSelect(std::vector<float> &numbers, int left, int right, int level) {
	if (left == right) {
		return numbers[left];
	}
	int q = RandomizedPartition(numbers, left, right);
	int k = q - left + 1;
	if (level == k) {
		return numbers[q];
	}
	else if (level < k) {
		return RandomizedSelect(numbers, left, q-1, level);
	}
	else {
		return RandomizedSelect(numbers, q+1, right, level-k);
	}
}