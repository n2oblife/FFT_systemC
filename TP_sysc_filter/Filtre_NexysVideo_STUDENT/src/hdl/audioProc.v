//                              -*- Mode: Verilog -*-
// Filename        : audioProc.v
// Description     : Audio processing project for IMTA A1S2 Labs in digital electronics, based on looper project by Digilent Inc.
// Author          : Matthieu Arzel
// Created On      : Fri Feb  8 11:16:35 2019
// Last Modified By: Matthieu Arzel
// Last Modified On: Fri Feb  8 11:16:35 2019
// Update Count    : 0
// Status          : Unknown, Use with caution!

`timescale 1ns / 1ps

module audioProc(

		 
		 input 	BTNL,
		 input 	BTNR,
		 input 	BTND,
		 input 	BTNC,
		 input 	BTNU,
		 //    input JA1,
		 //    input JA2,
		 //    input JA3,
		 //    input JA4,

		 input 	CLK100MHZ,
		 input 	rstn,
		 input 	sw,
		 //input [3:0]sw,
		 input 	sw3,
		 input 	sw4,
		 input 	sw5,
		 input 	sw6,
		 input 	sw7,
		 output led3,
		 output led4,
		 output led5,
		 output led6,
		 output led7,

		 inout 	scl,
		 inout 	sda,

		 output ac_mclk,
		 input 	ac_adc_sdata,
		 output ac_dac_sdata,
		 output ac_bclk,
		 output ac_lrclk

		 );

   wire 		rst;
   assign rst = ~rstn;
   wire 		clk50;
   parameter tenhz = 10000000;
   
   

   wire [4:0] 		buttons_i;
   assign buttons_i = {BTNU, BTNR, BTNC, BTND, BTNL};
   
   reg [21:0] 		max_block=0;
   
   wire 		set_max;
   wire 		reset_max;
   
   
   wire [4:0] 		buttons_db;//Debounced buttons
   
   wire 		data_flag;
   reg [23:0] 		sound_dataL;
   reg [23:0] 		sound_dataR;
   wire 		data_ready;
   
   wire 		mix_data;
   wire [21:0] 		block48KHz;
   
   wire 		clk_out_100MHZ;
   wire 		clk_out_200MHZ;
   
   
   //////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////    clk_wiz instantiation and wiring
   //////////////////////////////////////////////////////////////////////////////////////////////////////////
   clk_wiz_0 clk_1
     (
      // Clock in ports
      .clk_in1(CLK100MHZ),
      // Clock out ports  
      .clk_out1(clk_out_100MHZ),
      .clk_out2(clk_out_200MHZ),
      .clk_out3(ac_mclk),
      .clk_out4(clk50),
      // Status and control signals        
      .locked()            
      );     

   //////////////////////////////////////////////////////////////////////////////////////////////////////////
       ////    Audio Initialization via TWI
       ////////////////////////////////////////////////////////////////////////////////////////////////////////// 

   audio_init initialize_audio
     (
      .clk(clk50),
      .rst(rst),
      .sda(sda),
      .scl(scl)
      );


   wire [23:0] 		mixL;
   wire [23:0] 		mixR;


   debounce dbuttons(
		     .clock(clk_out_100MHZ),
		     .reset(rst),
		     .button(buttons_i),
		     .out(buttons_db)
		     );

   

   
   

   ////////////////////////////////////////////////////////////////////////////////////////////////////////
     // Audio input and output
   ////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   wire [23:0] 		in_audioL;
   wire [23:0] 		in_audioR;
   wire [23:0] 		out_audioL;
   wire [23:0] 		out_audioR;
   
   i2s_ctl audio_inout(
		       .CLK_I(clk_out_100MHZ),    //Sys clk
		       .RST_I(rst),    //Sys rst
		       .EN_TX_I(1),  // Transmit Enable (push sound data into chip)
		       .EN_RX_I(1), //Receive enable (pull sound data out of chip)
		       .FS_I(4'b0101),     //Sampling rate selector
		       .MM_I(0),     //Audio controller Master mode select
		       .D_L_I(mixL),    //Left channel data input from mix (mixed audio output)
		       .D_R_I(mixR),   //Right channel data input from mix
		       .D_L_O(in_audioL),    // Left channel data (input from mic input)
		       .D_R_O(in_audioR),    // Right channel data (input from mic input)
		       .BCLK_O(ac_bclk),   // serial CLK
		       .LRCLK_O(ac_lrclk),  // channel CLK
		       .SDATA_O(ac_dac_sdata),  // Output serial data
		       .SDATA_I(ac_adc_sdata)   // Input serial data
		       ); 
   
   reg 			lrclkD1=0;
   reg 			lrclkD2=0;
   
   always@(posedge(clk_out_100MHZ))begin
      lrclkD1<=ac_lrclk;
      lrclkD2<=lrclkD1;
   end
   
    reg pulse48kHz;
    wire lrclkrise;
    assign lrclkrise = lrclkD1 & ~lrclkD2;
    reg[3:0] lrclkcnt=0;
    
    always@(posedge(clk_out_100MHZ))begin
        if (lrclkcnt==15)begin
            pulse48kHz<=1;
            lrclkcnt<=0;
            end
        else
            pulse48kHz<=0;
            if (lrclkrise)lrclkcnt<=lrclkcnt+1;
    end
   //////////////////////////////
   //FIR filter
   // Marz
   /////////////////////////////
   wire [23:0] inputLeftSample, inputRightSample,outputLeftSample,outputRightSample;
   wire [4:0] configSw;

   assign inputLeftSample = in_audioL;
   assign inputRightSample = in_audioR;
   assign configSw[0]=sw3;
   assign configSw[1]=sw4;
   assign configSw[2]=sw5;
   assign configSw[3]=sw6;
   assign configSw[4]=sw7;
   assign led3=sw3;
   assign led4=sw4;
   assign led5=sw5;
   assign led6=sw6;
   assign led7=sw7;

   fir #(24,16) leftFir 
     (
      inputLeftSample,
      outputLeftSample,
      configSw,//config_sw, //   : in  std_logic_vector(3 downto 0);  --inutilise dans le TP majeure
      clk_out_100MHZ, //         : in  std_logic;
      rst,//         : in  std_logic;
      pulse48kHz//           : in  std_logic;  -- signal de validation de din a la frequence des echantillons audio
      );
   fir #(24,16) rightFir 
     (
      inputRightSample,
      outputRightSample,
      configSw,//config_sw, //   : in  std_logic_vector(3 downto 0);  --inutilise dans le TP majeure
      clk_out_100MHZ, //         : in  std_logic;
      rst,//         : in  std_logic;
      pulse48kHz//           : in  std_logic;  -- signal de validation de din a la frequence des echantillons audio
      );
   
   assign mixL = buttons_db[2] ? in_audioL : outputLeftSample;
   assign mixR = buttons_db[2] ? in_audioR : outputRightSample;


   ////////////////////////////////////////////////////////////////////////////////////////////////////////
       ////    Data in latch
       //////////////////////////////////////////////////////////////////////////////////////////////////////// 

   //Latch audio data input when data_flag goes high
   always@(posedge(clk_out_100MHZ))begin 
      if (data_flag==1)begin
         sound_dataL<=in_audioL;
         sound_dataR<=in_audioR;
      end
   end
   

endmodule
