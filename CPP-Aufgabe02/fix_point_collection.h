//
// Created by Tom Oberhauser on 01.07.15.
//

#ifndef CPP_AUFGABE02_FIX_POINT_COLLECTION_H
#define CPP_AUFGABE02_FIX_POINT_COLLECTION_H

#include <memory>
#include "fix_point_oo.hpp"

class fix_point_collection {
private:
    unsigned int m_size;
    std::unique_ptr<fix_point[]> m_data;
public:
    fix_point_collection();
    void push_back(fix_point);
    fix_point pop_back();
    size_t size() const;
    fix_point sum() const;
    size_t count_value(fix_point value) const;
    const fix_point& operator[](unsigned int index) const;
    fix_point& operator[](unsigned int index);
    fix_point operator[](fix_point index) const;
};

fix_point sum(fix_point_collection &collection); // "&" ... otherwise it would copy our collection, that leads to dead kittens!
size_t count_value(fix_point_collection &collection, fix_point value);

#endif //CPP_AUFGABE02_FIX_POINT_COLLECTION_H
