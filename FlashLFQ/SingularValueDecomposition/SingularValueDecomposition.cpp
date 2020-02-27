#include <iostream>
#include "SingularValueDecomposition.h"
#include "Tools.h"
#include "Matrix.h"

namespace FlashLFQ
{
    namespace Decompositions {
        
        double SingularValueDecomposition::getCondition() const {
            return s[0] / s[std::max(m, n) - 1];
        }
        
        double SingularValueDecomposition::getThreshold() const {
            return Constants::DoubleEpsilon * std::max(m, n) * s[0];
        }
        
        double SingularValueDecomposition::getTwoNorm() const {
            return s[0];
        }
        
        int SingularValueDecomposition::getRank() {
            if (this->rank) {
                return this->rank.value();
            }
            
            double tol = std::max(m, n) * s[0] * eps;
            
            int r = 0;
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (s[i] > tol) {
                    r++;
                }
            }
            
            //C# TO C++ CONVERTER TODO TASK: Comparisons involving nullable type instances will need
            // to be rewritten since comparison rules are different between C++ optional and System.Nullable:
            //return static_cast<int>(this->rank = std::make_optional(r));
            this->rank = std::make_optional(r);
            return rank.value();
        }

        bool SingularValueDecomposition::getIsSingular() {
            return getRank() < std::max(m, n);
        }
        
        std::vector<double> SingularValueDecomposition::getDiagonal() const {
            return this->s;
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::getDiagonalMatrix() {
            if (!this->diagonalMatrix.empty()) {
                return this->diagonalMatrix;
            }
            
            //return diagonalMatrix = Matrix::Diagonal(u.Columns(), v.Columns(), s);
            return diagonalMatrix = Matrix::Diagonal(HelperFunctions::Columns(u),
                                                     HelperFunctions::Columns(v), s);
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::getRightSingularVectors() const {
            return v;
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::getLeftSingularVectors() const {
            return u;
        }
        
        std::vector<int> SingularValueDecomposition::getOrdering() const {
            return si;
        }
        
        double SingularValueDecomposition::getAbsoluteDeterminant()  {
            if (!determinant) {
                double det = 1;
                for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                    det *= s[i];
                }
                determinant = std::make_optional(det);
            }
            
            return determinant.value();
        }
        
        double SingularValueDecomposition::getLogDeterminant()  {
            if (!lndeterminant) {
                double det = 0;
                for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                    det += std::log(static_cast<double>(s[i]));
                }
                lndeterminant = std::make_optional(static_cast<double>(det));
            }
            
            return lndeterminant.value();
        }
        
        double SingularValueDecomposition::getPseudoDeterminant() {
            if (!pseudoDeterminant) {
                double det = 1;
                for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                    if (s[i] != 0) {
                        det *= s[i];
                    }
                }
                pseudoDeterminant = std::make_optional(det);
            }
            
            return pseudoDeterminant.value();
        }
        
        double SingularValueDecomposition::getLogPseudoDeterminant() {
            if (!lnpseudoDeterminant) {
                double det = 0;
                for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                    if (s[i] != 0) {
                        det += std::log(static_cast<double>(s[i]));
                    }
                }
                lnpseudoDeterminant = std::make_optional(static_cast<double>(det));
            }
            
