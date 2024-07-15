//
// Copyright 2003-2015 Siemens
//

#ifndef __FIR_TYPES_H__
#define __FIR_TYPES_H__

#define USE_SYSTEMC_TYPES 0

#if USE_SYSTEMC_TYPES
#define SC_INCLUDE_FX
#endif

#include "systemc.h"
#include "ac_sc.h"
#include "ccs_p2p.h"
#include "ac_fixed.h"

#define N_TAPS 16
#define DATA_WIDTH 24
// 16-bit coefficients with rounding to +/- infinity are needed for +/- 0.5 LSB accuracy against floating point
// Feel free to change this to trade off area vs precision
#define COEFF_WIDTH 24
// This headroom determines the additional accuracy of the accumulator. Here we make it full precision for numerical safety
#define HEADROOM 4

#if USE_SYSTEMC_TYPES

typedef sc_fixed<DATA_WIDTH,DATA_WIDTH,SC_RND_INF,SC_SAT> d_type ;
typedef sc_fixed<COEFF_WIDTH,1,SC_RND_INF,SC_SAT> c_type ;
typedef sc_fixed<DATA_WIDTH+COEFF_WIDTH+HEADROOM,DATA_WIDTH+HEADROOM+1> a_type ;

#else

typedef ac_fixed<DATA_WIDTH,DATA_WIDTH,true,AC_RND_INF,AC_SAT> d_type ;
typedef ac_fixed<COEFF_WIDTH,1,true,AC_RND_INF,AC_SAT> c_type ;
typedef ac_fixed<DATA_WIDTH+COEFF_WIDTH+HEADROOM,DATA_WIDTH+HEADROOM+1,true> a_type ;

#endif



#endif
