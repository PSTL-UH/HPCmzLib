#pragma once
#include <vector>
#include <math.h>
#include <limits>
#include <iostream>


template <typename T>
double Quantile(std::vector<T>& array, double tau) {

	//return NaN if array is empty
	if (array.empty()) {
		return std::numeric_limits<double>::quiet_NaN();
	}

	//If array contains only one value, return that value
	if (1 == array.size()) {
		return array[0];
	}

	//Otherwise compute quantile value as follows:
	//n = sample size = array size
	auto n = array.size();

	//tau = quantile selector
	//m = (tau + 1)/3
	double m = (tau + 1) / 3;

	//j = floor((n * tau) + m)
	int j = (int)floor((n * tau) + m);

	//gamma = (n * tau) + m - j
	double gamma = (n * tau) + m - j;

	//quantile = (1 - gamma)*x_j + gamma*x_(j+1)
	//Here x_j is the "jth order statistic" and x_(j+1) is the "(j+1)th order statistic"
	//Because the array begins with index 0, these values correspond to array[j-1] and 
	//array[j] respectively. 
	double quantile = (((1 - gamma) * array[j - 1]) + (gamma * array[j]));
	return quantile;
}