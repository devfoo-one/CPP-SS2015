//
// Created by Tom Oberhauser on 26.05.15.
//

#include <cstdint>

#ifndef CPP_AUFGABE01_FIX_POINT_OO_H
#define CPP_AUFGABE01_FIX_POINT_OO_H
template <int fixM, int fixN>
class fix_point {
private:
    std::int32_t m_data;
public:
    fix_point();
    fix_point(float value);
    fix_point(double value);
    fix_point(int32_t value); //otherwise 'ambiguous conversion for functional-style cast from 'int' to 'fix_point''
    float to_float() const;
    float floor() const;
    float frac() const;
    fix_point operator+(fix_point rhs) const;
    fix_point operator-(fix_point rhs) const;
    fix_point operator*(fix_point rhs) const;
    fix_point operator/(fix_point rhs) const;
    fix_point operator%(fix_point rhs) const;
    fix_point operator=(float value);
    bool operator==(fix_point rhs) const;
    bool operator!=(fix_point rhs) const { return !operator==(rhs); };
    bool operator<(fix_point rhs) const;
    bool operator>(fix_point rhs) const;
    bool operator>=(fix_point rhs) const;
    bool operator<=(fix_point rhs) const;
    fix_point operator++ (); // prefix
    fix_point operator-- (); // prefix
    fix_point operator++ (int); // postfix
    fix_point operator-- (int); // postfix
    fix_point operator+= (fix_point rhs);
    fix_point operator-= (fix_point rhs);
    fix_point operator*= (fix_point rhs);
    fix_point operator/= (fix_point rhs);
    explicit operator float() const; //explicit, otherwise ambigous '=='
    explicit operator int() const; //explicit, otherwise ambigous '=='
};

template <typename fixpointType>
float floor(fixpointType value);

template <typename fixpointType>
float frac(fixpointType value);

template <typename fixpointType>
fixpointType sin(fixpointType angle);

template <typename fixpointType>
fixpointType cos(fixpointType angle);

#endif //CPP_AUFGABE01_FIX_POINT_OO_H
