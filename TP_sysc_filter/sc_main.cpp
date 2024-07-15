//
// Example: simulation of a FIR based on Siemens examples
// 
// Matthieu ARZEL -- IMT Atlantique
// 01/2023
#include "sc_main.h"

int sc_main(int argc, char *argv[])
 {
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

	sc_signal<bool>				clk("clk");//100MHz clock
	sc_signal<bool>				audio_clk("audio_clk");//48kHz clock
	sc_signal<bool>				rst("rst");
	sc_signal<d_type>			data_in("data_in"); //simplest handshake: when data is available, a VALID signal is HIGH so that DAT can be read
	sc_signal<bool> 			valid_in("valid_in");
	sc_signal<d_type>			data_out("data_out");
	sc_signal<bool>				valid_out("valid_out");
	sc_signal< c_type >			coeffs[N_TAPS];

	sc_trace_file *tf;


	// Design Under Test (DUT)
	CCS_DESIGN(top_level)(top_level_inst)("TOP_LEVEL_INST") ;
		top_level_inst.clk(clk);
		top_level_inst.rst(rst);
		top_level_inst.data_in(data_in);
		top_level_inst.valid_in(valid_in);
		top_level_inst.data_out(data_out);
		top_level_inst.valid_out(valid_out);
		for (int i=0;i<N_TAPS; i++) {
			top_level_inst.coeffs[i](coeffs[i]) ;
		}

	// Stimulus
	STIM STIM_INST("STIM_INST") ;
		STIM_INST.clk(clk);
		STIM_INST.audio_clk(audio_clk);
		STIM_INST.rst(rst);
		STIM_INST.data_in(data_in);
		STIM_INST.valid_in(valid_in);
		STIM_INST.data_out(data_out);
		STIM_INST.valid_out(valid_out);
		for (int i=0;i<N_TAPS; i++) {
			STIM_INST.coeffs[i](coeffs[i]) ;
		}
	// Waves:
		tf = sc_create_vcd_trace_file("waves");
		tf->set_time_unit(1, SC_NS);
		sc_trace(tf, clk, "clk");
		sc_trace(tf, rst, "rst");
		sc_trace(tf, audio_clk, "audio_clk");
		sc_trace(tf, data_in, "data_in");
		sc_trace(tf, valid_in, "valid_in");
		sc_trace(tf, data_out, "data_out");
		sc_trace(tf, valid_out, "valid_out");

		sc_start();
		sc_close_vcd_trace_file(tf);
		return (0);
}
