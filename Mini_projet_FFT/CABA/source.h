/* fichier source.h */
#ifndef SOURCE_H
#define SOURCE_H

#include "systemc.h"
#include "fft_types.h"
SC_MODULE(SOURCE)
  {
    sc_in_clk    clk;
    sc_in<bool> data_req; // BCA
    sc_out<d_type> out_real;
    sc_out<d_type> out_img;
    sc_out<bool> data_valid; // BCA

    void COMPORTEMENT();

    SC_CTOR(SOURCE)
    {
      SC_THREAD(COMPORTEMENT);
      sensitive << clk.pos();
    }
};
#endif
