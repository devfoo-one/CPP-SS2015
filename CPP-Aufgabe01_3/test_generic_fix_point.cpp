#include "fixpoint.hpp"
#include <cassert>
#include <cmath>


template< typename NumberType >
void test( float f1 = 6.375f , float f2 = -4.0f )
{
    using fix_point_t = NumberType;

    const fix_point_t fp1( f1 );
    const fix_point_t fp2 = f2;

    // ----------------------------------------------------------
    // integral and fractional parts
    assert( floor(fp1) ==  std::floor(f1) );
    assert( fp1.frac() ==  fix_point_t( f1 - std::floor(f1) ) );
    assert( frac(fp1)  ==  fix_point_t( f1 - std::floor(f1) ) );
    assert( floor(fp2) ==  std::floor(f2)  );
    assert( fp2.frac() ==  fix_point_t( f2 - std::floor(f2) ) );
    assert( frac(fp2)  ==  fix_point_t( f2 - std::floor(f2) ) );

    // ----------------------------------------------------------
    // comparison and ordering
    assert( fp1 == f1 );
    assert( fp2 != fp1 );
    assert( fp2 < fp1  );
    assert( fp1 > fp2  );
    assert( fp2 <= fp1 );
    assert( fp1 >= fp2 );
    assert( fp1 <= fix_point_t(f1) );
    assert( fp1 >= fix_point_t(f1) );


    float df = 1.f / float(1 << (NumberType::post_point_bits-1));

    // ----------------------------------------------------------
    // arithmetics
    assert( fp1 + fp2 == fix_point_t( f1+f2 ) );
    assert( fp1 - fp2 == fix_point_t( f1-f2 ) );
    assert( fp1 * fp2 == fix_point_t( f1*f2 ) );
    assert( fp1 / fp2 >  fix_point_t( f1/f2-df )  &&   fp1/fp2 < fix_point_t(f1/f2+df) );

    // ----------------------------------------------------------
    // arithmetics assignment
    fix_point_t
            fp3 = fp1;  fp3 += fp2;     assert( fp3 == fix_point_t(f1+f2) );
    fp3 = fp1;  fp3 -= fp2;     assert( fp3 == fix_point_t(f1-f2) );
    fp3 = fp1;  fp3 *= fp2;     assert( fp3 == fix_point_t(f1*f2) );
    fp3 = fp1;  fp3 /= fp2;     assert( fp3 >  fix_point_t(f1/f2-df)  &&  fp3 < fix_point_t(f1/f2+df) );

    // ----------------------------------------------------------
    // pre/post - increment/decrement
    fp3 = fp1;  assert( ++fp3 == f1+1.f );
    fp3 = fp1;  assert( --fp3 == f1-1.f );
    fp3 = fp1;  assert( fp3++ == f1 );  assert( fp3 == f1+1.f  );
    fp3 = fp1;  assert( fp3-- == f1 );  assert( fp3 == f1-1.f  );
}


int main()
{
    test< fix_point<16,16> >();
    test< fix_point<8,24>  >();
    test< fix_point<27,5>  >();
    test< fix_point<7,9>   >();
    test< fix_point<4,4>   >( 3.7 , 2.3 );
}