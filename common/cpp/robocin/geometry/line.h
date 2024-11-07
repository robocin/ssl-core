#ifndef ROBOCIN_GEOMETRY_LINE_H
#define ROBOCIN_GEOMETRY_LINE_H

namespace robocin {

template <class PT>
struct Line {

    PT pt1, pt2;

    // Constructors:
    inline constexpr Line() = default;
    inline constexpr Line(const PT& pt1, const PT& pt2) : pt1(pt1), pt2(pt2) {};

    // Line comparison:
    inline constexpr bool operator==(const Line& other) const {
        return pt1 == other.pt1 and pt2 == other.pt2;
    }

    // Setters:
    inline constexpr void setP1(const PT& pt1) { this->pt1 = pt1; };
    inline constexpr void setP2(const PT& pt2) { this->pt2 = pt2; };
    inline constexpr void setPoints(const PT& pt1, const PT& pt2) { this->pt1 = pt1, this->pt2 = pt2; };

    // Getters:
    inline constexpr PT p1() const { return pt1; };
    inline constexpr PT p2() const { return pt2; };
};

} // namespace robocin


#endif // ROBOCIN_GEOMETRY_LINE_H