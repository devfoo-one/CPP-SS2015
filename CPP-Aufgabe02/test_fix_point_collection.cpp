#include "fix_point_collection.h"

#include <cassert>

int main()
{
    // create an empty collection of fix_point values
    fix_point_collection collection;

    // add another fix_point value at the end
    collection.push_back(3.5f);
    collection.push_back(2.25f);
    collection.push_back(3.5f);
    collection.push_back(-2.25f);
    collection.push_back(3.5f);

    // check size
    size_t size = collection.size();
    assert(size == 5);

    // sum all values together
    const fix_point sum_all = sum(collection);
    assert(sum_all == 10.5f);

    // count value
    size_t count = count_value(collection, 3.5f);
    assert(count == 3);

    // interpolation
    const fix_point index = { 1.75f };
    assert(collection[index] == 3.1875f);

    // override 4th element
    collection[3] = -1.25f;
    assert(collection[3] == -1.25f);

    // pop last element
    collection.pop_back();

    // check size
    size = collection.size();
    assert(size == 4);

    // count value
    count = count_value(collection, 3.5f);
    assert(count == 2);

    return 0;
}
