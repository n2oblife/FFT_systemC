//
// Copyright 2003-2015 Siemens
//

#ifndef __STIM_H__
#define __STIM_H__
#include "FIR_TYPES.h"
#include "COEFFS_DOUBLE.h"
#include "math.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std ;

#define MY_2PI 2*3.14159265358979323846

// for comparing expected results vs actual
double FIR_FILTER_REFERENCE (
	double	&data_in,
	double	coeffs[N_TAPS]
) {

	static double taps[N_TAPS];

	double acc;

	SHIFT:for(int i=(N_TAPS-1);i>=0;i--) {
		taps[i] = (i==0) ? data_in : taps[i-1] ;
	}
	acc = 0 ;
	MAC:for(int i=0;i<N_TAPS;i++) {
		acc += coeffs[i] * taps[i] ;
	}
	return acc ;
}

SC_MODULE(STIM) { 
	sc_out<bool> clk; 
	sc_out<bool> audio_clk; 
	sc_out<bool> rst;
	sc_out<d_type>			data_in;
	sc_out<bool>			valid_in;
	sc_in<d_type>			data_out;
	sc_in<bool>				valid_out;
	sc_out<c_type>			coeffs[N_TAPS];

	bool				stop;
	sc_fifo<d_type> data_copy ;

	// Constructor 
	SC_CTOR(STIM) : 
		clk("clk"),
		audio_clk("audio_clk"),
		rst("rst"),
		data_in("data_in"),
		valid_in("valid_in"),
		data_out("data_out"),
		valid_out("valid_out"),
		data_copy(128)
		{ 
			SC_THREAD(stimulus_wave); 
			sensitive << audio_clk.pos();
			SC_THREAD(wave_consume); 
			sensitive << audio_clk.pos();
			SC_THREAD(clock_generator) ;
			SC_THREAD(audio_clock_generator) ;
		}

	void stimulus_wave() {
		cout << "stimulus_wave thread started" << endl ;
		ofstream INPUT_SIGNAL("input_signal.txt");
		//data_in.reset_write() ;
		rst.write(1) ;
		stop = false ;
		c_type c;
		// set up coefficients
		for (int i=0;i<N_TAPS;i++) {
			coeffs[i].write(coeffs_double[i]) ;
			cout <<"coeffs("<<i<<") <= std_logic_vector(to_signed("<<(int) round(coeffs_double[i]*pow(2.,COEFF_WIDTH-2))<<", "<<COEFF_WIDTH<<"));"<<endl;
		}
		cout<<endl;
		cerr<<"here"<<endl;
		//wait(3); // three clock cycles
		rst.write(0) ;
		//wait(20);
		// start stimulus
		cerr << "Starting to send data stream" << endl ;
		double wave1_amp = 120 ;
		double wave2_amp = 20 ;

		double sample_freq = 48000 ;
		double wave1_freq = 1 ;
		double wave2_freq = 300 ;


		for (int i=0; i<50;i++) { //i<sample_freq*3
			wait();
			double wave = sin(((double)i)/(sample_freq/wave1_freq)*MY_2PI) * wave1_amp 
						+ sin(((double)i)/(sample_freq/wave2_freq)*MY_2PI) * wave2_amp ;
			d_type temp = wave ;
			data_in.write(temp) ;
			valid_in.write(true); 
			data_copy.write(temp) ;
			INPUT_SIGNAL << temp.to_int() << endl ;
			cout<<"audio_sample #"<<i<<" sent to filter"<<endl;
			wait();
			valid_in.write(false); // protocol used to inform that one sample was sent
		}
		wait();
		valid_in.write(false);
		cout << "Stopping SystemC simulation" << endl ;
		INPUT_SIGNAL.close() ;
		stop = true ;
		wait(8) ;
		sc_stop(); // stop simulation when 8 cycles done
	}

	void wave_consume() {
		cout << "wave_consume thread started" << endl ;
		ofstream OUTPUT_SIGNAL("output_signal.txt");
		//data_out.reset_read() ;
		cout << "Starting to consume from DUT" << endl ;
		d_type temp ;
		double temp_double ;
		double worst_error = 0 ;
		double diff ;
		wait() ;
		while (!stop) {
			wait();
			if(valid_out.read()){
				///cerr<<"sample filtered"<<endl;
				temp = data_out.read();
				OUTPUT_SIGNAL << temp.to_int() << endl ;
				temp_double = data_copy.read().to_double() ;
				temp_double = FIR_FILTER_REFERENCE(temp_double, coeffs_double) ;
				cout<<temp.to_double()<<"(HW) "<<temp_double<<" (SW)"<<endl ;
				diff = temp.to_double() - temp_double ;
				diff = (diff<0) ? -diff : diff ;
				worst_error = (diff > worst_error) ? diff : worst_error ;
			}
		}
		cout << "Worst error compared with double precision = " << worst_error << endl ;
		OUTPUT_SIGNAL.close() ;
	}


	void clock_generator() { //5MHz to have more 100 cycles to run the filter
		cout << "Clock Generator thread running" << endl ;
		while (true) {
			clk = 0 ;
			wait(100,SC_NS) ;
			clk = 1 ;
			wait(100,SC_NS) ;
		}
	}
	
	void audio_clock_generator() { //approximately 96 kHz so that valid_in frequency is approximately equal to 48kHz
		cout << "Audio Clock Generator thread running" << endl ;
		while (true) {
			audio_clk = 0 ;
			//cerr<<"0 ";
			wait(5208,SC_NS) ; // 10417/2 so that the sample feeder wakes up one cycle to provide a sample with valid=high and another cycle 
								// to put valid=low so that the consumer knows a sample was sent
			audio_clk = 1 ;
			//cerr<<"1 ";
			wait(5208,SC_NS) ;
		}
	}
	

};
#endif
