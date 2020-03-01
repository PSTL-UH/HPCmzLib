#pragma once
#include <vector>
#include <iostream>

namespace FlashLFQ
{
    class Constants {
    public:
        static constexpr double DoubleEpsilon = 1.11022302462515654042e-16;
        static constexpr  double DoubleSmall = 1.493221789605150e-300;
    };

    class HelperFunctions {
    public:
        template <typename T>
            static int Rows (std::vector<T> &matrix ) {
            return matrix.size();
        }
        template <typename T>
            static int Rows (std::vector<std::vector<T>> &matrix ) {
            return matrix.size();
        }
        template <typename T>
            static int Columns (std::vector<std::vector<T>> &matrix ) {
            return matrix[0].size();
        }
    };
        

    class Matrix {
    public:
        static std::vector<std::vector<double>> Diagonal(int rows, int cols,
                                                         std::vector<double> &values)
        {
            int size = rows < cols ? rows : cols;

            auto result = RectangularVectors::RectangularDoubleVector(size, size);
            for ( int i = 0; i < size; i++ ) {
                for ( int j = 0; j<size; j++ ) {
                    result[i][j] = 0.0;
                }
            }
            for (int i = 0; i < size; i++)
                result[i][i] = values[i];
            
            return result;
        }
        static std::vector<std::vector<double>> Diagonal( std::vector<double> &values)
        {
            return Diagonal(values.size(), values.size(), values);
        }

        static std::vector<double> Diagonal( std::vector<std::vector<double>> &values)
        {
            std::vector<double>result(values.size());
            for ( int i = 0; i < (int)values.size(); i++ ) {
                result[i] = values[i][i];
            }
            return result;
        }
        static std::vector<std::vector<double>> Transpose (std::vector<std::vector<double>> &matrix,
                                                           bool inplace)
        {
            /// <summary>
            ///   Gets the transpose of a matrix.
            /// </summary>
            /// 
            /// <param name="matrix">A matrix.</param>
            /// 
            /// <param name="inPlace">True to store the transpose over the same input
            ///   <paramref name="matrix"/>, false otherwise. Default is false.</param>
            ///   
            /// <returns>The transpose of the given matrix.</returns>
            /// 
            /// public static T[,] Transpose<T>(this T[,] matrix, bool inPlace)
            
            int rows = HelperFunctions::Rows(matrix);
            int cols = HelperFunctions::Columns(matrix);
            
            if (inplace) {                
                if (rows != cols)
                    throw new std::invalid_argument("Only square matrices can be transposed in place.");
                

                for (int i = 0; i < rows; i++ ) {
                    for (int j = i; j < cols; j++) {
                        double element = matrix[j][i];
                        matrix[j][i] = matrix[i][j];
                        matrix[i][j] = element;
                    }
                }
                return matrix;
            }

            auto result = RectangularVectors::RectangularDoubleVector(cols, rows);
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++) {
                    result[j][i] = matrix[i][j];
                }
            }
                
