#ifndef FFT_H
#define FFT_H
#include <systemc.h>
#include "fft_types.h"
#pragma hls_design top
#define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
}

typedef struct complex_s complex_t;

struct complex_s {
	d_type real;
	d_type imag;
};


SC_MODULE(FFT)
    {
    public :
        sc_in_clk   clk;
        sc_in<bool>	rst ;
        sc_in<bool> data_valid_source,data_req_sink; // BCA
        sc_in <d_type>   in_real;
        sc_in <d_type>   in_img ;
        sc_out<d_type>  out_real;
        sc_out<d_type>  out_img ;
        sc_out<bool> data_valid_sink,data_req_source; // BCA

        SC_CTOR(FFT):clk("clk") 
        {
            SC_THREAD(COMPORTEMENT);
            sensitive << clk.pos() ;
            reset_signal_is(rst,true);
        }

    private :
        void COMPORTEMENT();
        complex_t cx_in[8],cx_out[8];
        // bool processing ;    
    
    };      
#endif
