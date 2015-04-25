//
// Created by Tom Oberhauser on 23.04.15.
//

#include "fix_point.h"
#include <cmath>
#include <iostream>

fix_point to_fix_point(float value) {
    //http://en.wikipedia.org/wiki/Q_(number_format)
    fix_point fp;
    fp.data = (int) (value * 65536); //bitshift by 16 bits and trim
    return fp;
}

float to_float(fix_point value) {
    float result = (float)(value.data * pow(2,-16));
    return result;
}

float floor(fix_point value) { return trunc(value); };
float trunc(fix_point value) {
    int integer = value.data >> 16; //without this line, it tells me that i can´t use bitshift with integers ... ???
    //return (float) value.data >> 16;
    return (float)integer;
}

float frac(fix_point value) {
    std::int32_t temp = value.data;
    temp = temp & 65535; // cut off leading bits
    float result = (float)(temp * pow(2,-16));
    return result;

}

bool less_than(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return false;
}

bool equals(fix_point lhs, fix_point rhs) { return is_equal(lhs, rhs); }
bool is_equal(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return false;
}

fix_point add(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return fix_point();
}

fix_point sub(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return fix_point();
}

fix_point mul(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return fix_point();
}

fix_point div(fix_point lhs, fix_point rhs) {
    //TODO: implement me
    return fix_point();
}
