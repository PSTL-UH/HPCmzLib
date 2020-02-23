#include "Tools.h"

namespace FlashLFQ
{
#ifdef LATER        
    System::Random *Tools::getRandom() {
        return Generator->Random;
    }
    
    void Tools::SetupGenerator(std::optional<int> &seed) {
        Generator->Seed = seed;
    }
#endif
    
    float Tools::Angle(float x, float y) {
        if (y >= 0) {
            if (x >= 0) {
                return static_cast<float>(std::atan(y / x));
            }
            return static_cast<float>(M_PI - std::atan(-y / x));
        }
        else {
            if (x >= 0) {
                return static_cast<float>(2 * M_PI - std::atan(-y / x));
            }
            return static_cast<float>(M_PI + std::atan(y / x));
        }
    }
    
    double Tools::Angle(double x, double y) {
        if (y >= 0) {
            if (x >= 0) {
                return std::atan2(y, x);
            }
            return M_PI - std::atan(-y / x);
        }
        else {
            if (x >= 0) {
                return 2.0 * M_PI - std::atan2(-y, x);
            }
            return M_PI + std::atan(y / x);
        }
    }
    
#ifdef LATER
    double Tools::Angle(IntPoint *previous, IntPoint *next) {
        double dx = next->X - previous->X;
        double dy = next->Y - previous->Y;
        
        return Accord::Math::Tools::Angle(dx, dy);
    }
    
    int Tools::Direction(IntPoint *previous, IntPoint *next) {
        double dx = next->X - previous->X;
        double dy = next->Y - previous->Y;
        
        double radians = Accord::Math::Tools::Angle(dx, dy);
        
        // code = Floor(20 / (2*System.Math.PI))
        int code = static_cast<int>(std::floor(radians * 3.183098861837907));
        
        return code;
    }
    
#endif
    
    int Tools::GreatestCommonDivisor(int a, int b) {
        int x = a - b * static_cast<int>(std::floor(a / static_cast<double>(b)));
        while (x != 0) {
            a = b;
            b = x;
            x = a - b * static_cast<int>(std::floor(a / static_cast<double>(b)));
        }
        return b;
    }
    
    int Tools::NextPowerOf2(int x) {
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return ++x;
    }
    
    int Tools::PreviousPowerOf2(int x) {
        return NextPowerOf2(x + 1) / 2;
    }
    
    double Tools::Hypotenuse(double a, double b) {
        double r = 0.0;
        double absA = std::abs(a);
        double absB = std::abs(b);
        
        if (absA > absB) {
            r = b / a;
            r = absA * std::sqrt(1 + r * r);
        }
        else if (b != 0) {
            r = a / b;
            r = absB * std::sqrt(1 + r * r);
        }
        
        return r;
    }
    
#ifdef LATER
    Decimal Tools::Hypotenuse(Decimal a, Decimal b) {
        Decimal r = 0;
        Decimal absA = std::abs(a);
        Decimal absB = std::abs(b);
        
        if (absA > absB) {
            r = b / a;
            r = absA * static_cast<Decimal>(std::sqrt(static_cast<double>(1 + r * r)));
        }
        else if (b != 0) {
            r = a / b;
            r = absB * static_cast<Decimal>(std::sqrt(static_cast<double>(1 + r * r)));
        }
        
        return r;
    }
#endif
    
    float Tools::Hypotenuse(float a, float b) {
        double r = 0;
        float absA = std::abs(a);
        float absB = std::abs(b);
        
        if (absA > absB) {
            r = b / a;
            r = absA * std::sqrt(1 + r * r);
        }
        else if (b != 0) {
            r = a / b;
            r = absB * std::sqrt(1 + r * r);
        }
        
        return static_cast<float>(r);
    }
    
    int Tools::Mod(int x, int m) {
        if (m < 0) {
            m = -m;
        }
        
        int r = x % m;
        
        return r < 0 ? r + m : r;
    }
    
#ifdef LATER
    // EDGAR: As far as I can see, not needed for our purpose.
    double Tools::Mod(double x, double m) {
        if (m < 0) {
            m = -m;
        }
        
        double r = x % m;
        
        return r < 0 ? r + m : r;
    }
    
    int Tools::Scale(IntRange *from, IntRange *to, int x) {
        return Accord::Math::Vector::Scale(x, static_cast<IRange<int>*>(from), static_cast<IRange<int>*>(to));
    }
    
    double Tools::Scale(DoubleRange *from, DoubleRange *to, double x) {
        return Accord::Math::Vector::Scale(x, from, to);
    }
    
    double Tools::Scale(double fromMin, double fromMax, double toMin, double toMax, double x) {
        return Accord::Math::Vector::Scale(x, fromMin, fromMax, toMin, toMax);
    }
    
