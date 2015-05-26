//
// Created by Tom Oberhauser on 23.04.15.
//

#include <cstdint>

#ifndef CPP_AUFGABE01_FIX_POINT_H
#define CPP_AUFGABE01_FIX_POINT_H

#endif //CPP_AUFGABE01_FIX_POINT_H

struct fix_point {std::int32_t data;};
fix_point to_fix_point(float value);
float to_float(fix_point value);
float trunc(fix_point value);
float floor(fix_point value);
float frac(fix_point value);
bool is_equal(fix_point lhs, fix_point rhs);
bool equals(fix_point lhs, fix_point rhs);
bool less_than(fix_point lhs, fix_point rhs);
fix_point add(fix_point lhs, fix_point rhs);
fix_point sub(fix_point lhs, fix_point rhs);
fix_point mul(fix_point lhs, fix_point rhs);
fix_point div(fix_point lhs, fix_point rhs);