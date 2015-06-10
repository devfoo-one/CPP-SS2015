//
// Created by Tom Oberhauser on 26.05.15.
//

#include <cmath>
#include "fix_point_oo.hpp"

fix_point::fix_point() : //default constructor, make sure that empty object has 0 as data
m_data(0)
{ }

fix_point::fix_point(float value) {
    m_data = (std::int32_t) (value * 65536);
}

fix_point::fix_point(double value) {
    m_data = (std::int32_t) ((float)value * 65536);
}

fix_point::fix_point(int32_t value) :
m_data(value) //int32_t ctor calls should already be converted to fixpoint values
{ }

std::int32_t fix_point::getData() {
    return m_data;
}

float fix_point::to_float() const {
    float result = (float)(m_data * pow(2,-16));
    return result;
}

float fix_point::floor() const {
    return (float) (m_data >> 16);
}

float fix_point::frac() const {
    std::int32_t temp = m_data;
    temp = temp & 65535; // cut off leading bits
    return (float)(temp * pow(2,-16)); // no bit shift because that would lead to 0 (integer stuff)
}

fix_point fix_point::operator+(fix_point rhs) const {
    return fix_point(m_data + rhs.m_data);
}

fix_point fix_point::operator-(fix_point rhs) const{
    return fix_point(m_data - rhs.m_data);
}

fix_point fix_point::operator*(fix_point rhs) const{
    //http://en.wikipedia.org/wiki/Q_(number_format)
    std::int64_t temp = (std::int64_t)m_data * (std::int64_t)rhs.m_data;
    temp = temp / (std::int64_t)65536;
    return fix_point((std::int32_t)temp);
}

fix_point fix_point::operator/(fix_point rhs) const{
    std::int64_t temp = ((std::int64_t)m_data * 65536) / (std::int64_t)rhs.m_data;
    return fix_point((std::int32_t)temp);
}

bool fix_point::operator==(fix_point rhs) const { //const weil is so, mal fragen
    return m_data == rhs.m_data;
}

bool fix_point::operator<(fix_point rhs) const{
    return m_data < rhs.m_data;
}

bool fix_point::operator>(fix_point rhs) const{
    return m_data > rhs.m_data;
}

bool fix_point::operator<=(fix_point rhs) const{
    return m_data < rhs.m_data || m_data == rhs.m_data;
}

bool fix_point::operator>=(fix_point rhs) const{
    return m_data > rhs.m_data || m_data == rhs.m_data;
}

fix_point fix_point::operator=(float value) {
    return fix_point(value);
}

fix_point fix_point::operator++() {
    m_data += pow(2,16);
    return *this; //'this' is a pointer '*this' is the dereferenced object
}

fix_point fix_point::operator++(int) {
    fix_point temp = *this;
    m_data += pow(2,16);
    return temp;
}

fix_point fix_point::operator--() {
    m_data -= pow(2,16);
    return *this;
}

fix_point fix_point::operator--(int) {
    fix_point temp = *this;
    m_data -= pow(2,16);
    return temp;
}

fix_point fix_point::operator+=(fix_point rhs) {
    m_data += rhs.m_data;
    return *this;
}

fix_point fix_point::operator-=(fix_point rhs) {
    m_data -= rhs.m_data;
    return *this;
}

fix_point fix_point::operator*=(fix_point rhs) {
    std::int64_t temp = (std::int64_t)m_data * (std::int64_t)rhs.m_data;
    temp = temp / (std::int64_t)65536;
    m_data = (std::int32_t)temp;
    return *this;
}

fix_point fix_point::operator/=(fix_point rhs) {
    std::int64_t temp = ((std::int64_t)m_data * 65536) / (std::int64_t)rhs.m_data;
    m_data = (std::int32_t)temp;
    return *this;
}

float floor(fix_point value) {
    return value.floor();
}

float frac(fix_point value) {
    return value.frac();
}

fix_point sin(fix_point angle) {
    // x−x^3/6+x^5/120
    float x = angle.to_float();
    float sin_x = x - (x * x * x)/6 + (x * x * x * x * x) / 120;
    return fix_point(sin_x);
    //TODO implement me without using floats
}

fix_point cos(fix_point angle) {
    // 1−x^2/2+x^4/24−x^6/720
    float x = angle.to_float();
    float cos_x = (1 - (x * x / 2)) + ((x * x * x * x) / 24) - ((x * x * x * x * x * x) / 720);
    return fix_point(cos_x);
    //TODO implement me without using floats
}