    std::vector<double> Tools::Scale(double fromMin, double fromMax, double toMin, double toMax, std::vector<double> &x) {
        return Accord::Math::Vector::Scale(x, fromMin, fromMax, toMin, toMax);
    }
    
    std::vector<int> Tools::Scale(int fromMin, int fromMax, int toMin, int toMax, std::vector<int> &x) {
        return Accord::Math::Vector::Scale(x, fromMin, fromMax, toMin, toMax);
    }
    
    std::vector<int> Tools::Scale(IntRange *from, IntRange *to, std::vector<int> &x) {
        return Accord::Math::Vector::Scale(x, static_cast<IRange<int>*>(from), static_cast<IRange<int>*>(to));
    }
    
    std::vector<double> Tools::Scale(DoubleRange *from, DoubleRange *to, std::vector<double> &x) {
        return Accord::Math::Vector::Scale(values: x, fromRange: from, toRange: to);
    }
    
    std::vector<float> Tools::Scale(float fromMin, float fromMax, float toMin, float toMax, std::vector<float> &x) {
        return Accord::Math::Vector::Scale(x, fromMin, fromMax, toMin, toMax);
    }
    
    std::vector<float> Tools::Scale(Range *from, Range *to, std::vector<float> &x) {
        return Accord::Math::Vector::Scale(x, static_cast<IRange<float>*>(from), static_cast<IRange<float>*>(to));
    }
    
    std::vector<double> Tools::Scale(double toMin, double toMax, std::vector<double> &x) {
        return Accord::Math::Vector::Scale(x, toMin, toMax);
    }
    
    std::vector<std::vector<double>> Tools::Scale(std::vector<double> &fromMin, std::vector<double> &fromMax, std::vector<double> &toMin, std::vector<double> &toMax, std::vector<std::vector<double>> &x) {
        int rows = x.size();
        int cols = fromMin.size();
        
        std::vector<std::vector<double>> result(rows);
        for (int i = 0; i < rows; i++) {
            result[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j++) {
                result[i][j] = (toMax[j] - toMin[j]) * (x[i][j] - fromMin[j]) / (fromMax[j] - fromMin[j]) + toMin[j];
            }
        }
        
        return result;
    }
    
    std::vector<std::vector<double>> Tools::Scale(double fromMin, double fromMax, double toMin, double toMax, std::vector<std::vector<double>> &x) {
        int rows = x.size();
        
        std::vector<std::vector<double>> result(rows);
        for (int i = 0; i < rows; i++) {
            result[i] = std::vector<double>(x[i].size());
            for (int j = 0; j < result[i].size(); j++) {
                result[i][j] = (toMax - toMin) * (x[i][j] - fromMin) / (fromMax - fromMin) + toMin;
            }
        }
        
        return result;
    }
    
    std::vector<std::vector<double>> Tools::Scale(std::vector<double> &fromMin, std::vector<double> &fromMax, double toMin, double toMax, std::vector<std::vector<double>> &x) {
        int rows = x.size();
        int cols = fromMin.size();
        
        std::vector<std::vector<double>> result(rows);
        for (int i = 0; i < rows; i++) {
            result[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j++) {
                result[i][j] = (toMax - toMin) * (x[i][j] - fromMin[j]) / (fromMax[j] - fromMin[j]) + toMin;
            }
        }
        
        return result;
    }
    
    std::vector<std::vector<double>> Tools::Scale(std::vector<double> &toMin, std::vector<double> &toMax, std::vector<std::vector<double>> &x) {
        auto min = Matrix::Min(x, 0);
        auto max = Matrix::Max(x, 0);
        return Scale(min, max, toMin, toMax, x);
    }
    
    std::vector<std::vector<double>> Tools::Scale(double toMin, double toMax, std::vector<std::vector<double>> &x) {
        return Scale(Matrix::Min(x, 0), Matrix::Max(x, 0), toMin, toMax, x);
    }
    
    float Tools::Scale(float fromMin, float fromMax, float toMin, float toMax, float x) {
        return Accord::Math::Vector::Scale(x, fromMin, fromMax, toMin, toMax);
    }
    
    double Tools::Scale(IntRange *from, DoubleRange *to, int x) {
        return Accord::Math::Vector::Scale(x, from, to);
    }
#endif
    
    double Tools::Acosh(double x) {
        if (x < 1.0) {
            throw ArgumentOutOfRangeException("x");
        }
        return std::log(x + std::sqrt(x * x - 1));
    }
    
