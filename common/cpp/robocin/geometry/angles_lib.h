#ifndef ROBOCIN_GEOMETRY_H
#define ROBOCIN_GEOMETRY_H

#include <cassert>
#include <concepts>
#include <type_traits>
#include <cmath>
#include "math/math_lib.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

namespace robocin {

static constexpr bool isNullable(std::floating_point auto f) {
  return math::isNull(f) or not std::isnormal(f);
}

static constexpr bool isNullable(std::integral auto i) {
  return math::isNull(i);
}

namespace angles {
  static constexpr double PI = M_PI;

  /*!
   * @tparam T floating point type.
   * @param radians the value in radians.
   * @return This function converts the radians in T to degrees.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> radiansToDegrees(T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(PI));
  }

  /*!
   * @tparam T integral point type.
   * @param radians the value in radians.
   * @return This function converts the radians in T to degrees and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> radiansToDegrees(T radians) {
    return radiansToDegrees(static_cast<double>(radians));
  }

  /*!
   * @tparam T floating point type.
   * @param degrees the value in degrees.
   * @return This function converts the degrees in T to radians.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> degreesToRadians(T degrees) {
    return (degrees * static_cast<T>(PI)) / static_cast<T>(180);
  }

  /*!
   * @tparam T integral point type.
   * @param degrees the value in degrees.
   * @return This function converts the degrees in T to radians and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> degreesToRadians(T degrees) {
    return degreesToRadians(static_cast<double>(degrees));
  }

  /*!
   * @param lhs, rhs floating point values in radians.
   * @return Returns the signed smallest angle difference in radians.
   * @note This function is not a true angle difference, it is a signed angle difference.
   * @note The angle difference is target (rhs) - source (lhs).
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> smallestAngleDiff(const T& lhs,
                                                                               const T& rhs) {
    T angle = math::modularize<T>(rhs - lhs, static_cast<T>(2) * PI);
    if (angle >= PI) {
      return angle - static_cast<T>(2) * PI;
    }
    
    if (angle < -PI) {
      return angle + static_cast<T>(2) * PI;
    }
    return angle;
  }

  /*!
   * @param value the value in degrees.
   * @return Returns the value in radians.
   */
  constexpr auto operator"" _degrees(long double value) {
    return geometry::degreesToRadians(value);
  }

  /*!
   * @param value the value in degrees.
   * @return Returns the value in radians.
   */
  constexpr auto operator"" _degrees(unsigned long long value) {
    return geometry::degreesToRadians(value);
  }

  /*!
   * @tparam T arithmetic type.
   * @param value The angle to normalize, in radians or degrees (depending on center and amplitude
   * values).
   * @param center The center of the angle interval. <br>
   *   if center == 0 and amplitude == π, the interval is [-π ; +π]. <br>
   *   if center == π and amplitude == π, the interval is [0 ; 2*π].
   * @param amplitude The amplitude of the angle, usually π in radians or 180 in degrees.
   * @return Normalizes the angle and returns the value between [-amplitude + center, +amplitude +
   * center].
   */
  template <class T>
  constexpr T normalizeAngle(T value, const T& center, const T& amplitude) {
    value = math::modularize<T>(value, static_cast<T>(2) * amplitude);
    if (value < -amplitude + center) {
      value += static_cast<T>(2) * amplitude;
    } else if (value > amplitude + center) {
      value -= static_cast<T>(2) * amplitude;
    }
    return value;
  }

  /*!
   * @tparam T floating point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-π, +π].
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> normalizeInPI(const T& radians) {
    return normalizeAngle<T>(radians, 0, static_cast<T>(PI));
  }

  /*!
   * @tparam T floating point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-180, +180].
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> normalizeIn180(const T& degrees) {
    return normalizeAngle<T>(degrees, 0, static_cast<T>(180));
  }

  /*!
   * @tparam T integer point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-180, +180] in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> normalizeIn180(const T& degrees) {
    return normalizeAngle<double>(degrees, 0, static_cast<double>(180));
  }
}  // namespace angles

}  // namespace robocin

#endif // ROBOCIN_ANGLES_H

