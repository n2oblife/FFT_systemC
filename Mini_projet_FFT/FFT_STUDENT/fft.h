#ifndef FFT_H
#define FFT_H
#include <systemc.h>

SC_MODULE(FFT){	
    public :
        sc_in<bool>	   clk; 
        sc_in<float>   real_in;
        sc_in<float>   imag_in;

        sc_out<float>  real_out;
        sc_out<float>  imag_out;

        sc_in<bool>    data_valid_source_in;
        sc_out<bool>   data_req_source_out;

        sc_in<bool>    data_req_sink_in;
        sc_out<bool>   data_valid_sink_out;


        SC_CTOR(FFT) : 
            clk("clk") ,
            real_in("real_in") ,
            imag_in("imag_in"),
            real_out("real_out") ,
            imag_out("imag_out"),
            data_valid_source_in("data_valid_source_in"),
            data_req_sink_in("data_req_sink_in"),
            data_req_source_out("data_req_source_out"),
            data_valid_sink_out("data_valid_sink_out")            
            {
                SC_CTHREAD(COMPORTEMENT,clk.pos());
            }

    private :
        void COMPORTEMENT();


};      



#endif

