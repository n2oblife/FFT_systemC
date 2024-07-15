/* fichier fft.cpp */
#include <systemc.h>
#include "fft.h"




#define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
}

typedef struct complex_s complex_t;

struct complex_s {
	float real;
	float imag;
};

complex_t weights[4] = W;

void but(complex_t *weight,
					complex_t *in0,
					complex_t *in1,
					complex_t *out0,
					complex_t *out1)
{
      out0->real = (in0->real + ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out0->imag = (in0->imag + ((in1->real * weight->imag) + (in1->imag * weight->real)));
      out1->real = (in0->real - ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out1->imag = (in0->imag - ((in1->real * weight->imag) + (in1->imag * weight->real)));
}

	
void fft_compute(complex_t in[8], complex_t out[8]) 
{
	complex_t stage1[8], stage2[8];

	// First stage
	but(&weights[0], &in[0], &in[4], &stage1[0], &stage1[1]);
	but(&weights[0], &in[2], &in[6], &stage1[2], &stage1[3]); 
	but(&weights[0], &in[1], &in[5], &stage1[4], &stage1[5]);
	but(&weights[0], &in[3], &in[7], &stage1[6], &stage1[7]);

	// Second stage
	but(&weights[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
	but(&weights[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
	but(&weights[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
	but(&weights[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);
                
	// Etape 3
	but(&weights[0], &stage2[0], &stage2[4], &out[0], &out[4]);
	but(&weights[1], &stage2[1], &stage2[5], &out[1], &out[5]);
	but(&weights[2], &stage2[2], &stage2[6], &out[2], &out[6]);
	but(&weights[3], &stage2[3], &stage2[7], &out[3], &out[7]);
}



void FFT::COMPORTEMENT(){
    
    complex_t complex_in[8];
	complex_t complex_out[8];

	
    while(true)
    { 
        data_req_source_out.write(1);
        
        for (int i = 0; i < 8; i++){ 
            wait();
            while(data_valid_source_in.read()==0){
                wait();
            }

            complex_in[i].real = real_in.read();
            complex_in[i].imag = imag_in.read();
        }

        data_req_source_out.write(0);

        wait();                
        
        fft_compute(complex_in, complex_out);

        wait();
        data_valid_sink_out.write(1);
        real_out.write(complex_out[0].real);
        imag_out.write(complex_out[0].imag);
        wait();

        for (int i = 1; i < 8; i++){
            while(data_req_sink_in.read()==0){
                wait();
            }
            real_out.write(complex_out[i].real);
            imag_out.write(complex_out[i].imag);
            wait();                
        }

        data_valid_sink_out.write(0);
            

    }  
  

}

