# Environment variable settings
global env
set CATAPULT_HOME "/usr/local/bin/Siemens_EDA/Catapult_Synthesis_2022.2_1-1019737/Mgc_home"
## Set the variable for file path prefixing 
set RTL_TOOL_SCRIPT_DIR /mnt/campux/CHLS/Mini_projet_FFT/Catapult_5/FFT.v3/vivado_concat_v
set RTL_TOOL_SCRIPT_DIR [file dirname [file normalize [info script] ] ]
puts "-- RTL_TOOL_SCRIPT_DIR is set to '$RTL_TOOL_SCRIPT_DIR' "
# Vivado Non-Project mode script starts here
puts "==========================================="
puts "Catapult driving Vivado in Non-Project mode"
puts "==========================================="
set outputDir /mnt/campux/CHLS/Mini_projet_FFT/Catapult_5/FFT.v3/vivado_concat_v
set outputDir $RTL_TOOL_SCRIPT_DIR
create_project -force ip_tcl_concat_v
   read_verilog ../concat_rtl.v
# set up XPM libraries for XPM-related IP like the Catapult Xilinx_FIFO
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY XPM_FIFO} [current_project]
read_xdc $outputDir/concat_rtl.v.xv.sdc
set_property part xc7a200tsbg484-3 [current_project]
