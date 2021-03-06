/* This file is part of Into.
 * Copyright (C) Intopii 2013.
 * All rights reserved.
 *
 * Licensees holding a commercial Into license may use this file in
 * accordance with the commercial license agreement. Please see
 * LICENSE.commercial for commercial licensing terms.
 *
 * Alternatively, this file may be used under the terms of the GNU
 * Affero General Public License version 3 as published by the Free
 * Software Foundation. In addition, Intopii gives you special rights
 * to use Into as a part of open source software projects. Please
 * refer to LICENSE.AGPL3 for details.
 */

#ifndef _PIIPRINCIPALCOMPONENTS_H
#define _PIIPRINCIPALCOMPONENTS_H

#include "PiiSvDecomposition.h"

namespace Pii
{
  /**
   * Returns the PCA base vectors for a data set in *X*.
   *
   * Principal component analysis (PCA) produces an orthogonal
   * transformation that transforms the input data to a new coordinate
   * system so that the greatest variance by any projection of the
   * data comes to lie on the first coordinate (called the first
   * principal component), the second greatest variance on the second
   * coordinate, and so on.
   *
   * Given an m-by-n input matrix X in which each of the m rows
   * represents an n-dimensional observation. This function returns a
   * n-by-n matrix V that transforms X into a maximally uncorrelated
   * coordinate system when applied from the left: Y = XV.
   *
   * @param X the input data, stored as rows. The input data must have
   * a zero mean.
   *
   * @param S an optional output parameter that will store the
   * singular values of X as a row vector.
   *
   * @return V, a new orthonormal base represented as row vectors.
   *
   * @see subtractMean()
   */
  template <class Matrix>
  PiiMatrix<typename Matrix::value_type> principalComponents(const Matrix& X,
                                                             PiiMatrix<typename Matrix::value_type>* S = 0)
  {
    // SVD: X = USV' -> X' = VS'U'
    // Y = XV = US
    PiiMatrix<typename Matrix::value_type> matV;
    if (S == 0)
      svDecompose<Matrix>(X, 0, &matV, Pii::SvdFullV);
    else
      *S = svDecompose<Matrix>(X, 0, &matV, Pii::SvdFullV);
    return matV;
  }

  /**
   * Decorrelates a possibly correlated set of data. This function
   * uses PCA to transform the input data set into a maximally
   * uncorrelated data set. The output data will be uncorrelated only
   * if the input data is jointly normally distributed.
   *
   * @param X input data with observation vectors as its rows. Must
   * have zero mean.
   *
   * @return decorrelated data
   *
   * @see subtractMean()
   */
  template <class Matrix> PiiMatrix<typename Matrix::value_type> pcaDecorrelate(const Matrix& X)
  {
    typedef typename Matrix::value_type T;
    PiiMatrix<T> matU;
    // Singular values as a row vector
    PiiMatrix<T> matS = svDecompose(X, &matU, 0, Pii::SvdFullU);
    // Optimized multiplication of U*S (S is diagonal)
    transformRows(matU, matS[0], std::multiplies<T>());
    return matU;
  }
}

#endif //_PIIPRINCIPALCOMPONENTS_H
