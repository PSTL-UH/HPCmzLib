#pragma once
#include <vector>

class BitConverter {
public:
	float toSingle(char *bytes, int index) {
		unsigned char single_precision_char_array[4];
		for (int i = 0; i < 4; i++) {
			single_precision_char_array[i] = bytes[i + index];
		}
		float* f;
		f = (float*)single_precision_char_array;
		return *f;
	}

	double toDouble(char *bytes, int index) {
		unsigned char double_precision_char_array[8];
		for (int i = 0; i < 8; i++) {
			double_precision_char_array[i] = bytes[i + index];
		}
		double* d;
		d = (double*)double_precision_char_array;
		return *d;
	}
};