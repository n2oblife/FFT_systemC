//  Catapult Ultra Synthesis 2022.2_1/1019737 (Production Release) Mon Nov 21 20:05:27 PST 2022
//  
//          Copyright (c) Siemens EDA, 1996-2022, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                   PROPERTY OF SIEMENS EDA OR ITS LICENSORS.
//  
//  Running on Linux HLS_student@wifi-salsa-197.priv.enst-bretagne.fr 3.10.0-1160.el7.x86_64 x86_64 aol
//  
//  Package information: SIFLIBS v25.2_1.0, HLS_PKGS v25.2_1.0, 
//                       SIF_TOOLKITS v25.2_1.0, SIF_XILINX v25.2_1.0, 
//                       SIF_ALTERA v25.2_1.0, CCS_LIBS v25.2_1.0, 
//                       CDS_PPRO v2022.1, CDS_DesigChecker v2022.2, 
//                       CDS_OASYS v21.1_2.5, CDS_PSR v22.1_0.5, 
//                       DesignPad v2.78_1.0
//  
solution new -state initial
solution options defaults
solution options set /OnTheFly/VthAttributeType cell_lib
solution options set /Input/TargetPlatform x86_64
solution options set /Input/SearchPath /usr/local/bin/Siemens_EDA/Catapult_Synthesis_2022.2_1-1019737/Mgc_home/shared/include
solution options set /Output/GenerateCycleNetlist false
solution file add ./CABA/fft_types.h -type CHEADER
solution file add ./CABA/fft.cpp -type C++
solution file add ./CABA/fft.h -type CHEADER
directive set -DESIGN_GOAL area
directive set -SPECULATE true
directive set -MERGEABLE true
directive set -REGISTER_THRESHOLD 256
directive set -MEM_MAP_THRESHOLD 32
directive set -LOGIC_OPT false
directive set -FSM_ENCODING none
directive set -FSM_BINARY_ENCODING_THRESHOLD 64
directive set -REG_MAX_FANOUT 0
directive set -NO_X_ASSIGNMENTS true
directive set -SAFE_FSM false
directive set -REGISTER_SHARING_MAX_WIDTH_DIFFERENCE 8
directive set -REGISTER_SHARING_LIMIT 0
directive set -ASSIGN_OVERHEAD 0
directive set -TIMING_CHECKS true
directive set -MUXPATH true
directive set -REALLOC true
directive set -UNROLL no
directive set -IO_MODE super
directive set -CHAN_IO_PROTOCOL use_library
directive set -ARRAY_SIZE 1024
directive set -IDLE_SIGNAL {}
directive set -STALL_FLAG_SV off
directive set -STALL_FLAG false
directive set -TRANSACTION_DONE_SIGNAL true
directive set -DONE_FLAG {}
directive set -READY_FLAG {}
directive set -START_FLAG {}
directive set -TRANSACTION_SYNC ready
directive set -RESET_CLEARS_ALL_REGS use_library
directive set -CLOCK_OVERHEAD 20.000000
directive set -ON_THE_FLY_PROTOTYPING false
directive set -OPT_CONST_MULTS use_library
directive set -CHARACTERIZE_ROM false
directive set -PROTOTYPE_ROM true
directive set -ROM_THRESHOLD 64
directive set -CLUSTER_ADDTREE_IN_WIDTH_THRESHOLD 0
directive set -CLUSTER_ADDTREE_IN_COUNT_THRESHOLD 0
directive set -CLUSTER_OPT_CONSTANT_INPUTS true
directive set -CLUSTER_RTL_SYN false
directive set -CLUSTER_FAST_MODE false
directive set -CLUSTER_TYPE combinational
directive set -PROTOTYPING_ENGINE oasys
directive set -PIPELINE_RAMP_UP true
go new
go analyze
go compile
solution library add mgc_Xilinx-ARTIX-7-3_beh -- -rtlsyntool Vivado -manufacturer Xilinx -family ARTIX-7 -speed -3 -part xc7a200tsbg484-3
solution library add Xilinx_RAMS
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 10.0 -CLOCK_UNCERTAINTY 0.0 -CLOCK_HIGH_TIME 5.0}}
go assembly
go assembly
