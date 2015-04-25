#include "fix_point.h"

#include <cassert>

int main()
{
    const fix_point fp1 = to_fix_point(6.375f);
    const fix_point fp2 = to_fix_point(-4.0f);

    // integral and fractional parts
    assert(floor(fp1) == 6.f);
    assert(frac(fp1) == .375f);
    assert(floor(fp2) == -4.f);
    assert(frac(fp2) == 0.f);

    // comparison
    assert(!equals(fp2, fp1));
    assert(less_than(fp2, fp1));

    // arithmetics
    const auto result_add = to_float(add(fp1, fp2));
    const auto result_sub = to_float(sub(fp1, fp2));
    const auto result_mul = to_float(mul(fp1, fp2));
    const auto result_div = to_float(div(fp1, fp2));

    // check results
    assert(result_add == 2.375f);
    assert(result_sub == 10.375f);
    assert(result_mul == -25.5f);
    assert(result_div == -1.59375f);
  
    return 0;
}
