#pragma once
#include <vector>

namespace FlashLFQ
{

    class Matrix {
    public:
        static std::vector<std::vector<double>> Diagonal(int, int, std::vector<double> matrix);
        static std::vector<std::vector<double>> Transpose (std::vector<std::vector<double>> matrix,
                                                           bool inplace);
        static std::vector<std::vector<double>> Dot ( std::vector<std::vector<double>> matrix, std::vector<std::vector<double>> matrix2);

        static std::vector<double> Dot ( std::vector<std::vector<double>> matrix, std::vector<double> vec);

        static std::vector<double> Dot ( std::vector<double> vec, std::vector<std::vector<double>> matrix);

        static std::vector<std::vector<double>> DotWithDiagonal ( std::vector<std::vector<double>> matrix, std::vector<double> vec);        

        static std::vector<std::vector<double>> DotWithTransposed ( std::vector<std::vector<double>> matrix, std::vector<std::vector<double>> vec);        

    };
}
