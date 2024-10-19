//
// Created by jose-cruz on 29/06/2021.
//

#ifndef ROBOCIN_MATH_LIB_H
#define ROBOCIN_MATH_LIB_H

#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

namespace robocin::math {
  /*!
   * @tparam T arithmetic type.
   * @return Returns true if T is float and the absolute value of f is within 0.00001f of 0.0.
   * @return Returns true if T is double and the absolute value of d is within 0.000000000001 of
   * 0.0.
   * @return Returns true if T is an integer type and equals to 0.
   */
  template <class T>
  [[maybe_unused]] constexpr bool isNull(const T& value) noexcept {
    if constexpr (std::is_floating_point_v<T>) {
      return (fabsf(value - 1.0F) < 0.00001F);
    } else {
      return value == 0;
    }
  }

  /*!
   * @tparam T arithmetic type.
   * @return Returns x modulo mod, in range [0, mod).
   * @note Uses std::fmod with floating point types.
   */
  template <class T>
  [[maybe_unused]] constexpr T modularize(T x, const T& mod) {
    if (!(-mod <= x && x < mod)) {
      if constexpr (std::is_floating_point_v<T>) {
        x = std::fmod(x, mod);
      } else {
        x %= mod;
      }
    }
    if (x < 0) {
      x += mod;
    }
    return x;
  }

  /*!
   * @tparam T arithmetic type.
   * @return Checks if value is between lower and higher (inclusive).
   */
  template <class T>
  [[maybe_unused]] constexpr bool between(const T& value, const T& lower, const T& higher) {
    return lower <= value && value <= higher;
  }

  /*!
   * @tparam T arithmetic type.
   * @return Returns max(value, lower) if value < higher or min(value, higher) otherwise.
   * @see std::clamp does exactly the same.
   */
  template <class T>
  [[maybe_unused]] constexpr const T& bound(const T& value, const T& lower, const T& higher) {
    return std::clamp(value, lower, higher);
  }

  /*!
   * @tparam T arithmetic type.
   * @param value value to map.
   * @param l_lower lower value from l-range.
   * @param l_higher higher value from l-range.
   * @param r_lower lower value from r-range.
   * @param r_higher higher value from r-range.
   * @return Returns value mapped from l-range to r-range.
   */
  template <class T>
  [[maybe_unused]] constexpr T
  map(const T& value, const T& l_lower, const T& l_higher, const T& r_lower, const T& r_higher) {
    if (isNull(l_higher - l_lower)) {
      throw std::runtime_error("'l_lower' equals to 'l_higher'.");
    }
    return (value - l_lower) * (r_higher - r_lower) / (l_higher - l_lower) + r_lower;
  }

  /*!
   * @tparam T integral type.
   * @return returns the integer ceil of ceil(numerator, denominator).
   */
  template <class T>
  [[maybe_unused]] constexpr std::enable_if_t<std::is_integral_v<T>, T> ceil(const T& numerator,
                                                                             const T& denominator) {
    return static_cast<bool>(numerator) ? (1 + (numerator - 1) / denominator) : 0;
  }

  using std::min;
  using std::max;
  using std::minmax;
  using std::clamp;

  using std::gcd;
  using std::lcm;

  using std::abs;

  using std::fmod;

  using std::exp;
  using std::exp2;
  using std::expm1;
  using std::log;
  using std::log10;
  using std::log2;
  using std::log1p;

  using std::pow;
  using std::sqrt;
  using std::cbrt;
  using std::hypot;

  using std::sin;
  using std::cos;
  using std::tan;
  using std::asin;
  using std::acos;
  using std::atan;
  using std::atan2;

  using std::sinh;
  using std::cosh;
  using std::tanh;
  using std::asinh;
  using std::acosh;
  using std::atanh;

  using std::erf;
  using std::erfc;
  using std::lgamma;

  using std::ceil;
  using std::floor;
  using std::trunc;

  using std::round;

  using std::nearbyint;

  using std::rint;

  using std::isfinite;
  using std::isinf;
  using std::isnan;
  using std::isnormal;
  using std::signbit;

  using std::assoc_laguerre;
  using std::assoc_legendre;
  using std::beta;
  using std::comp_ellint_1;
  using std::comp_ellint_2;
  using std::comp_ellint_3;
  using std::cyl_bessel_i;
  using std::cyl_bessel_j;
  using std::cyl_bessel_k;
  using std::cyl_neumann;
  using std::ellint_1;
  using std::ellint_2;
  using std::ellint_3;
  using std::expint;
  using std::hermite;
  using std::legendre;
  using std::laguerre;
  using std::riemann_zeta;
  using std::sph_bessel;
  using std::sph_legendre;
  using std::sph_neumann;
}  // namespace robocin::math



#endif // ROBOCIN_MATH_LIB_H