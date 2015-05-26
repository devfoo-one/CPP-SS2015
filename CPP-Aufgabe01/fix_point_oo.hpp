//
// Created by Tom Oberhauser on 26.05.15.
//

#include <cstdint>

#ifndef CPP_AUFGABE01_FIX_POINT_OO_H
#define CPP_AUFGABE01_FIX_POINT_OO_H


class fix_point {
private:
    std::int32_t m_data;
public:
    fix_point(float value);
    float to_float(fix_point value);
    float trunc(fix_point value);
    float floor(fix_point value) { return trunc(value); };
    float frac(fix_point value);
    bool is_equal(fix_point lhs, fix_point rhs);
    bool equals(fix_point lhs, fix_point rhs);
    bool less_than(fix_point lhs, fix_point rhs);
    fix_point operator+(fix_point rhs);
    fix_point operator-(fix_point rhs);
    fix_point operator*(fix_point rhs);
    fix_point operator/(fix_point rhs);
    bool operator==(fix_point rhs);
    bool operator!=(fix_point rhs) { return !operator==(rhs); };

};


#endif //CPP_AUFGABE01_FIX_POINT_OO_H
