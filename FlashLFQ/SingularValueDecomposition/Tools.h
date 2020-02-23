#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <stdexcept>
#include <optional>
#include "exceptionhelper.h"
#include <type_traits>

// Accord Math Library
// The Accord.NET Framework
// http://accord-framework.net
//
// Copyright © César Souza, 2009-2017
// cesarsouza at gmail.com
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

namespace FlashLFQ
{
    /// <summary>
    ///   Set of mathematical tools.
    /// </summary>
    /// 
    class Tools final {
        
        /// <summary>
        ///   Gets a reference to the random number generator used
        ///   internally by the Accord.NET classes and methods.
        /// </summary>
        /// 
    public:
#ifdef LATER
        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Obsolete("Please use Generator.Random instead.")] public static System.Random Random
        static System::Random *getRandom();
        
        /// <summary>
        ///   Sets a random seed for the framework's main 
        ///   <see cref="Random">internal number generator</see>.
        /// </summary>
        ///
        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Obsolete("Please set the Seed property of Accord.Math.Random.Generator instead.")]
        //public static void SetupGenerator(System.Nullable<int> seed)
        static void SetupGenerator(std::optional<int> &seed);
#endif            
        
        /// <summary>
        ///   Gets the angle formed by the vector [x,y].
        /// </summary>
        /// 
        static float Angle(float x, float y);
        
        /// <summary>
        ///   Gets the angle formed by the vector [x,y].
        /// </summary>
        /// 
        static double Angle(double x, double y);
        
#ifdef LATER
        /// <summary>
        ///   Gets the displacement angle between two points.
        /// </summary>
        /// 
        static double Angle(IntPoint *previous, IntPoint *next);
        
        /// <summary>
        ///   Gets the displacement angle between two points, coded
        ///   as an integer varying from 0 to 20.
        /// </summary>
        /// 
        static int Direction(IntPoint *previous, IntPoint *next);
#endif
        
        /// <summary>
        ///   Gets the greatest common divisor between two integers.
        /// </summary>
        /// 
        /// <param name="a">First value.</param>
        /// <param name="b">Second value.</param>
        /// 
        /// <returns>The greatest common divisor.</returns>
        /// 
        static int GreatestCommonDivisor(int a, int b);
        
        /// <summary>
        ///   Returns the next power of 2 after the input value x.
        /// </summary>
        /// 
        /// <param name="x">Input value x.</param>
        /// 
        /// <returns>Returns the next power of 2 after the input value x.</returns>
        /// 
        static int NextPowerOf2(int x);
        
        /// <summary>
        ///   Returns the previous power of 2 after the input value x.
        /// </summary>
        /// 
        /// <param name="x">Input value x.</param>
        /// 
        /// <returns>Returns the previous power of 2 after the input value x.</returns>
        /// 
        static int PreviousPowerOf2(int x);
        
        
        /// <summary>
        ///   Hypotenuse calculus without overflow/underflow
        /// </summary>
        /// 
        /// <param name="a">First value</param>
        /// <param name="b">Second value</param>
        /// 
        /// <returns>The hypotenuse Sqrt(a^2 + b^2)</returns>
        /// 
        static double Hypotenuse(double a, double b);
        
#ifdef LATER
        /// <summary>
        ///   Hypotenuse calculus without overflow/underflow
        /// </summary>
        /// 
        /// <param name="a">first value</param>
        /// <param name="b">second value</param>
        /// 
        /// <returns>The hypotenuse Sqrt(a^2 + b^2)</returns>
        /// 
        static Decimal Hypotenuse(Decimal a, Decimal b);
#endif
        
        /// <summary>
        ///   Hypotenuse calculus without overflow/underflow
        /// </summary>
        /// 
        /// <param name="a">first value</param>
        /// <param name="b">second value</param>
        /// 
        /// <returns>The hypotenuse Sqrt(a^2 + b^2)</returns>
        /// 
        static float Hypotenuse(float a, float b);
        
        /// <summary>
        ///   Gets the proper modulus operation for
        ///   an integer value x and modulo m.
        /// </summary>
        /// 
        static int Mod(int x, int m);
        
        /// <summary>
        ///   Gets the proper modulus operation for
        ///   a real value x and modulo m.
        /// </summary>
        /// 
        static double Mod(double x, double m);
        
        