            return result;
        }

            
        static std::vector<std::vector<double>> Dot ( std::vector<std::vector<double>> &a,
                                                      std::vector<std::vector<double>> &b){
            /// <summary>
            ///   Computes the product <c>R = A*B</c> of two matrices <c>A</c>
            ///   and <c>B</c>, storing the result in matrix <c>R</c>.
            /// </summary>
            /// 
            /// <param name="a">The left matrix <c>A</c>.</param>
            /// <param name="b">The right matrix <c>B</c>.</param>
            /// <param name="result">The matrix <c>R</c> to store the product.</param>
            /// 
            /// public static double[][] Dot(this sbyte[,] a, float[][] b, double[][] result)
            
#if DEBUG
            if (HelperFunctions::Columns(a) != HelperFunctions::Rows(b) )
                throw new DimensionMismatchException();
#endif
            int M = HelperFunctions::Columns(a);
            int N = HelperFunctions::Rows(a);
            auto result= RectangularVectors::RectangularDoubleVector(N, N);

            auto t = new double[M];

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for ( int k =0; k < M; k++ ) {
                        t[k] = b[k][j];
                    }
                    result[i][j] =0.0;
                    for (int k = 0; k < M; k++) {
                        result[i][j] += a[i][k] * t[k];
                    }
                }
            }

            return result;                                
        }
        
        static std::vector<double> Dot ( std::vector<std::vector<double>> &matrix,
                                         std::vector<double> &columnVector){
            /// <summary>
            ///   Multiplies a matrix <c>A</c> and a column vector <c>v</c>,
            ///   giving the product <c>A*v</c>
            /// </summary>
            /// 
            /// <param name="matrix">The matrix <c>A</c>.</param>
            /// <param name="columnVector">The column vector <c>v</c>.</param>
            /// <param name="result">The matrix <c>R</c> to store the product.</param>
            /// 
            /// public static double[] Dot(this sbyte[][] matrix, float[] columnVector, double[] result)
            
#if DEBUG
            if (HelperFunctions::Columns(matrix) != columnVector.size() )
                throw new DimensionMismatchException();
#endif
            std::vector<double> result(matrix.size());
            for (int i = 0; i < (int)matrix.size(); i++)
            {
                double s = 0.0;
                for (int j = 0; j < (int)columnVector.size(); j++)
                    s += matrix[i][j] * columnVector[j];
                result[i] = s;
            }
            return result;
        }
        
    
        static std::vector<double> Dot ( std::vector<double> &rowVector,
                                         std::vector<std::vector<double>> &matrix){
            /// <summary>
            ///   Multiplies a row vector <c>v</c> and a matrix <c>A</c>,
            ///   giving the product <c>v'*A</c>.
            /// </summary>
            /// 
            /// <param name="rowVector">The row vector <c>v</c>.</param>
            /// <param name="matrix">The matrix <c>A</c>.</param>
            /// <param name="result">The matrix <c>R</c> to store the product.</param>
            /// 
            /// public static double[] Dot(this sbyte[] rowVector, float[,] matrix, double[] result)
            
#if DEBUG
            if (rowVector.size != HelperFunctions::Rows(matrix))
                throw new DimensionMismatchException();
#endif
            int cols = HelperFunctions::Columns(matrix);

            std::vector<double> result(cols);
            for (int j = 0; j < cols; j++)
            {
                double s = 0.0;
                for (int k = 0; k < (int)rowVector.size(); k++)
                    s += rowVector[k] * matrix[k][j];
                result[j] = s;
            }
            return result;                
        }

        static double Dot ( std::vector<double> a, std::vector<double> b) {
            double result=0.0;
            std::cout << "Function not yet implemented.\n";
            return result;
        }
        
        static std::vector<std::vector<double>> DotWithDiagonal ( std::vector<std::vector<double>> &a,
                                                                  std::vector<double> &diagonal)
        {
            /// <summary>
            ///   Computes the product A*B of matrix <c>A</c> and diagonal matrix <c>B</c>.
            /// </summary>
            /// 
            /// <param name="a">The left matrix <c>A</c>.</param>
            /// <param name="diagonal">The diagonal vector of right matrix <c>B</c>.</param>
            /// <param name="result">The matrix <c>R</c> to store the product <c>R = A*B</c>
            ///   of the given matrices <c>A</c> and <c>B</c>.</param>
            /// 
            /// public static double[][] DotWithDiagonal(this sbyte[][] a, double[] diagonal, double[][] result)

            int rows = HelperFunctions::Rows(a);
            int size = diagonal.size();
            auto result= RectangularVectors::RectangularDoubleVector(rows, size);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < size; j++ )
                    result[i][j] = a[i][j] * diagonal[j];

            return result;
        }
        
        static std::vector<std::vector<double>> DotWithTransposed ( std::vector<std::vector<double>> &a,
                                                                    std::vector<std::vector<double>> &b)
        {
            auto bdash = Transpose(b, false);
            return Dot ( a, bdash);
        }

    };
}
