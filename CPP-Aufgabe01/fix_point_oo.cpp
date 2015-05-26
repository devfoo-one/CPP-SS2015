//
// Created by Tom Oberhauser on 26.05.15.
//

#include "fix_point_oo.hpp"

fix_point::fix_point(float value) {
    m_data = (int) (value * 65536);
}

float fix_point::to_float(fix_point value) {
    return 0; //TODO implement me
}

float fix_point::trunc(fix_point value) {
    return 0; //TODO implement me
}

float fix_point::frac(fix_point value) {
    return 0; //TODO implement me
}

fix_point fix_point::operator+(fix_point rhs) {
    return fix_point(0); //TODO implement me
}

fix_point fix_point::operator-(fix_point rhs) {
    return fix_point(0); //TODO implement me
}

fix_point fix_point::operator*(fix_point rhs) {
    return fix_point(0); //TODO implement me
}

fix_point fix_point::operator/(fix_point rhs) {
    return fix_point(0); //TODO implement me
}

bool fix_point::operator==(fix_point rhs) {
    return fix_point(0); //TODO implement me
}
