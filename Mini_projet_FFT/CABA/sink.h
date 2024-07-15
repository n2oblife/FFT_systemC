#ifndef SINK_H
#define SINK_H

#include "systemc.h"
#include "fft_types.h"

 SC_MODULE(SINK) 
    {
         sc_in_clk    clk; 
         sc_in<bool> data_valid; // BCA
         sc_in<d_type> in_real; 
         sc_in<d_type> in_img ; 
         sc_out<bool> data_req; // BCA

        void COMPORTEMENT(); 

         SC_CTOR(SINK)
              {
                     SC_THREAD(COMPORTEMENT);
                     sensitive << clk.pos();
              }    };
#endif
