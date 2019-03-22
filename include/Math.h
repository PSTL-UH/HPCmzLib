#include <cmath>
#include <vector>

class Math {
public:
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
};
