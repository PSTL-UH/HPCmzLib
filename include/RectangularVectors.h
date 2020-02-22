//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2018 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
class RectangularVectors
{
public:
    static std::vector<std::vector<double>> ReturnRectangularDoubleVector(int size1, int size2)
    {
        std::vector<std::vector<double>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<double>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<double>>> RectangularDoubleVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<double>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<double>>(size2);
            for (int vector2 = 0; vector2 < size2; vector2++)
            {
                newVector[vector1][vector2] = std::vector<double>(size3);
            }
        }

        return newVector;
    }

    static std::vector<std::vector<double>> RectangularDoubleVector(int size1, int size2)
    {
        std::vector<std::vector<double>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<double>(size2);
        }

        return newVector;
    }
};
