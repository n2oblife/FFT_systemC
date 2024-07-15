# written for flow package Vivado 
set sdc_version 1.7 

create_clock -name clk -period 10.0 -waveform { 0.0 5.0 } [get_ports {clk}]
set_clock_uncertainty 0.0 [get_clocks {clk}]

create_clock -name virtual_io_clk -period 10.0
## IO TIMING CONSTRAINTS
set_input_delay -clock [get_clocks {clk}] 0.0 [get_ports {rst}]
set_input_delay -clock [get_clocks {clk}] 0.0 [get_ports {data_valid_source}]
set_input_delay -clock [get_clocks {clk}] 0.0 [get_ports {data_req_sink}]
set_input_delay -clock [get_clocks {clk}] 0.0 [get_ports {in_real[*]}]
set_input_delay -clock [get_clocks {clk}] 0.0 [get_ports {in_img[*]}]
set_output_delay -clock [get_clocks {clk}] 0.0 [get_ports {out_real[*]}]
set_output_delay -clock [get_clocks {clk}] 0.0 [get_ports {out_img[*]}]
set_output_delay -clock [get_clocks {clk}] 0.0 [get_ports {data_valid_sink}]
set_output_delay -clock [get_clocks {clk}] 0.0 [get_ports {data_req_source}]

