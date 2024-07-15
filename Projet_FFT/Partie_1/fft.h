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
        sc_fifo_in<float>   in;
        sc_fifo_out<float>  out;

        SC_CTOR(FFT)
        {
            SC_THREAD(COMPORTEMENT);
            sensitive << clk.pos();
        }

    private :
        void COMPORTEMENT();
        complex_t cx_in[8],cx_out[8];
    
      
    };      
#endif

// #ifndef __FFT_H__ 
// #define __FFT_H__ 

// #define W {\
// 	{1, 0}, \
// 	{0.7071067812, -0.7071067812}, \
// 	{0, -1}, \
// 	{-0.7071067812, -0.7071067812}\
// }

// typedef struct complex_s complex_t;

// struct complex_s {
// 	double real;
// 	double imag;
// };

// void fft(complex_t in[8], complex_t out[8]);

// #endif
