#ifndef SINK_H
#define SINK_H

#include "systemc.h"

 SC_MODULE(SINK) 
    {
         sc_in_clk    clk; 
         sc_in<bool> data_valid; // BCA
         sc_in<float> in_real; 
         sc_in<float> in_img ; 
         sc_out<bool> data_req; // BCA

        void COMPORTEMENT(); 

         SC_CTOR(SINK)
              {
                     SC_THREAD(COMPORTEMENT);
                     sensitive << clk.pos();
              }    };
#endif
