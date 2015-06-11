//
// Created by Tom Oberhauser on 26.05.15.
//

#include <cstdint>
#include <cmath>
#include <iostream>

#ifndef CPP_AUFGABE01_FIX_POINT_OO_H
#define CPP_AUFGABE01_FIX_POINT_OO_H


template< int bits >
struct type_generator
{
};

template<> struct type_generator<8>
{
    using type = std::int8_t;
};

template<> struct type_generator<16>
{
    using type = std::int16_t;
};

template<> struct type_generator<32>
{
    using type = std::int32_t;
};

template<> struct type_generator<64>
{
    using type = std::int64_t;
};



template <int fixM, int fixN>
class fix_point {
public:
    static const int pre_point_bits = fixM; //static, see comment below
    static const int post_point_bits = fixN; //static, see comment below
    static const int total_bits = fixM + fixN; //static, otherwise "invalid use of non-static data member 'total_bits'" in 'typename type_generator<total_bits>::type;'
    using IntegerType = typename type_generator<total_bits>::type; //access type alias, get typename and store it into IntegerType
    using IntegerTypeDoublePrecision = typename type_generator<total_bits * 2>::type; //access type alias, get typename and store it into IntegerType

    fix_point() :
    m_data(0)
    { }

    fix_point(float value) {
        m_data = (IntegerType) std::round(value * std::pow(2, fixN));
    }

    fix_point(double value) {
        m_data = (IntegerType) (std::round(value * std::pow(2, fixN)));
    }

    fix_point(IntegerType value) : //otherwise 'ambiguous conversion for functional-style cast from 'int' to 'fix_point''
        m_data(value) //int32_t ctor calls should already be converted to fixpoint values
        { }

    IntegerType getData() const{
        return m_data;
    }

    float to_float() const {
        float result = (float)(m_data * std::pow(2,-fixN));
        return result;
    }

    float floor() const {
        return (float) (m_data >> fixN);
    }
    float frac() const  {
        IntegerType temp = m_data;
        temp = temp & (IntegerType)(std::pow(2, fixN) - 1); // cut off leading bits
        return (float)(temp * std::pow(2,-fixN)); // no bit shift because that would lead to 0 (integer stuff)
    }

    template <typename fixpointType>
    fixpointType operator+(fixpointType rhs) const {
        IntegerType sum = getData() + rhs.getData();
        return fixpointType(sum);
    }

    template <typename fixpointType>
    fix_point operator-(fixpointType rhs) const {
        IntegerType sum = getData() - rhs.getData();
        return fixpointType(sum);
    }

    template <typename fixpointType>
    fix_point operator*(fixpointType rhs) const {
        //http://en.wikipedia.org/wiki/Q_(number_format)
        IntegerTypeDoublePrecision temp = (IntegerTypeDoublePrecision)m_data * (IntegerTypeDoublePrecision)rhs.m_data;
        temp = temp / (IntegerTypeDoublePrecision)std::pow(2, fixN);
        return fixpointType((IntegerType)temp);
    }

    template <typename fixpointType>
    fix_point operator/(fixpointType rhs) const {
        IntegerTypeDoublePrecision temp = ((IntegerTypeDoublePrecision)m_data * (IntegerTypeDoublePrecision)std::pow(2, fixN)) / (IntegerTypeDoublePrecision)rhs.m_data;
        return fixpointType((IntegerType)temp);
    }

    template <typename fixpointType>
    fix_point operator%(fixpointType rhs) const  {
        return fixpointType(m_data % rhs.m_data);
    }

    template <typename fixpointType>
    bool operator<(fixpointType rhs) const {
        return m_data < rhs.m_data;
    }

    template <typename fixpointType>
    bool operator>(fixpointType rhs) const {
        return m_data > rhs.m_data;
    }

    template <typename fixpointType>
    bool operator>=(fixpointType rhs) const {
        return m_data > rhs.m_data || m_data == rhs.m_data;
    }

