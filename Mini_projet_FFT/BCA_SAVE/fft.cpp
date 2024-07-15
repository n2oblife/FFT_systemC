/* fichier fft.cpp */
#include <systemc.h>
/*
 * Author: Pierre-Henri Horrein
 * Pure software C implementation of a 8 point FFT based on Cooley-Tuckey algorithm
 * This is a floating point implementation
 */

#include<stdio.h>
#include"fft.h"

// DECLARATION DES BOOLS A FALSE

complex_t weights[4] = W;
bool processing = false;

// FFT :
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
    
void fft(complex_t in[8], complex_t out[8]) 
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

    processing = false ;

}

void FFT::COMPORTEMENT()
{
    int i = 0;
    int j = 8;
    data_req_source.write(true);
    data_valid_sink.write(false);
 


    while(true)
    { 
        wait();
      
        if (!processing){

            if ( j == 8 ) 
                data_valid_sink.write(false);

            // INPUT :
            if(data_valid_source.read() && i != 8 ){
                cx_in[i].real = in_real.read();
                cx_in[i].imag = in_img.read();
                i++ ;   
            }
            
            // OUTPUT :
            if(data_req_sink.read() && j != 8 ){
                data_valid_sink.write(true);
                out_real.write(cx_out[j].real);
                out_img.write(cx_out[j].imag);
                j++;    
            }

            if ( i == 8 && j == 8){
                i = 0;
                j = 0;
                processing = true;
                data_req_source.write(false);
            }

        }else{
                fft(cx_in, cx_out);
                data_req_source.write(true);
                data_valid_sink.write(false);
                cout<< "[FFT]" << "ALIVE"<<endl;
        } // end else processing
    }//end while
}// end method


