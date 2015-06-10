#include "fix_point_oo.hpp"
#include <cassert>
#include <cmath>

int main()
{
    const fix_point fp1(6.375f);
    const fix_point fp2 = -4.0f;

    // ----------------------------------------------------------
    // integral and fractional parts
    assert( floor(fp1) ==  6.f  );
    assert( fp1.frac() == .375f );
    assert( frac(fp1)  == .375f );
    assert( floor(fp2) == -4.f  );
    assert( fp2.frac() ==  0.f  );
    assert( frac(fp2)  ==  0.f  );

    // ----------------------------------------------------------
    // comparison and ordering
    assert( fp1 == fix_point(6.375) );
    assert( fp2 != fp1 );
    assert( fp2 < fp1  );
    assert( fp1 > fp2  );
    assert( fp2 <= fp1 );
    assert( fp1 >= fp2 );
    assert( fp1 <= fix_point(6.375) );
    assert( fp1 >= fix_point(6.375) );

    // ----------------------------------------------------------
    // arithmetics
    assert( fp1 + fp2 ==  2.375f   );
    assert( fp1 - fp2 ==  10.375f  );
    assert( fp1 * fp2 == -25.5f    );
    assert( fp1 / fp2 == -1.59375f );

    // ----------------------------------------------------------
    // arithmetics assignment
    fix_point
    fp3 = fp1;  fp3 += fp2;     assert( fp3 ==  2.375f   );
    fp3 = fp1;  fp3 -= fp2;     assert( fp3 ==  10.375f  );
    fp3 = fp1;  fp3 *= fp2;     assert( fp3 == -25.5f    );
    fp3 = fp1;  fp3 /= fp2;     assert( fp3 == -1.59375f );

    // ----------------------------------------------------------
    // pre/post - increment/decrement
    fp3 = fp1;  assert( ++fp3 ==  7.375f );
    fp3 = fp1;  assert( --fp3 ==  5.375f );
    fp3 = fp1;  assert( fp3++ ==  6.375f  );  assert( fp3 ==  7.375f  );
    fp3 = fp1;  assert( fp3-- ==  6.375f  );  assert( fp3 ==  5.375f  );

    // ----------------------------------------------------------
    // trigonometric functions
    assert( sin(fix_point(0.5f)) == fix_point(sin(0.5f)) );
    assert( cos(fix_point(0.5f)) == fix_point(cos(0.5f)) );

    // ----------------------------------------------------------
    // check some more numbers
    for ( float f = 0.f ; f <= 1.f ; f += 0.25f )   assert( fix_point(f) == f );
}