    template <typename fixpointType>
    bool operator<=(fixpointType rhs) const {
        return m_data < rhs.m_data || m_data == rhs.m_data;
    }

    fix_point operator=(float value) {
        return fix_point(value);
    }

    fix_point operator++ () { // prefix
        m_data += pow(2,fixN);
        return *this; //'this' is a pointer '*this' is the dereferenced object
    }
    fix_point operator-- () { // prefix
        m_data -= pow(2,fixN);
        return *this;
    }
    fix_point operator++ (int) { // postfix
        fix_point temp = *this;
        m_data += pow(2,fixN);
        return temp;
    }
    fix_point operator-- (int) { // postfix
        fix_point temp = *this;
        m_data -= pow(2,fixN);
        return temp;
    }

    template <typename fixpointType>
    fix_point operator+= (fixpointType rhs) {
        m_data += rhs.m_data;
        return *this;
    }

    template <typename fixpointType>
    fix_point operator-= (fixpointType rhs) {
        m_data -= rhs.m_data;
        return *this;
    }

    template <typename fixpointType>
    fix_point operator*= (fixpointType rhs) {
        IntegerTypeDoublePrecision temp = (IntegerTypeDoublePrecision)m_data * (IntegerTypeDoublePrecision)rhs.m_data; //TODO this code already exists in / operator
        temp = temp / (IntegerTypeDoublePrecision)std::pow(2, fixN);
        m_data = (IntegerTypeDoublePrecision)temp;
        return *this;
    }

    template <typename fixpointType>
    fix_point operator/= (fixpointType rhs) {
        IntegerTypeDoublePrecision temp = ((IntegerTypeDoublePrecision)m_data * (IntegerTypeDoublePrecision)std::pow(2, fixN)) / (IntegerTypeDoublePrecision)rhs.m_data; //TODO this code already exists in / operator
        m_data = (IntegerType)temp;
        return *this;
    }

    operator float() const {  //explicit, otherwise ambigous '=='
        return to_float();
    }
    explicit operator int() const  { //explicit, otherwise ambigous '=='
        return (int)floor();
    }

private:
    IntegerType m_data;
};

template <typename fixpointType>
float floor(fixpointType value) {
    return value.floor();
}

template <typename fixpointType>
float frac(fixpointType value) {
    return value.frac();
}

template <typename fixpointType>
fixpointType sin(fixpointType x) {
    // TODO add modulo 2pi
//    fix_pointType sin_x = (x - ((x * x * x)/fixpointType(6.f))) + (((x * x * x * x * x) / fixpointType(120.f)));
    fixpointType sin_x = (x - ((x*x*x)/fixpointType(6.f))) + ((x*x*x*x*x) / fixpointType(120.f)) - ((x*x*x*x*x*x*x) / fixpointType(5040.f));
    return sin_x;
}

template <typename fixpointType>
fixpointType cos(fixpointType x) {
    // 1−x^2/2+x^4/24−x^6/720
    // TODO add modulo 2pi
//    fixpointType cos_x = (fixpointType(1.f) - (x * x / fixpointType(2.f))) + ((x * x * x * x) / fixpointType(24.f)) - ((x*x*x*x*x*x) / fixpointType(720.f));
    fixpointType cos_x = (fixpointType(1.f) - (x * x / fixpointType(2.f))) + ((x * x * x * x) / fixpointType(24.f)) - ((x*x*x*x*x*x) / fixpointType(720.f)) + ((x*x*x*x*x*x*x*x) / fixpointType(40320.f));
    return cos_x;
}

template <typename fixpointType> //moved out of class because i had to remove the explicit from the float cast (test does "float == fix_point" which is bad, mkay?)
bool operator==(fixpointType lhs, fixpointType rhs) {
    return lhs.getData() == rhs.getData();
}

template <typename fixpointType>
bool operator!=(fixpointType lhs, fixpointType rhs) {
    return !(lhs == rhs);
}


#endif //CPP_AUFGABE01_FIX_POINT_OO_H
