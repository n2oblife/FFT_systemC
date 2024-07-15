
#ifndef __TOP_LEVEL_H__
#define __TOP_LEVEL_H__
#include "FIR_TYPES.h"

#pragma hls_design top
SC_MODULE (top_level) {
	sc_in<bool>				clk ; // clock for the processing domain, typically 100 MHz, different from the sampling clock
	sc_in<bool>				rst ;
	sc_in<d_type>			data_in;
	sc_in<bool>				valid_in; // simple signal to valid that a new sample is available on data_in, but coming from another clock domain (48kHz)
	sc_in<c_type>			coeffs[N_TAPS] ;
	sc_out<d_type>			data_out;
	sc_out<bool>			valid_out;


	SC_CTOR(top_level) : 
		clk("clk") ,
		rst("rst") ,
		data_in("data_in") ,
		valid_in("valid_in") ,
		data_out("data_out"),
		valid_out("valid_out")
		{
			SC_CTHREAD(FIR_FILTER,clk.pos());
			reset_signal_is(rst,true);
		}

	private:
	sc_signal<bool> new_sample; //signal to store the state: if new_sample=0 and valid_in='1' then new_sample='0' else new_sample='0'
								// this will allow tracking a rising_edge of valid_in switching at 48kHz while the processing runs at 100MHz

	void FIR_FILTER() { 

		static d_type taps[N_TAPS];
		static a_type acc = 0 ;
		new_sample = false;
		valid_out.write(false);
		
		while (1) {
		    wait() ; // clock edge
			if(!new_sample&&valid_in.read()){ // rising_edge of valid_in
				//cerr<<"new sample"<<endl;
				new_sample=true;
				SHIFT:for(int i=(N_TAPS-1);i>=0;i--) {
					taps[i] = (i==0) ? data_in.read() : taps[i-1] ;
				}	
				acc = 0 ;
				MAC:for(int i=0;i<N_TAPS;i++) {
					acc += coeffs[i].read() * taps[i] ;
				}
				//cerr<<"filtered value ="<<acc<<endl;
				data_out.write(acc);
				valid_out.write(true);
			}
			else if(new_sample&&!valid_in.read()){//on the current sample, valid_in went from high to low
				//cerr<<"waiting for sample"<<endl;
				new_sample=false; //the process will wait for a new rising edge of valid_in
				valid_out.write(false);
			}
		}
		
	}
} ;

#endif

