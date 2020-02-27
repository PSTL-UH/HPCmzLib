#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>
#include <any>
#include <optional>

#include "RectangularVectors.h"
#include "Matrix.h"

// Accord Math Library
// The Accord.NET Framework
// http://accord-framework.net
//
// Copyright © César Souza, 2009-2017
// cesarsouza at gmail.com
//
// Original work copyright © Lutz Roeder, 2000
//  Adapted from Mapack for .NET, September 2000
//  Adapted from Mapack for COM and Jama routines
//  http://www.aisto.com/roeder/dotnet
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
    namespace Decompositions {

        /// <summary>
        ///   Singular Value Decomposition for a rectangular matrix.
        /// </summary>
        ///
        /// <remarks>
        ///  <para>
        ///      For an m-by-n matrix <c>A</c> with <c>m >= n</c>, the singular value decomposition
        ///   is an m-by-n orthogonal matrix <c>U</c>, an n-by-n diagonal matrix <c>S</c>, and
        ///   an n-by-n orthogonal matrix <c>V</c> so that <c>A = U * S * V'</c>.
        ///   The singular values, <c>sigma[k] = S[k,k]</c>, are ordered so that
        ///   <c>sigma[0] >= sigma[1] >= ... >= sigma[n-1]</c>.</para>
        ///  <para>
        ///   The singular value decomposition always exists, so the constructor will
        ///   never fail. The matrix condition number and the effective numerical
        ///   rank can be computed from this decomposition.</para>
        ///  <para>
        ///   WARNING! Please be aware that if A has less rows than columns, it is better
        ///   to compute the decomposition on the transpose of A and then swap the left
        ///   and right eigenvectors. If the routine is computed on A directly, the diagonal
        ///   of singular values may contain one or more zeros. The identity A = U * S * V'
        ///   may still hold, however. To overcome this problem, pass true to the
        ///   <see cref="SingularValueDecomposition(Double[,], bool, bool, bool)">autoTranspose</see>
        ///   argument of the class constructor.</para>
        ///
        ///  <para>
        ///   This routine computes the economy decomposition of A.</para> 
        /// </remarks>
        /// 


        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Serializable] public sealed class SingularValueDecomposition : ICloneable, ISolverMatrixDecomposition<Double>
        class SingularValueDecomposition final  {
        private:
            std::vector<std::vector<double>> u; // left singular vectors
            std::vector<std::vector<double>> v; // right singular vectors
            std::vector<double> s; // singular values
            int m = 0;
            int n = 0;
            bool swapped = false;
            
            std::vector<int> si; // sorting order
            
            static constexpr double eps = 2 * Constants::DoubleEpsilon;
            static constexpr double tiny = Constants::DoubleSmall;
            
            std::optional<int> rank;
            std::optional<double> determinant;
            std::optional<double> lndeterminant;
            std::optional<double> pseudoDeterminant;
            std::optional<double> lnpseudoDeterminant;
            
            std::vector<std::vector<double>> diagonalMatrix;
            
            /// <summary>
            ///   Returns the condition number <c>max(S) / min(S)</c>.
            /// </summary>
            ///
        public:
            double getCondition() const;
            
            /// <summary>
            ///   Returns the singularity threshold.
            /// </summary>
            ///
            double getThreshold() const;
            
            /// <summary>
            ///   Returns the Two norm.
            /// </summary>
            ///
            double getTwoNorm() const;
            
            /// <summary>
            ///   Returns the effective numerical matrix rank.
            /// </summary>
            ///
            /// <value>Number of non-negligible singular values.</value>
            ///
            int getRank();
            
            /// <summary>
            ///   Gets whether the decomposed matrix is singular.
            /// </summary>
            ///
            bool getIsSingular();
            
            /// <summary>
            ///   Gets the one-dimensional array of singular values.
            /// </summary>        
            ///
            std::vector<double> getDiagonal() const;
            
            /// <summary>
            ///  Returns the block diagonal matrix of singular values.
            /// </summary>        
            ///
            std::vector<std::vector<double>> getDiagonalMatrix();
            
            /// <summary>
            ///   Returns the V matrix of Singular Vectors.
            /// </summary>        
            ///
            std::vector<std::vector<double>> getRightSingularVectors() const;
            
            /// <summary>
            ///   Returns the U matrix of Singular Vectors.
            /// </summary>        
            ///
            std::vector<std::vector<double>> getLeftSingularVectors() const;
            
            /// <summary>
            ///   Returns the ordering in which the singular values have been sorted.
            /// </summary>
            ///
            std::vector<int> getOrdering() const;
            
            /// <summary>
            ///   Returns the absolute value of the matrix determinant.
            /// </summary>
            ///
            double getAbsoluteDeterminant();
            
            /// <summary>
            ///   Returns the log of the absolute value for the matrix determinant.
            /// </summary>
            ///
            double getLogDeterminant();
            
            
            /// <summary>
            ///   Returns the pseudo-determinant for the matrix.
            /// </summary>
            ///
            double getPseudoDeterminant();
            
            /// <summary>
            ///   Returns the log of the pseudo-determinant for the matrix.
            /// </summary>
            ///
            double getLogPseudoDeterminant();
            
            
            /// <summary>
            ///   Constructs a new singular value decomposition.
            /// </summary>
            ///
            /// <param name="value">
            ///   The matrix to be decomposed.</param>
            ///
            SingularValueDecomposition(std::vector<std::vector<double>> &value);
            
            
            /// <summary>
            ///     Constructs a new singular value decomposition.
            /// </summary>
            /// 
            /// <param name="value">
            ///   The matrix to be decomposed.</param>
            /// <param name="computeLeftSingularVectors">
            ///   Pass <see langword="true"/> if the left singular vector matrix U 
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// <param name="computeRightSingularVectors">
            ///   Pass <see langword="true"/> if the right singular vector matrix V
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// 
            SingularValueDecomposition(std::vector<std::vector<double>> &value, bool computeLeftSingularVectors, bool computeRightSingularVectors);

            /// <summary>
            ///   Constructs a new singular value decomposition.
            /// </summary>
            /// 
            /// <param name="value">
            ///   The matrix to be decomposed.</param>
            /// <param name="computeLeftSingularVectors">
            ///   Pass <see langword="true"/> if the left singular vector matrix U 
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// <param name="computeRightSingularVectors">
            ///   Pass <see langword="true"/> if the right singular vector matrix V 
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// <param name="autoTranspose">
            ///   Pass <see langword="true"/> to automatically transpose the value matrix in
            ///   case JAMA's assumptions about the dimensionality of the matrix are violated.
            ///   Pass <see langword="false"/> otherwise. Default is <see langword="false"/>.</param>
            /// 
            SingularValueDecomposition(std::vector<std::vector<double>> &value, bool computeLeftSingularVectors, bool computeRightSingularVectors, bool autoTranspose);

            /// <summary>
            ///   Constructs a new singular value decomposition.
            /// </summary>
            /// 
            /// <param name="value">
            ///   The matrix to be decomposed.</param>
            /// <param name="computeLeftSingularVectors">
            ///   Pass <see langword="true"/> if the left singular vector matrix U 
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// <param name="computeRightSingularVectors">
            ///   Pass <see langword="true"/> if the right singular vector matrix V 
            ///   should be computed. Pass <see langword="false"/> otherwise. Default
            ///   is <see langword="true"/>.</param>
            /// <param name="autoTranspose">
            ///   Pass <see langword="true"/> to automatically transpose the value matrix in
            ///   case JAMA's assumptions about the dimensionality of the matrix are violated.
            ///   Pass <see langword="false"/> otherwise. Default is <see langword="false"/>.</param>
            /// <param name="inPlace">
            ///   Pass <see langword="true"/> to perform the decomposition in place. The matrix
            ///   <paramref name="value"/> will be destroyed in the process, resulting in less
            ///   memory comsumption.</param>
            /// 
            SingularValueDecomposition(std::vector<std::vector<double>> &value, bool computeLeftSingularVectors, bool computeRightSingularVectors, bool autoTranspose, bool inPlace);


            /// <summary>
            ///   Solves a linear equation system of the form AX = B.
            /// </summary>
            /// <param name="value">Parameter B from the equation AX = B.</param>
            /// <returns>The solution X from equation AX = B.</returns>
            std::vector<std::vector<double>> Solve(std::vector<std::vector<double>> &value) ;
            
            /// <summary>
            ///   Solves a linear equation system of the form AX = B.
            /// </summary>
            /// <param name="value">Parameter B from the equation AX = B.</param>
            /// <returns>The solution X from equation AX = B.</returns>
            std::vector<std::vector<double>> SolveTranspose(std::vector<std::vector<double>> &value);
            
            /// <summary>
            ///   Solves a linear equation system of the form AX = B.
            /// </summary>
            /// <param name="value">Parameter B from the equation AX = B.</param>
            /// <returns>The solution X from equation AX = B.</returns>
            std::vector<std::vector<double>> SolveForDiagonal(std::vector<double> &value);
            
            /// <summary>
            ///   Solves a linear equation system of the form xA = b.
            /// </summary>
            /// <param name="value">The b from the equation xA = b.</param>
            ///
            /// <returns>The x from equation Ax = b.</returns>
            ///
            std::vector<double> SolveTranspose(std::vector<double> &value);
            
            /// <summary>
            ///   Solves a linear equation system of the form Ax = b.
            /// </summary>
            /// <param name="value">The b from the equation Ax = b.</param>
            /// <returns>The x from equation Ax = b.</returns>
            std::vector<double> Solve(std::vector<double> &value);
            
            /// <summary>
            ///   Computes the (pseudo-)inverse of the matrix given to the Singular value decomposition.
            /// </summary>
            ///
            std::vector<std::vector<double>> Inverse();
            
            /// <summary>
            ///   Reverses the decomposition, reconstructing the original matrix <c>X</c>.
            /// </summary>
            /// 
            std::vector<std::vector<double>> Reverse();
            
            /// <summary>
            ///   Computes <c>(Xt * X)^1</c> (the inverse of the covariance matrix). This
            ///   matrix can be used to determine standard errors for the coefficients when
            ///   solving a linear set of equations through any of the <see cref="Solve(Double[,])"/>
            ///   methods.
            /// </summary>
            /// 
            std::vector<std::vector<double>> GetInformationMatrix();
            
        private:
            SingularValueDecomposition();
            
            /// <summary>
            ///   Creates a new object that is a copy of the current instance.
            /// </summary>
            /// <returns>
            ///   A new object that is a copy of this instance.
            /// </returns>
            ///
        public:
            std::any Clone();
            
            
        };
    }
}
    