#ifdef LATER
        // EDGAR: not needed right now.
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static int Scale(IntRange *from, IntRange *to, int x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static double Scale(DoubleRange *from, DoubleRange *to, double x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static double Scale(double fromMin, double fromMax, double toMin, double toMax, double x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<double> Scale(double fromMin, double fromMax, double toMin, double toMax, std::vector<double> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<int> Scale(int fromMin, int fromMax, int toMin, int toMax, std::vector<int> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<int> Scale(IntRange *from, IntRange *to, std::vector<int> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<double> Scale(DoubleRange *from, DoubleRange *to, std::vector<double> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<float> Scale(float fromMin, float fromMax, float toMin, float toMax, std::vector<float> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<float> Scale(Range *from, Range *to, std::vector<float> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<double> Scale(double toMin, double toMax, std::vector<double> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<std::vector<double>> Scale(std::vector<double> &fromMin, std::vector<double> &fromMax, std::vector<double> &toMin, std::vector<double> &toMax, std::vector<std::vector<double>> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<std::vector<double>> Scale(double fromMin, double fromMax, double toMin, double toMax, std::vector<std::vector<double>> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<std::vector<double>> Scale(std::vector<double> &fromMin, std::vector<double> &fromMax, double toMin, double toMax, std::vector<std::vector<double>> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<std::vector<double>> Scale(std::vector<double> &toMin, std::vector<double> &toMax, std::vector<std::vector<double>> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static std::vector<std::vector<double>> Scale(double toMin, double toMax, std::vector<std::vector<double>> &x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static float Scale(float fromMin, float fromMax, float toMin, float toMax, float x);
        
        /// <summary>
        ///   Converts the value x (which is measured in the scale
        ///   'from') to another value measured in the scale 'to'.
        /// </summary>
        /// 
        static double Scale(IntRange *from, DoubleRange *to, int x);
#endif
        
        /// <summary>
        ///   Returns the hyperbolic arc cosine of the specified value.
        /// </summary>
        /// 
        static double Acosh(double x);
        
        /// <summary>
        /// Returns the hyperbolic arc sine of the specified value.
        /// </summary>
        /// 
        static double Asinh(double d);
        
        /// <summary>
        /// Returns the hyperbolic arc tangent of the specified value.
        /// </summary>
        /// 
        static double Atanh(double d);
        
        
        
        /// <summary>
        ///   Returns the factorial falling power of the specified value.
        /// </summary>
        /// 
        static int FactorialPower(int value, int degree);
        
        /// <summary>
        ///   Truncated power function.
        /// </summary>
        /// 
        static double TruncatedPower(double value, double degree);
        
        /// <summary>
        ///   Fast inverse floating-point square root.
        /// </summary>
        ///
        static float InvSqrt(float f);
        
#ifdef LATER        
        /// <summary>
        ///   Sorts the elements of an entire one-dimensional array using the given comparison.
        /// </summary>
        /// 
        template<typename T>
            static void StableSort(std::vector<T> &values, Comparison<T> comparison) {
            Vector::Sort(values, comparison, true);
        }
        
        /// <summary>
        ///   Sorts the elements of an entire one-dimensional array using the given comparison.
        /// </summary>
        /// 
        template<typename T>
            static void StableSort(std::vector<T> &values)
        {
            static_assert(std::is_base_of<IComparable<T>, T>::value, "T must inherit from IComparable<T>");
            Vector::Sort(values, true);
        }
        
        /// <summary>
        ///   Sorts the elements of an entire one-dimensional array using the given comparison.
        /// </summary>
        /// 
        template<typename T>
            static void StableSort(std::vector<T> &values, std::vector<int> &order)
        {
            static_assert(std::is_base_of<IComparable<T>, T>::value, "T must inherit from IComparable<T>");
            Vector::Sort(values, order, true);
        }
#endif        
        /// <summary>
        ///   Interpolates data using a piece-wise linear function.
        /// </summary>
        /// 
        /// <param name="value">The value to be calculated.</param>
        /// <param name="x">The input data points <c>x</c>. Those values need to be sorted.</param>
        /// <param name="y">The output data points <c>y</c>.</param>
        /// <param name="lower">
        ///   The value to be returned for values before the first point in <paramref name="x"/>.</param>
        /// <param name="upper">
        ///   The value to be returned for values after the last point in <paramref name="x"/>.</param>
        ///   
        /// <returns>Computes the output for f(value) by using a piecewise linear
        ///   interpolation of the data points <paramref name="x"/> and <paramref name="y"/>.</returns>
        /// 
        static double Interpolate1D(double value, std::vector<double> &x, std::vector<double> &y, double lower, double upper);
        
        /// <summary>
        ///   Gets the maximum value among three values.
        /// </summary>
        /// 
        /// <param name="a">The first value <c>a</c>.</param>
        /// <param name="b">The second value <c>b</c>.</param>
        /// <param name="c">The third value <c>c</c>.</param>
        /// 
        /// <returns>The maximum value among <paramref name="a"/>, 
        ///   <paramref name="b"/> and <paramref name="c"/>.</returns>
        /// 
        static double Max(double a, double b, double c);
        
        /// <summary>
        ///   Gets the minimum value among three values.
        /// </summary>
        /// 
        /// <param name="a">The first value <c>a</c>.</param>
        /// <param name="b">The second value <c>b</c>.</param>
        /// <param name="c">The third value <c>c</c>.</param>
        /// 
        /// <returns>The minimum value among <paramref name="a"/>, 
        ///   <paramref name="b"/> and <paramref name="c"/>.</returns>
        /// 
        static double Min(double a, double b, double c);
        
        /// <summary>
        /// Calculates power of 2.
        /// </summary>
        /// 
        /// <param name="power">Power to raise in.</param>
        /// 
        /// <returns>Returns specified power of 2 in the case if power is in the range of
        /// [0, 30]. Otherwise returns 0.</returns>
        /// 
        static int Pow2(int power);
        
        /// <summary>
        /// Checks if the specified integer is power of 2.
        /// </summary>
        /// 
        /// <param name="x">Integer number to check.</param>
        /// 
        /// <returns>Returns <b>true</b> if the specified number is power of 2.
        /// Otherwise returns <b>false</b>.</returns>
        /// 
        static bool IsPowerOf2(int x);
        
        /// <summary>
        /// Get base of binary logarithm.
        /// </summary>
        /// 
        /// <param name="x">Source integer number.</param>
        /// 
        /// <returns>Power of the number (base of binary logarithm).</returns>
        /// 
        static int Log2(int x);
        
#ifdef LATER
        /// <summary>
        ///   Returns the square root of the specified <see cref="decimal"/> number.
        /// </summary>
        /// 
        static Decimal Sqrt(Decimal x, Decimal epsilon = 0.0);
#endif
    };
}

//Helper class added by C# to C++ Converter:

#include <exception>

class ArgumentOutOfRangeException : public std::exception
{
private:
    std::string msg;
    
public:
ArgumentOutOfRangeException(const std::string& message = "") : msg(message)
    {
    }
    
    const char * what() const throw()
    {
        return msg.c_str();
    }
};

