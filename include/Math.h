#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <numeric>
#include <limits>

#include "Quantiles.h"

class Math {
public:
    template <typename T>
        static void Clear (std::vector<T> &array, int index, int length)    
    {
        for ( int i=index; i<length; i++ ) {
            array[i] = static_cast<T>(0);
        }
        
        return;
    }

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

    static double PopulationStandardDeviation(std::vector<double> samples)
    {
        std::cout << "PopulationStandardDeviation: Normalization not yet implemented correctly. Using StandardDeviation\n";
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
        
        //return NaN if array is empty
        if (vec.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        //If array contains only one value, return that value
        if (1 == vec.size()) {
            return vec[0];
        }

        //Otherwise compute quantile value as follows:
        //n = sample size = array size
        auto n = vec.size();

        //quantile = quantile selector
        //m = (quantile + 1)/3
        double m = (quantile + 1) / 3;

        //j = floor((n * quantile) + m)
        int j = (int)floor((n * quantile) + m);

        //gamma = (n * quantile) + m - j
        double gamma = (n * quantile) + m - j;

        //quantile = (1 - gamma)*x_j + gamma*x_(j+1)
        //Here x_j is the "jth order statistic" and x_(j+1) is the "(j+1)th order statistic"
        //Because the array begins with index 0, these values correspond to array[j-1] and 
        //array[j] respectively. 
        double value = (((1 - gamma) * vec[j - 1]) + (gamma * vec[j]));
        return value;
    }

    static  std::vector<double> BoxCarSmooth ( std::vector<double> vec, int points) {
        std::vector<double> *d = new std::vector<double>();
        std::cout << " Math::BoxCarSmooth: function is not correctly implemented. Please revisit if nevessary" << std::endl;
        return *d;
    }

    static double GammaLowerRegularized(double globalMeanCount, double score )
    {
        double ret = 0.0;
        std::cout << " Math::GammaLowerRegularized: function is not correctly implemented. Please revisit if nevessary" << std::endl;
        return ret;
    }

    static double Mean ( std::vector<double> samples )
    {
        if (samples.empty())
            return std::numeric_limits<double>::quiet_NaN();

        return std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
    }

    static double Median ( std::vector<double> samples )
    {
        if (samples.empty())
            return std::numeric_limits<double>::quiet_NaN();

        std::sort(samples.begin(), samples.end());
        return  samples[samples.size()/2];
    }

    static double InterquartileRange ( std::vector<double> samples )
    {
        if (samples.empty())
            return std::numeric_limits<double>::quiet_NaN();

        std::cout << " Math::InterquartileRange: function is not correctly implemented. Please revisit if necessary" << std::endl;
        return  (double)0.0;
    }

    static double LowerQuartile ( std::vector<double> samples )
    {
        return Measures::LowerQuartile(samples);
    }

    static double UpperQuartile ( std::vector<double> samples )
    {
        return Measures::UpperQuartile(samples);
    }
    
    static double PopulationCovariance ( std::vector<double> &a, std::vector<double> &b)
    {
        std::cout << " Math::PopulationCovariance: function is not correctly implemented. Please revisit if nevessary" << std::endl;
        return  (double)0.0;
    }

    static double PearsonCorrelation ( std::vector<double> &a, std::vector<double> &b ) {
        double p = 0;
        double q = 0;
        double p2 = 0;
        double q2 = 0;
        double sum = 0;

        for (int i = 0; i < (int)a.size(); i++)
        {
            p += a[i];
            q += b[i];
            p2 += a[i] * a[i];
            q2 += b[i] * b[i];
            sum += a[i] * b[i];
        }

        double n = a.size();
        double num = sum - (p * q) / n;
        double den = sqrt((p2 - (p * p) / n) * (q2 - (q * q) / n));

        return (den == 0) ? 0 : num / den;
    }
    
};
