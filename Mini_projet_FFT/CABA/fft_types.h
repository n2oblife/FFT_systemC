//
// Copyright 2003-2015 Siemens
//

#ifndef __FFT_TYPES_H__
#define __FFT_TYPES_H__

#include "systemc.h"
#include "ac_sc.h"
#include "ccs_p2p.h"
#include "ac_fixed.h"

#define DATA_WIDTH 23
#define OVERC_WIDTH 18


typedef ac_fixed<DATA_WIDTH,OVERC_WIDTH,true,AC_RND_INF,AC_SAT> d_type ;

#endif
