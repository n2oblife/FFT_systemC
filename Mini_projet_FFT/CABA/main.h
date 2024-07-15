//  main.h

#include <systemc.h>
#include "source.h"
#include "fft.h"
#include "sink.h"
#include "fft_types.h"

SC_MODULE (TOP) {
  
  // signals
  sc_clock clk;

  sc_signal<bool> data_req_sink;
  sc_signal<bool> data_req_fft;
  sc_signal<bool> data_valid_source;
  sc_signal<bool> data_valid_fft;

  sc_signal<d_type> source_fft_real;
  sc_signal<d_type> source_fft_img ;
  sc_signal<d_type> fft_sink_real  ;
  sc_signal<d_type> fft_sink_img   ;


  // instanciate
  SOURCE SOURCE1;
  FFT FFT1; 
  SINK SINK1;

 SC_CTOR(TOP):
    clk("clk", 10, SC_NS, 0.5),
    // source_fft("source_fft", 16),
    // fft_sink("fft_sink", 16),
    FFT1("FFT_PROCESS"),
    SOURCE1("SOURCE_PROCESS"),
    SINK1("SINK_PROCESS")
      {

        FFT1.clk(clk);
        FFT1.in_real(source_fft_real);
        FFT1.in_img(source_fft_img);
        FFT1.out_real(fft_sink_real);
        FFT1.out_img(fft_sink_img);
        FFT1.data_valid_source(data_valid_source);
        FFT1.data_req_sink(data_req_sink);
        FFT1.data_valid_sink(data_valid_fft);
        FFT1.data_req_source(data_req_fft);

        SOURCE1.clk(clk);
        SOURCE1.out_img(source_fft_img);
        SOURCE1.out_real(source_fft_real);
        SOURCE1.data_req(data_req_fft);
        SOURCE1.data_valid(data_valid_source);

        SINK1.clk(clk);
        SINK1.in_img(fft_sink_img);
        SINK1.in_real(fft_sink_real);
        SINK1.data_req(data_req_sink);
        SINK1.data_valid(data_valid_fft);

      }
};

