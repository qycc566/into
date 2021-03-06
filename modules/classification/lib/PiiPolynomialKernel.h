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

#ifndef _PIIPOLYNOMIALKERNEL_H
#define _PIIPOLYNOMIALKERNEL_H

/**
 * Polynomial kernel function. The polynomial kernel is defined as
 * \(k(x,y) = (\alpha + \beta \langle x, y \rangle)^d\), where *x*
 * and *y* are vectors of any dimensionality. The user-specified
 * constants of the function can be interpreted as follows:
 *
 * - \(\alpha\) - an offset. Setting this value to 0 (the default)
 * results in a homogeneous polynomial kernel. The offset must be a
 * non-negative value to satisfy Mercer's condition.
 *
 * - \(\beta\) - a scale. This is a convenient way of normalizing
 * the input vectors without actually modifying them.
 *
 * - *d* - the degree of the polynomial, a positive integer.
 *
 */
template <class FeatureIterator> class PiiPolynomialKernel
{
public:
  /**
   * Constructs a new polynomial kernel function.
   */
  PiiPolynomialKernel() : _dAlpha(0), _dBeta(1), _iDegree(2) {}

  /**
   * Sets the value of \(\alpha\) to *offset*. The default value is
   * zero.
   */
  void setOffset(double offset) { _dOffset = offset; }
  /**
   * Returns the current offset.
   */
  double offset() const { return _dOffset; }
  /**
   * Sets the value of \(\beta\) to *scale*. The default value is
   * one.
   */
  void setScale(double scale) { _dScale = scale; }
  /**
   * Returns the current scale.
   */
  double scale() const { return _dScale; }
  /**
   * Sets the degree of the polynomial to *degree*. The default value
   * is two.
   */
  void setDegree(int degree) { _iDegree = degree; }
  /**
   * Returns the current degree of the polynomial.
   */
  int degree() const { return _iDegree; }

  inline double operator() (FeatureIterator sample, FeatureIterator model, int length) const throw()
  {
    return Pii::pow(_dAlpha + _dBeta * Pii::innerProductN(sample, length, model, 0.0), _iDegree)
  }
private:
  double _dOffset;
  double _dScale;
  int _iDegree;
}

#endif //_PIIPOLYNOMIALKERNEL_H
