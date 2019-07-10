#pragma once

#include <cmath>
#include <vector>
#include <iostream>

class Math {
public:
    static double Round(double myNumber, int places)
    {
        double nm;
        nm = (floor((static_cast<double>(myNumber*pow(10,places))+.5))/pow(10,places));
        return nm;
    }

    static double StandardDeviation(std::vector<double> samples)
    {
        return sqrt(Variance(samples));
    }

    static double Variance(std::vector<double> samples)
    {
        int size = samples.size();
        
        double variance = 0;
        double t = samples[0];
        for (int i = 1; i < size; i++)
        {
            t += samples[i];
            double diff = ((i + 1) * samples[i]) - t;
            variance += (diff * diff) / ((i + 1.0) *i);
        }
        
        return variance / (size - 1);
    }

    static double Quantile ( std::vector<double> vec, double quantile ) {
        double val = (double) 0.0;
        std::cout << " Math::Quantile: function is not correctly implemented. Please revisit if nevessary" << std::endl;
        return val;
    }

    static  std::vector<double> BoxCarSmooth ( std::vector<double> vec, int points) {
        std::vector<double> *d = new std::vector<double>();
        std::cout << " Math::BoxCarSmooth: function is not correctly implemented. Please revisit if nevessary" << std::endl;
        return *d;
    }
};