            return lnpseudoDeterminant.value();
        }
        
        SingularValueDecomposition::SingularValueDecomposition(std::vector<std::vector<double>> &value) :
            SingularValueDecomposition(value, true, true) {
        }
        
        SingularValueDecomposition::SingularValueDecomposition(std::vector<std::vector<double>> &value,
                                                               bool computeLeftSingularVectors,
                                                               bool computeRightSingularVectors) :
            SingularValueDecomposition(value, computeLeftSingularVectors, computeRightSingularVectors, false) {
        }

        SingularValueDecomposition::SingularValueDecomposition(std::vector<std::vector<double>> &value,
                                                               bool computeLeftSingularVectors,
                                                               bool computeRightSingularVectors,
                                                               bool autoTranspose) :
            SingularValueDecomposition(value, computeLeftSingularVectors, computeRightSingularVectors, autoTranspose, false) {
        }

        SingularValueDecomposition::SingularValueDecomposition(std::vector<std::vector<double>> &value,
                                                               bool computeLeftSingularVectors,
                                                               bool computeRightSingularVectors,
                                                               bool autoTranspose, bool inPlace) {
            if (value.empty()) {
                throw std::invalid_argument("value");
            }
            
            std::vector<std::vector<double>> *a;

            m = HelperFunctions::Rows(value); // rows
            if (m == 0) {
                throw std::invalid_argument("Matrix does not have any rows.");
            }
            
            n = HelperFunctions::Columns(value); // cols
            if (n == 0) {
                throw std::invalid_argument("Matrix does not have any columns.");
            }
            
            if (m < n) { // Check if we are violating JAMA's assumption
                if (!autoTranspose) { // Yes, check if we should correct it
                    // Warning! This routine is not guaranteed to work when A has less rows
                    //  than columns. If this is the case, you should compute SVD on the
                    //  transpose of A and then swap the left and right eigenvectors.
                    
                    // However, as the solution found can still be useful, the exception below
                    // will not be thrown, and only a warning will be output in the trace.
                    
                    // throw new ArgumentException("Matrix should have more rows than columns.");
                    
                    //Trace::WriteLine("WARNING: Computing SVD on a matrix with more columns than rows.");
                    std::cout << "WARNING: Computing SVD on a matrix with more columns than rows.\n";
                    
                    // Proceed anyway
                    //a = inPlace ? value : value.Copy();
                    if (inPlace) {
                        a = &value;
                    }
                    else {
                        a = new std::vector<std::vector<double>>(value);
                    } 
                }
                else {
                    // Transposing and swapping
                    //a = value.Transpose(inPlace && m == n);
                    a = new std::vector<std::vector<double>>;
                    *a = Matrix::Transpose (value, inPlace && m == n );
                    n = HelperFunctions::Rows(value); // rows
                    m = HelperFunctions::Columns(value); // cols
                    swapped = true;
                    
                    bool aux = computeLeftSingularVectors;
                    computeLeftSingularVectors = computeRightSingularVectors;
                    computeRightSingularVectors = aux;
                }
            }
            else {
                // Input matrix is ok
                //a = inPlace ? value : value.Copy();
                if (inPlace) {
                    a = &value;
                }
                else {
                    a = new std::vector<std::vector<double>>(value);
                } 
            }
            
            
            int nu = std::min(m, n);
            int ni = std::min(m + 1, n);
            s = std::vector<double>(ni);
            u = RectangularVectors::RectangularDoubleVector(m, nu);
            v = RectangularVectors::RectangularDoubleVector(n, n);
            
            std::vector<double> e(n);
            std::vector<double> work(m);
            bool wantu = computeLeftSingularVectors;
            bool wantv = computeRightSingularVectors;
            
            // Will store ordered sequence of indices after sorting.
            si = std::vector<int>(ni);
            for (int i = 0; i < ni; i++) {
                si[i] = i;
            }
            
            
            // Reduce A to bidiagonal form, storing the diagonal elements in s and the super-diagonal elements in e.
            int nct = std::min(m - 1, n);
            int nrt = std::max(0, std::min(n - 2, m));
            int mrc = std::max(nct, nrt);
            
            for (int k = 0; k < mrc; k++) {
                if (k < nct) {
                    // Compute the transformation for the k-th column and place the k-th diagonal in s[k].
                    // Compute 2-norm of k-th column without under/overflow.
                    s[k] = 0;
                    for (int i = k; i < HelperFunctions::Rows(*a); i++) {
                        s[k] = Tools::Hypotenuse(s[k], (*a)[i][k]);
                    }
                    
                    if (s[k] != 0) {
                        if ((*a)[k][k] < 0) {
                            s[k] = -s[k];
                        }
                        
                        for (int i = k; i < HelperFunctions::Rows(*a); i++) {
                            (*a)[i][k] /= s[k];
                        }
                        
                        (*a)[k][k] += 1;
                    }
                    
                    s[k] = -s[k];
                }
                
                for (int j = k + 1; j < n; j++) {
                    if ((k < nct) & (s[k] != 0)) {
                        // Apply the transformation.
                        double t = 0;
                        for (int i = k; i < HelperFunctions::Rows(*a); i++) {
                            t += (*a)[i][k] * (*a)[i][j];
                        }
                        
                        t = -t / (*a)[k][k];
                        
                        for (int i = k; i < HelperFunctions::Rows(*a); i++) {
                            (*a)[i][j] += t * (*a)[i][k];
                        }
                    }
                    
                    // Place the k-th row of A into e for the
                    // subsequent calculation of the row transformation.
                    
                    e[j] = (*a)[k][j];
                }
                
                if (wantu & (k < nct)) {
                    // Place the transformation in U for subsequent back
                    // multiplication.
                    
                    for (int i = k; i < HelperFunctions::Rows(*a); i++) {
                        u[i][k] = (*a)[i][k];
                    }
                }
                
                if (k < nrt) {
                    // Compute the k-th row transformation and place the
                    // k-th super-diagonal in e[k].
                    // Compute 2-norm without under/overflow.
                    e[k] = 0;
                    for (int i = k + 1; i < HelperFunctions::Rows(e); i++) {
                        e[k] = Tools::Hypotenuse(e[k], e[i]);
                    }
                    
                    if (e[k] != 0) {
                        if (e[k + 1] < 0) {
                            e[k] = -e[k];
                        }
                        
                        for (int i = k + 1; i < HelperFunctions::Rows(e); i++) {
                            e[i] /= e[k];
                        }
                        
                        e[k + 1] += 1;
                    }
                    
                    e[k] = -e[k];
                    if ((k + 1 < m) & (e[k] != 0)) {
                        // Apply the transformation.
                        for (int i = k + 1; i < HelperFunctions::Rows(work); i++) {
                            work[i] = 0;
                        }
                        
                        for (int i = k + 1; i < HelperFunctions::Rows(*a); i++) {
                            for (int j = k + 1; j < HelperFunctions::Columns(*a); j++) {
                                work[i] += e[j] * (*a)[i][j];
                            }
                        }
                        
                        for (int j = k + 1; j < n; j++) {
                            double t = -e[j] / e[k + 1];
                            for (int i = k + 1; i < HelperFunctions::Rows(work); i++) {
                                (*a)[i][j] += t * work[i];
                            }
                        }
                    }
                    
                    if (wantv) {
                        // Place the transformation in V for subsequent
                        // back multiplication.
                        
                        for (int i = k + 1; i < HelperFunctions::Rows(v); i++) {
                            v[i][k] = e[i];
                        }
                    }
                }
            }
            
            // Set up the final bidiagonal matrix or order p.
            int p = std::min(n, m + 1);
            if (nct < n) {
                s[nct] = (*a)[nct][nct];
            }
            if (m < p) {
                s[p - 1] = 0;
            }
            if (nrt + 1 < p) {
                e[nrt] = (*a)[nrt][p - 1];
            }
            e[p - 1] = 0;
            
            // If required, generate U.
            if (wantu) {
                for (int j = nct; j < nu; j++) {
                    for (int i = 0; i < HelperFunctions::Rows(u); i++) {
                        u[i][j] = 0;
                    }
                    
                    u[j][j] = 1;
                }
                
                for (int k = nct - 1; k >= 0; k--) {
                    if (s[k] != 0) {
                        for (int j = k + 1; j < nu; j++) {
                            double t = 0;
                            for (int i = k; i < HelperFunctions::Rows(u); i++) {
                                t += u[i][k] * u[i][j];
                            }
                            
                            t = -t / u[k][k];
                            
                            for (int i = k; i < HelperFunctions::Rows(u); i++) {
                                u[i][j] += t * u[i][k];
                            }
                        }
                        
                        for (int i = k; i < HelperFunctions::Rows(u); i++) {
                            u[i][k] = -u[i][k];
                        }
                        
                        u[k][k] = 1 + u[k][k];
                        for (int i = 0; i < k - 1; i++) {
                            u[i][k] = 0;
                        }
                    }
                    else {
                        for (int i = 0; i < HelperFunctions::Rows(u); i++) {
                            u[i][k] = 0;
                        }
                        u[k][k] = 1;
                    }
                }
            }
            
            
            // If required, generate V.
            if (wantv) {
                for (int k = n - 1; k >= 0; k--) {
                    if ((k < nrt) & (e[k] != 0)) {
                        // TODO: The following is a pseudo correction to make SVD
                        //  work on matrices with n > m (less rows than columns).
                        
                        // For the proper correction, compute the decomposition of the
                        //  transpose of A and swap the left and right eigenvectors
                        
                        // Original line:
                        //   for (int j = k + 1; j < nu; j++)
                        // Pseudo correction:
                        //   for (int j = k + 1; j < n; j++)
                        
                        for (int j = k + 1; j < n; j++) { // pseudo-correction
                            double t = 0;
                            for (int i = k + 1; i < HelperFunctions::Rows(v); i++) {
                                t += v[i][k] * v[i][j];
                            }
                            
                            t = -t / v[k + 1][k];
                            for (int i = k + 1; i < HelperFunctions::Rows(v); i++) {
                                v[i][j] += t * v[i][k];
                            }
                        }
                    }
                    
                    for (int i = 0; i < HelperFunctions::Rows(v); i++) {
                        v[i][k] = 0;
                    }
                    v[k][k] = 1;
                }
            }
            
            // Main iteration loop for the singular values.
            
            int pp = p - 1;
            int iter = 0;
            double eps = Constants::DoubleEpsilon;
            while (p > 0) {
                int k, kase;
                
                // Here is where a test for too many iterations would go.
                
                // This section of the program inspects for
                // negligible elements in the s and e arrays.  On
                // completion the variables kase and k are set as follows.
                
                // kase = 1     if s(p) and e[k-1] are negligible and k<p
                // kase = 2     if s(k) is negligible and k<p
                // kase = 3     if e[k-1] is negligible, k<p, and
                //              s(k), ..., s(p) are not negligible (qr step).
                // kase = 4     if e(p-1) is negligible (convergence).
                
                for (k = p - 2; k >= -1; k--) {
                    if (k == -1) {
                        break;
                    }
                    
                    auto alpha = tiny + eps * (std::abs(s[k]) + std::abs(s[k + 1]));
                    if (std::abs(e[k]) <= alpha || std::isnan(e[k])) {
                        e[k] = 0;
                        break;
                    }
                }
                
                if (k == p - 2) {
                    kase = 4;
                }
                
                else {
                    int ks;
                    for (ks = p - 1; ks >= k; ks--) {
                        if (ks == k) {
                            break;
                        }
                        
                        double t = (ks != p ? std::abs(e[ks]) : static_cast<double>(0)) +
                            (ks != k + 1 ? std::abs(e[ks - 1]) : static_cast<double>(0));
                        
                        if (std::abs(s[ks]) <= eps * t) {
                            s[ks] = 0;
                            break;
                        }
                    }
                    
                    if (ks == k) {
                        kase = 3;
                    }
                    
                    else if (ks == p - 1) {
                        kase = 1;
                    }
                    
                    else {
                        kase = 2;
                        k = ks;
                    }
                }
                
                k++;
                
                // Perform the task indicated by kase.
                switch (kase) {
                    // Deflate negligible s(p).
                    case 1: {
                        double f = e[p - 2];
                        e[p - 2] = 0;
                        for (int j = p - 2; j >= k; j--) {
                            double t = Tools::Hypotenuse(s[j],f);
                            double cs = s[j] / t;
                            double sn = f / t;
                            s[j] = t;
                            if (j != k) {
                                f = -sn * e[j - 1];
                                e[j - 1] = cs * e[j - 1];
                            }
                            if (wantv) {
                                for (int i = 0; i < HelperFunctions::Rows(v); i++) {
                                    t = cs * v[i][j] + sn * v[i][p - 1];
                                    v[i][p - 1] = -sn * v[i][j] + cs * v[i][p - 1];
                                    v[i][j] = t;
                                }
                            }
                        }
                    }
                        break;
                        
                        // Split at negligible s(k).
                        
                    case 2: {
                        double f = e[k - 1];
                        e[k - 1] = 0;
                        for (int j = k; j < p; j++) {
                            double t = Tools::Hypotenuse(s[j], f);
                            double cs = s[j] / t;
                            double sn = f / t;
                            s[j] = t;
                            f = -sn * e[j];
                            e[j] = cs * e[j];
                            if (wantu) {
                                for (int i = 0; i < HelperFunctions::Rows(u); i++) {
                                    t = cs * u[i][j] + sn * u[i][k - 1];
                                    u[i][k - 1] = -sn * u[i][j] + cs * u[i][k - 1];
                                    u[i][j] = t;
                                }
                            }
                        }
                    }
                        break;
                        
                        // Perform one qr step.
                    case 3: {
                        // Calculate the shift.
                        double scale = std::max(std::max(std::max(std::max(std::abs(s[p - 1]), std::abs(s[p - 2])),
                                                                  std::abs(e[p - 2])), std::abs(s[k])),std::abs(e[k]));
                        double sp = s[p - 1] / scale;
                        double spm1 = s[p - 2] / scale;
                        double epm1 = e[p - 2] / scale;
                        double sk = s[k] / scale;
                        double ek = e[k] / scale;
                        double b = ((spm1 + sp) * (spm1 - sp) + epm1 * epm1) / 2;
                        double c = (sp * epm1) * (sp * epm1);
                        double shift = 0;
                        if ((b != 0) || (c != 0)) {
                            if (b < 0) {
                                shift = -static_cast<double>(std::sqrt(b * b + c));
                            }
                            else {
                                shift = static_cast<double>(std::sqrt(b * b + c));
                            }
                            shift = c / (b + shift);
                        }
                        
                        double f = (sk + sp) * (sk - sp) + static_cast<double>(shift);
                        double g = sk * ek;
                        
                        // Chase zeros.
                        for (int j = k; j < p - 1; j++) {
                            double t = Tools::Hypotenuse(f, g);
                            double cs = f / t;
                            double sn = g / t;
                            
                            if (j != k) {
                                e[j - 1] = t;
                            }
                            
                            f = cs * s[j] + sn * e[j];
                            e[j] = cs * e[j] - sn * s[j];
                            g = sn * s[j + 1];
                            s[j + 1] = cs * s[j + 1];
                            
                            if (wantv) {
                                for (int i = 0; i < HelperFunctions::Rows(v); i++) {
                                    t = cs * v[i][j] + sn * v[i][j + 1];
                                    v[i][j + 1] = -sn * v[i][j] + cs * v[i][j + 1];
                                    v[i][j] = t;
                                }
                            }
                            
                            t = Tools::Hypotenuse(f,g);
                            cs = f / t;
                            sn = g / t;
                            s[j] = t;
                            f = cs * e[j] + sn * s[j + 1];
                            s[j + 1] = -sn * e[j] + cs * s[j + 1];
                            g = sn * e[j + 1];
                            e[j + 1] = cs * e[j + 1];
                            
                            if (wantu && (j < m - 1)) {
                                for (int i = 0; i < HelperFunctions::Rows(u); i++) {
                                    t = cs * u[i][j] + sn * u[i][j + 1];
                                    u[i][j + 1] = -sn * u[i][j] + cs * u[i][j + 1];
                                    u[i][j] = t;
                                }
                            }
                        }
                        
                        e[p - 2] = f;
                        iter = iter + 1;
                    }
                        break;
                        
                        // Convergence.
                    case 4: {
                        // Make the singular values positive.
                        if (s[k] <= 0) {
                            s[k] = (s[k] < 0 ? -s[k] : static_cast<double>(0));
                            
                            if (wantv) {
                                for (int i = 0; i <= pp; i++) {
                                    v[i][k] = -v[i][k];
                                }
                            }
                        }
                        
                        // Order the singular values.
                        while (k < pp) {
                            if (s[k] >= s[k + 1]) {
                                break;
                            }
                            
                            double t = s[k];
                            s[k] = s[k + 1];
                            s[k + 1] = t;
                            if (wantv && (k < n - 1)) {
                                for (int i = 0; i < n; i++) {
                                    t = v[i][k + 1];
                                    v[i][k + 1] = v[i][k];
                                    v[i][k] = t;
                                }
                            }
                            
                            if (wantu && (k < m - 1)) {
                                for (int i = 0; i < HelperFunctions::Rows(u); i++) {
                                    t = u[i][k + 1];
                                    u[i][k + 1] = u[i][k];
                                    u[i][k] = t;
                                }
                            }
                            
                            k++;
                        }
                        
                        iter = 0;
                        p--;
                    }
                        break;
                }
            }
            
            
            // If we are violating JAMA's assumption about 
            // the input dimension, we need to swap u and v.
            if (swapped) {
                auto temp = this->u;
                this->u = this->v;
                this->v = temp;
            }
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::Solve(std::vector<std::vector<double>> &value) {
            // Additionally an important property is that if there does not exists a solution
            // when the matrix A is singular but replacing 1/Li with 0 will provide a solution
            // that minimizes the residue |AX -Y|. SVD finds the least squares best compromise
            // solution of the linear equation system. Interestingly SVD can be also used in an
            // over-determined system where the number of equations exceeds that of the parameters.
            
            // L is a diagonal matrix with non-negative matrix elements having the same
            // dimension as A, Wi ? 0. The diagonal elements of L are the singular values of matrix A.
            
            std::vector<std::vector<double>> Y = value;
            
            // Create L*, which is a diagonal matrix with elements
            //    L*[i] = 1/L[i]  if L[i] < e, else 0, 
            // where e is the so-called singularity threshold.
            
            // In other words, if L[i] is zero or close to zero (smaller than e),
            // one must replace 1/L[i] with 0. The value of e depends on the precision
            // of the hardware. This method can be used to solve linear equations
            // systems even if the matrices are singular or close to singular.
            
            //singularity threshold
            double e = this->getThreshold();
            
            
            int scols = HelperFunctions::Rows(s);

            auto Ls = RectangularVectors::RectangularDoubleVector(scols, scols);
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (std::abs(s[i]) <= e) {
                    Ls[i][i] = 0;
                }
                else {
                    Ls[i][i] = 1 / s[i];
                }
            }
            
            //(V x L*) x Ut x Y
            std::vector<std::vector<double>> VL = Matrix::Dot(v, Ls);
            
            //(V x L* x Ut) x Y
            int vrows = HelperFunctions::Rows(v);
            int urows = HelperFunctions::Rows(u);
            int ucols = HelperFunctions::Columns(u);

            auto VLU = RectangularVectors::RectangularDoubleVector(vrows, urows);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < ucols; k++) {
                        sum += VL[i][k] * u[j][k];
                    }
                    VLU[i][j] = sum;
                }
            }
            
            //(V x L* x Ut x Y)
            return Matrix::Dot(VLU, Y);
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::SolveTranspose(std::vector<std::vector<double>> &value) {
            // Additionally an important property is that if there does not exists a solution
            // when the matrix A is singular but replacing 1/Li with 0 will provide a solution
            // that minimizes the residue |AX -Y|. SVD finds the least squares best compromise
            // solution of the linear equation system. Interestingly SVD can be also used in an
            // over-determined system where the number of equations exceeds that of the parameters.
            
            // L is a diagonal matrix with non-negative matrix elements having the same
            // dimension as A, Wi ? 0. The diagonal elements of L are the singular values of matrix A.
            
            std::vector<std::vector<double>> Y = value;
            
            // Create L*, which is a diagonal matrix with elements
            //    L*[i] = 1/L[i]  if L[i] < e, else 0, 
            // where e is the so-called singularity threshold.
            
            // In other words, if L[i] is zero or close to zero (smaller than e),
            // one must replace 1/L[i] with 0. The value of e depends on the precision
            // of the hardware. This method can be used to solve linear equations
            // systems even if the matrices are singular or close to singular.
            
            //singularity threshold
            double e = this->getThreshold();
            
            
            int scols = HelperFunctions::Rows(s);

            auto Ls = RectangularVectors::RectangularDoubleVector(scols, scols);
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (std::abs(s[i]) <= e) {
                    Ls[i][i] = 0;
                }
                else {
                    Ls[i][i] = 1 / s[i];
                }
            }
            
            //(V x L*) x Ut x Y
            auto VL = Matrix::Dot(v, Ls);
            
            //(V x L* x Ut) x Y
            int vrows = HelperFunctions::Rows(v);
            int urows = HelperFunctions::Rows(u);

            auto VLU = RectangularVectors::RectangularDoubleVector(vrows, scols);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < urows; k++) {
                        sum += VL[i][k] * u[j][k];
                    }
                    VLU[i][j] = sum;
                }
            }
            
            return Matrix::Dot(Y, VLU);
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::SolveForDiagonal(std::vector<double> &value) {
            // Additionally an important property is that if there does not exists a solution
            // when the matrix A is singular but replacing 1/Li with 0 will provide a solution
            // that minimizes the residue |AX -Y|. SVD finds the least squares best compromise
            // solution of the linear equation system. Interestingly SVD can be also used in an
            // over-determined system where the number of equations exceeds that of the parameters.
            
            // L is a diagonal matrix with non-negative matrix elements having the same
            // dimension as A, Wi ? 0. The diagonal elements of L are the singular values of matrix A.
            
            std::vector<double> Y = value;
            
            // Create L*, which is a diagonal matrix with elements
            //    L*[i] = 1/L[i]  if L[i] < e, else 0, 
            // where e is the so-called singularity threshold.
            
            // In other words, if L[i] is zero or close to zero (smaller than e),
            // one must replace 1/L[i] with 0. The value of e depends on the precision
            // of the hardware. This method can be used to solve linear equations
            // systems even if the matrices are singular or close to singular.
            
            //singularity threshold
            double e = this->getThreshold();
            
            
            int scols = HelperFunctions::Rows(s);

            auto Ls = RectangularVectors::RectangularDoubleVector(scols, scols);
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (std::abs(s[i]) <= e) {
                    Ls[i][i] = 0;
                }
                else {
                    Ls[i][i] = 1 / s[i];
                }
            }
            
            //(V x L*) x Ut x Y
            std::vector<std::vector<double>> VL = Matrix::Dot(v, Ls);
            
            //(V x L* x Ut) x Y
            int vrows = HelperFunctions::Rows(v);
            int urows = HelperFunctions::Rows(u);

            auto VLU = RectangularVectors::RectangularDoubleVector(vrows, scols);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < urows; k++) {
                        sum += VL[i][k] * u[j][k];
                    }
                    VLU[i][j] = sum;
                }
            }
            
            //(V x L* x Ut x Y)
            return Matrix::DotWithDiagonal(VLU, Y);
        }
        
        std::vector<double> SingularValueDecomposition::SolveTranspose(std::vector<double> &value) {
            // Additionally an important property is that if there does not exists a solution
            // when the matrix A is singular but replacing 1/Li with 0 will provide a solution
            // that minimizes the residue |AX -Y|. SVD finds the least squares best compromise
            // solution of the linear equation system. Interestingly SVD can be also used in an
            // over-determined system where the number of equations exceeds that of the parameters.
            
            // L is a diagonal matrix with non-negative matrix elements having the same
            // dimension as A, Wi ? 0. The diagonal elements of L are the singular values of matrix A.
            
            std::vector<double> Y = value;
            
            // Create L*, which is a diagonal matrix with elements
            //    L*[i] = 1/L[i]  if L[i] < e, else 0, 
            // where e is the so-called singularity threshold.
            
            // In other words, if L[i] is zero or close to zero (smaller than e),
            // one must replace 1/L[i] with 0. The value of e depends on the precision
            // of the hardware. This method can be used to solve linear equations
            // systems even if the matrices are singular or close to singular.
            
            //singularity threshold
            double e = this->getThreshold();
            
            
            int scols = HelperFunctions::Rows(s);

            auto Ls = RectangularVectors::RectangularDoubleVector(scols, scols);
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (std::abs(s[i]) <= e) {
                    Ls[i][i] = 0;
                }
                else {
                    Ls[i][i] = 1 / s[i];
                }
            }
            
            //(V x L*) x Ut x Y
            std::vector<std::vector<double>> VL = Matrix::Dot(v, Ls);
            
            //(V x L* x Ut) x Y
            int vrows = HelperFunctions::Rows(v);
            int urows = HelperFunctions::Rows(u);

            auto VLU = RectangularVectors::RectangularDoubleVector(vrows, scols);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < urows; k++) {
                        sum += VL[i][k] * u[j][k];
                    }
                    VLU[i][j] = sum;
                }
            }
            
            //return Y.Dot(VLU);
            return Matrix::Dot(Y, VLU);
        }
        
        std::vector<double> SingularValueDecomposition::Solve(std::vector<double> &value) {
            // Additionally an important property is that if there does not exists a solution
            // when the matrix A is singular but replacing 1/Li with 0 will provide a solution
            // that minimizes the residue |AX -Y|. SVD finds the least squares best compromise
            // solution of the linear equation system. Interestingly SVD can be also used in an
            // over-determined system where the number of equations exceeds that of the parameters.
            
            // L is a diagonal matrix with non-negative matrix elements having the same
            // dimension as A, Wi ? 0. The diagonal elements of L are the singular values of matrix A.
            
            //singularity threshold
            double e = this->getThreshold();
            
            auto Y = value;
            
            // Create L*, which is a diagonal matrix with elements
            //    L*i = 1/Li  if Li = e, else 0, 
            // where e is the so-called singularity threshold.
            
            // In other words, if Li is zero or close to zero (smaller than e),
            // one must replace 1/Li with 0. The value of e depends on the precision
            // of the hardware. This method can be used to solve linear equations
            // systems even if the matrices are singular or close to singular.
            
            
            int scols = HelperFunctions::Rows(s);
            
            auto Ls = RectangularVectors::RectangularDoubleVector(scols, scols);
            for (int i = 0; i < HelperFunctions::Rows(s); i++) {
                if (std::abs(s[i]) <= e) {
                    Ls[i][i] = 0;
                }
                else {
                    Ls[i][i] = 1 / s[i];
                }
            }
            
            //(V x L*) x Ut x Y
            auto VL = Matrix::Dot(v, Ls);
            
            //(V x L* x Ut) x Y
            int urows = HelperFunctions::Rows(u);
            int vrows = HelperFunctions::Rows(v);

            auto VLU = RectangularVectors::RectangularDoubleVector(vrows, urows);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < scols; k++) {
                        sum += VL[i][k] * u[j][k];
                    }
                    VLU[i][j] = sum;
                }
            }
            
            //(V x L* x Ut x Y)
            return Matrix::Dot(VLU, Y);
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::Inverse() {
            double e = this->getThreshold();
            
            // X = V*S^-1
            int vrows = HelperFunctions::Rows(v);
            int vcols = HelperFunctions::Columns(v);

            auto X = RectangularVectors::RectangularDoubleVector(vrows, HelperFunctions::Rows(s));
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < vcols; j++) {
                    if (std::abs(s[j]) > e) {
                        X[i][j] = v[i][j] / s[j];
                    }
                }
            }
            
            // Y = X*U'
            int urows = HelperFunctions::Rows(u);
            int ucols = HelperFunctions::Columns(u);

            auto Y = RectangularVectors::RectangularDoubleVector(vrows, urows);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < urows; j++) {
                    double sum = 0;
                    for (int k = 0; k < ucols; k++) {
                        sum += X[i][k] * u[j][k];
                    }
                    Y[i][j] = sum;
                }
            }
            
            return Y;
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::Reverse() {
            //return getLeftSingularVectors().Dot(getDiagonalMatrix()).DotWithTransposed(getRightSingularVectors());
            auto mat = getDiagonalMatrix();
            auto mat2 = getRightSingularVectors();
            auto mat3 = Matrix::DotWithTransposed(mat, mat2);
            auto mat4 = getLeftSingularVectors();
            return Matrix::Dot(mat4, mat3 );
        }
        
        std::vector<std::vector<double>> SingularValueDecomposition::GetInformationMatrix() {
            double e = this->getThreshold();
            
            // X = V*S^-1
            int vrows = HelperFunctions::Rows(v);
            int vcols = HelperFunctions::Columns(v);

            auto X = RectangularVectors::RectangularDoubleVector(vrows, HelperFunctions::Rows(s));
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < vcols; j++) {
                    if (std::abs(s[j]) > e) {
                        X[i][j] = v[i][j] / s[j];
                    }
                }
            }
            
            // Y = X*V'

            auto Y = RectangularVectors::RectangularDoubleVector(vrows, vrows);
            for (int i = 0; i < vrows; i++) {
                for (int j = 0; j < vrows; j++) {
                    double sum = 0;
                    for (int k = 0; k < vrows; k++) {
                        sum += X[i][k] * v[j][k];
                    }
                    Y[i][j] = sum;
                }
            }
            
            return Y;
        }
        
        SingularValueDecomposition::SingularValueDecomposition() {
        }
        
        std::any SingularValueDecomposition::Clone() {
            auto svd = new SingularValueDecomposition();
            svd->m = m;
            svd->n = n;
            //svd->s = static_cast<std::vector<double>>(s.Clone());
            svd->s = s;
            //svd->si = static_cast<std::vector<int>>(si.Clone());
            svd->si = si;
            
            svd->swapped = swapped;
            if (!u.empty()) {
                //svd->u = static_cast<std::vector<std::vector<double>>>(u.MemberwiseClone());
                svd->u = u;
            }
            if (!v.empty()) {
                //svd->v = static_cast<std::vector<std::vector<double>>>(v.MemberwiseClone());
                svd->v = v;
            }
            
            return svd;
        }
    }
    
}
