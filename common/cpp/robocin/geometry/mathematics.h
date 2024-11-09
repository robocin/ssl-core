#ifndef ROBOCIN_MATHEMATICS_H
#define ROBOCIN_MATHEMATICS_H

#include "robocin/geometry/line.h"
#include "robocin/geometry/point2d.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <type_traits>

namespace mathematics {

template <class T>
bool fuzzyIsNull(T value, T epsilon = static_cast<T>(1e-9)) {
  return std::abs(value) < epsilon;
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
  if (fuzzyIsNull(l_higher - l_lower)) {
    throw std::runtime_error("'l_lower' equals to 'l_higher'.");
  }
  return (value - l_lower) * (r_higher - r_lower) / (l_higher - l_lower) + r_lower;
}

////////////////////////////////////////////////////// adapting

/*!
 * @tparam T arithmetic type.
 * @param a, b, c, d lines (a, b) and (c, d).
 * @return Determines if lines through (a, b) and (c, d) are parallel.
 */
template <class T>
constexpr bool linesParallel(const robocin::Point2D<T>& a,
                             const robocin::Point2D<T>& b,
                             const robocin::Point2D<T>& c,
                             const robocin::Point2D<T>& d) {
  return fuzzyIsNull(robocin::Point2D<T>{b - a}.cross(c - d));
}

/*!
 * @tparam T arithmetic type.
 * @param a, b lines a and b.
 * @return Determines if lines through (a, b) and (c, d) are parallel.
 */
template <class T>
constexpr bool linesParallel(const robocin::Line<T>& a, const robocin::Line<T>& b) {
  return linesParallel(a.p1(), a.p2(), b.p1(), b.p2());
}

/*!
 * @tparam T arithmetic type.
 * @param a, b, c, d lines (a, b) and (c, d).
 * @return Determines if lines through (a, b) and (c, d) are collinear.
 */
template <class T>
constexpr bool linesCollinear(const robocin::Point2D<T>& a,
                              const robocin::Point2D<T>& b,
                              const robocin::Point2D<T>& c,
                              const robocin::Point2D<T>& d) {
  if (!linesParallel<T>(a, b, c, d)) {
    return false;
  }
  if (!fuzzyIsNull(robocin::Point2D<T>{a - b}.cross(a - c))) {
    return false;
  }
  if (!fuzzyIsNull(robocin::Point2D<T>{c - d}.cross(c - a))) {
    return false;
  }
  return true;
}

/*!
 * @tparam T arithmetic type.
 * @param a and b are lines.
 * @return Determines if lines through (a, b) and (c, d) are collinear.
 */
template <class T>
constexpr bool linesCollinear(const robocin::Line<T>& a, const robocin::Line<T>& b) {
  return linesCollinear(a.p1(), a.p2(), b.p1(), b.p2());
}
/*!
 * @tparam T arithmetic type.
 * @param a, b, c, d lines (a, b) and (c, d).
 * @return Determines if line segment from a to b intersects with line segment from c to d.
 */
template <class T>
constexpr bool segmentsIntersect(const robocin::Point2D<T>& a,
                                 const robocin::Point2D<T>& b,
                                 const robocin::Point2D<T>& c,
                                 const robocin::Point2D<T>& d) {
  if (linesCollinear<T>(a, b, c, d)) {
    if (fuzzyIsNull(a.distanceSquaredTo(c)) || fuzzyIsNull(a.distanceSquaredTo(d))
        || fuzzyIsNull(b.distanceSquaredTo(c)) || fuzzyIsNull(b.distanceSquaredTo(d))) {
      return true;
    }
    if (robocin::Point2D<T>{c - a}.dot(c - b) > 0 && robocin::Point2D<T>{d - a}.dot(d - b) > 0
        && robocin::Point2D<T>{c - b}.dot(d - b) > 0) {
      return false;
    }
    return true;
  }
  if (robocin::Point2D<T>{d - a}.cross(b - a) * robocin::Point2D<T>{c - a}.cross(b - a) > 0) {
    return false;
  }
  if (robocin::Point2D<T>{a - c}.cross(d - c) * robocin::Point2D<T>{b - c}.cross(d - c) > 0) {
    return false;
  }
  return true;
}

/*!
 * @tparam T arithmetic type.
 * @param a, b, c, d lines (a, b) and (c, d).
 * @return Determines if line segment from a to b intersects with line segment from c to d.
 */
template <class T>
constexpr bool segmentsIntersect(const robocin::Line<T>& a, const robocin::Line<T>& b) {
  return segmentsIntersect(a.p1(), a.p2(), b.p1(), b.p2());
}

} // namespace mathematics

#endif // ROBOCIN_MATHEMATICS_H
