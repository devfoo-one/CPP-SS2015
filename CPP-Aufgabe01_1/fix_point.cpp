//
// Created by Tom Oberhauser on 23.04.15.
//

#include "fix_point.hpp"
#include <cmath>
#include <iostream>

fix_point to_fix_point(float value) {
    //http://en.wikipedia.org/wiki/Q_(number_format)
    fix_point fp;
    fp.data = (std::int32_t) std::round(value * 65536); //bitshift by 16 bits and trim
    return fp;
}

float to_float(fix_point value) {
    float result = (float)(value.data * pow(2,-16));
    return result;
}

float floor(fix_point value) {
    return (float) (value.data >> 16);
}

float frac(fix_point value) {
    std::int32_t temp = value.data;
    temp = temp & 65535; // cut off leading bits
    float result = (float)(temp * pow(2,-16)); // no bit shift because that would lead to 0 (integer stuff)
    return result;
}

bool less_than(fix_point lhs, fix_point rhs) {
    return lhs.data < rhs.data;
}

bool equals(fix_point lhs, fix_point rhs) { return is_equal(lhs, rhs); }
bool is_equal(fix_point lhs, fix_point rhs) {
    return lhs.data == rhs.data;
}

fix_point add(fix_point lhs, fix_point rhs) {
    fix_point fp;
    fp.data = lhs.data + rhs.data;
    return fp;
}

fix_point sub(fix_point lhs, fix_point rhs) {
    fix_point fp;
    fp.data = lhs.data - rhs.data;
    return fp;
}

fix_point mul(fix_point lhs, fix_point rhs) {
    //http://en.wikipedia.org/wiki/Q_(number_format)
    fix_point fp;
    std::int64_t temp = (std::int64_t)lhs.data * (std::int64_t)rhs.data;
    temp = temp / (std::int64_t)65536;
    fp.data = (std::int32_t)temp;
    return fp;
}

fix_point div(fix_point lhs, fix_point rhs) {
    fix_point fp;
    std::int64_t temp = ((std::int64_t)lhs.data * 65536) / (std::int64_t)rhs.data;
    fp.data = (std::int32_t)temp;
    return fp;
}
