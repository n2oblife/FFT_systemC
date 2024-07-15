#ifndef FFT_H
#define FFT_H
#include <systemc.h>


#define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
}

typedef struct complex_s complex_t;

struct complex_s {
	double real;
	double imag;
};


SC_MODULE(FFT)
    {
    public :
        sc_in_clk   clk;
        sc_in<bool> data_valid_source,data_req_sink; // BCA
        sc_in<float>   in_real;
        sc_in<float>   in_img ;
        sc_out<float>  out_real;
        sc_out<float>  out_img ;
        sc_out<bool> data_valid_sink,data_req_source; // BCA

        SC_CTOR(FFT)
        {
            SC_THREAD(COMPORTEMENT);
            sensitive << clk.pos();
        }

    private :
        void COMPORTEMENT();
        complex_t cx_in[8],cx_out[8];
        // bool processing ;    
    
    };      
#endif