    double Tools::Asinh(double d) {
        double x;
        int sign;
        
        if (d == 0.0) {
            return d;
        }
        
        if (d < 0.0) {
            sign = -1;
            x = -d;
        }
        else {
            sign = 1;
            x = d;
        }
        return sign * std::log(x + std::sqrt(x * x + 1));
    }
    
    double Tools::Atanh(double d) {
        if (d > 1.0 || d < -1.0) {
            throw ArgumentOutOfRangeException("d");
        }
        return 0.5 * std::log((1.0 + d) / (1.0 - d));
    }
    
    int Tools::FactorialPower(int value, int degree) {
        int t = value;
        for (int i = 0; i < degree; i++) {
            t *= degree--;
        }
        return t;
    }
    
    double Tools::TruncatedPower(double value, double degree) {
        double x = std::pow(value, degree);
        return (x > 0) ? x : 0.0;
    }

#ifdef LATER
    float Tools::InvSqrt(float f) {
        //C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
        //        unsafe
        //            {
        //                float xhalf = 0.5f * f;
        //                Int32 i = * (Int32 * ) & f;
        //                i = 0x5f375a86 - (i >> 1);
        //                f = * (float * ) & i;
        //                f = f * (1.5f - xhalf * f * f);
        //                return f;
        //            }
    }
#endif
    
    double Tools::Interpolate1D(double value, std::vector<double> &x, std::vector<double> &y, double lower, double upper) {
        for (int i = 0; i < (int)x.size(); i++) {
            if (value < x[i]) {
                if (i == 0) {
                    return lower;
                }
                
                int start = i - 1;
                int next = i;
                
                double m = (value - x[start]) / (x[next] - x[start]);
                return y[start] + (y[next] - y[start]) * m;
            }
        }
        
        return upper;
    }
    
    double Tools::Max(double a, double b, double c) {
        if (a > b) {
            if (c > a) {
                return c;
            }
            return a;
        }
        else {
            if (c > b) {
                return c;
            }
            return b;
        }
    }
    
    double Tools::Min(double a, double b, double c) {
        if (a < b) {
            if (c < a) {
                return c;
            }
            return a;
        }
        else {
            if (c < b) {
                return c;
            }
            return b;
        }
    }
    
    int Tools::Pow2(int power) {
        return ((power >= 0) && (power <= 30)) ? (1 << power) : 0;
    }
    
    bool Tools::IsPowerOf2(int x) {
        return (x > 0) ? ((x & (x - 1)) == 0) : false;
    }
    
    int Tools::Log2(int x) {
        if (x <= 65536) {
            if (x <= 256) {
                if (x <= 16) {
                    if (x <= 4) {
                        if (x <= 2) {
                            if (x <= 1) {
                                return 0;
                            }
                            return 1;
                        }
                        return 2;
                    }
                    if (x <= 8) {
                        return 3;
                    }
                    return 4;
                }
                if (x <= 64) {
                    if (x <= 32) {
                        return 5;
                    }
                    return 6;
                }
                if (x <= 128) {
                    return 7;
                }
                return 8;
            }
            if (x <= 4096) {
                if (x <= 1024) {
                    if (x <= 512) {
                        return 9;
                    }
                    return 10;
                }
                if (x <= 2048) {
                    return 11;
                }
                return 12;
            }
            if (x <= 16384) {
                if (x <= 8192) {
                    return 13;
                }
                return 14;
            }
            if (x <= 32768) {
                return 15;
            }
            return 16;
        }
        
        if (x <= 16777216) {
            if (x <= 1048576) {
                if (x <= 262144) {
                    if (x <= 131072) {
                        return 17;
                    }
                    return 18;
                }
                if (x <= 524288) {
                    return 19;
                }
                return 20;
            }
            if (x <= 4194304) {
                if (x <= 2097152) {
                    return 21;
                }
                return 22;
            }
            if (x <= 8388608) {
                return 23;
            }
            return 24;
        }
        if (x <= 268435456) {
            if (x <= 67108864) {
                if (x <= 33554432) {
                    return 25;
                }
                return 26;
            }
            if (x <= 134217728) {
                return 27;
            }
            return 28;
        }
        if (x <= 1073741824) {
            if (x <= 536870912) {
                return 29;
            }
            return 30;
        }
        return 31;
    }
    
#ifdef LATER        
    Decimal Tools::Sqrt(Decimal x, Decimal epsilon) {
        if (x < 0) {
            throw std::overflow_error("Cannot calculate square root from a negative number.");
        }
        
        Decimal current = static_cast<Decimal>(std::sqrt(static_cast<double>(x))), previous;
        
        do {
            previous = current;
            if (previous == 0.0) {
                return 0;
            }
            current = (previous + x / previous) / 2;
        } while (std::abs(previous - current) > epsilon);
        
        return current;
    }
#endif
}
