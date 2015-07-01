//
// Created by Tom Oberhauser on 01.07.15.
//

#include "fix_point_collection.h"
#include <algorithm>
#include <math.h>

fix_point_collection::fix_point_collection() :
m_size(0)
{

}

void fix_point_collection::push_back(fix_point p) {
    std::unique_ptr<fix_point[]> temp (new fix_point[m_size + 1]); //new temp object, one item larger than old one
    std::copy(m_data.get(), m_data.get() + m_size, temp.get()); //copy old m_data to the beginning of temp
    temp[m_size] = p; //push given fix_point to last element
    m_data = std::move(temp); // move temp unique_ptr pointer into memory of m_data
    m_size++;
}

fix_point fix_point_collection::pop_back() {
    fix_point returnVal;
    if(m_size != 0) {
        returnVal = m_data[m_size - 1];
        std::unique_ptr<fix_point[]> temp (new fix_point[m_size - 1]); //new temp object, one item smaller than old one
        std::copy(m_data.get(), m_data.get() + (m_size - 1), temp.get());
        m_data = std::move(temp);
        m_size--;
    }
    return returnVal;
}

size_t fix_point_collection::size() const {
    return (size_t) m_size;
}

fix_point fix_point_collection::sum() const {
    fix_point sum = fix_point(0.f);
    for (unsigned int i = 0; i < m_size; i++) {
        sum += m_data[i];
    }
    return sum;
}

fix_point sum(fix_point_collection &collection) {
    return collection.sum();
}

size_t fix_point_collection::count_value(fix_point value) const {
    size_t count = 0;
    for(int i=0; i<m_size; i++) {
        if (m_data[i] == value) {
            count++;
        }
    }
    return count;
}

size_t count_value(fix_point_collection &collection, fix_point value) {
    return collection.count_value(value);
}

const fix_point& fix_point_collection::operator[](unsigned int index) const {
    if(index < m_size) {
        return m_data[index];
    }
    fix_point fp(0.f);
    return fp;
}

fix_point& fix_point_collection::operator[](unsigned int index) {
    if(index < m_size) {
        return m_data[index];
    }
    fix_point fp(0.f);
    return fp;

}

fix_point fix_point_collection::operator[](fix_point index) const {
    int lowerIndex = (int) floor(index.to_float());
    int upperIndex = (int) ceil(index.to_float());
    float t = index.to_float() - lowerIndex;
    if(upperIndex < m_size) {
        return fix_point((1.f - t) * m_data[lowerIndex].to_float() + t * m_data[upperIndex].to_float());
    }
    return fix_point(0.f);
}

