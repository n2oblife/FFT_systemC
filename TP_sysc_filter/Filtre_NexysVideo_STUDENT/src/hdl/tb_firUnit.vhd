-------------------------------------------------------------------------------
-- Title      : FirUnit
-- Project    : 
-------------------------------------------------------------------------------
-- File       : operativeUnit.vhd
-- Author     : Jean-Noel BAZIN  <jnbazin@pc-disi-026.enst-bretagne.fr>
-- Company    : 
-- Created    : 2018-04-11
-- Last update: 2019-02-26
-- Platform   : 
-- Standard   : VHDL'93/02
-------------------------------------------------------------------------------
-- Description: 8 bit FIR
-------------------------------------------------------------------------------
-- Copyright (c) 2018 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2018-04-11  1.0      jnbazin Created
-- 2018-04-18  1.1      marzel	Modified to add more test inputs
-- 2019-02-26  1.1      marzel  Adapted to 16-tap filtering
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_firUnit is
end entity tb_firUnit;

architecture archi_tb_firUnit of tb_firUnit is
--  component firUnit is
--    port (
--      I_clock               : in  std_logic;
--      I_reset               : in  std_logic;
--      I_inputSample         : in  std_logic_vector(7 downto 0);
--      I_inputSampleValid    : in  std_logic;
--      O_filteredSample      : out std_logic_vector(7 downto 0);
--      O_filteredSampleValid : out std_logic);
--  end component firUnit;

 component top_level IS
  PORT(
    clk : IN STD_LOGIC;
    rst : IN STD_LOGIC;
    data_in : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    valid_in : IN STD_LOGIC;
    coeffs_0 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_1 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_2 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_3 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_4 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_5 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_6 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_7 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_8 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_9 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_10 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_11 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_12 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_13 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_14 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    coeffs_15 : IN STD_LOGIC_VECTOR (23 DOWNTO 0);
    data_out : OUT STD_LOGIC_VECTOR (23 DOWNTO 0);
    valid_out : OUT STD_LOGIC
  );
    end component top_level;


  signal SC_clock               : std_logic := '0';
  signal SC_reset               : std_logic;
  signal SC_inputSample         : std_logic_vector(23 downto 0);
  signal SC_inputSampleValid    : std_logic:='0';
  signal SC_filteredSample      : std_logic_vector(23 downto 0);
  signal SC_filteredSampleValid : std_logic;

begin

  SC_clock <= not SC_clock after 5 ns;
  SC_reset <= '0', '1' after 19 ns, '0' after 57 ns;

  -- Sample period = 20 clk period
  SC_inputSampleValid <= not SC_inputSampleValid after 100 ns;

  -- Null signal followed by a Dirac and then an arbitrary sequence
  SC_inputSample <= "000000000000000000000000",
                    "011111111111111111111111" after 401 ns,
                    "000000000000000000000000" after 601 ns,
                    "000000000000000000100100" after 4201 ns,
                    "000000000000000001100100" after 4401 ns,
                    "000000000000000010100010" after 4601 ns,
                    "111111111111111111011011" after 4801 ns,
                    "111111111111111100001011" after 5001 ns,
                    "111111111111111110000000" after 5201 ns,
                    "111111111111111101111111" after 5401 ns,
                    "111111111111111110111010" after 5601 ns;


-- the filter output on 8 bits is a sequence of signed numbers (with the  assumption
-- of rounding the output, so the accuracy can be slightly different depending
-- on your final stage):
  -- 0
  --   45987
  --   98851
  --  249223
  --  519415
  --  887618
  -- 1288443
  -- 1631039
  -- 1828678
  -- 1828678
  -- 1631039
  -- 1288443
  --  887618
  --  519415
  --  249223
  --   98851
  --   45987
  -- 0
  -- 0
  -- 0
  -- 0
  --  1
  --  3
  --  7
  --  13
  --  21
  --  28
  --  27
  --  17
  --  -6
  --  -36
  --  -71
  --  -102
  --  -124
  --  -136
  --  -137
  --  -131
  --  -123
  --  -117
  --  -113
  --  -110
  --  -110
  --  -109 ...


 firUnit_1 : entity work.top_level
    port map (
      clk               => SC_clock,
      rst               => SC_reset,
      data_in           => SC_inputSample,
      valid_in          => SC_inputSampleValid,
      data_out          => SC_filteredSample,
      valid_out         => SC_filteredSampleValid,
      coeffs_0 =>  std_logic_vector(to_signed(         45987, 24)),
      coeffs_1 =>  std_logic_vector(to_signed(         98851, 24)),
      coeffs_2 =>  std_logic_vector(to_signed(        249223, 24)),
      coeffs_3 =>  std_logic_vector(to_signed(        519415, 24)),
      coeffs_4 =>  std_logic_vector(to_signed(        887618, 24)),
      coeffs_5 =>  std_logic_vector(to_signed(       1288443, 24)),
      coeffs_6 =>  std_logic_vector(to_signed(       1631039, 24)),
      coeffs_7 =>  std_logic_vector(to_signed(       1828678, 24)),
      coeffs_8 =>  std_logic_vector(to_signed(       1828678, 24)),
      coeffs_9 =>  std_logic_vector(to_signed(       1631039, 24)),
      coeffs_10 =>  std_logic_vector(to_signed(      1288443, 24)),
      coeffs_11 =>  std_logic_vector(to_signed(       887618, 24)),
      coeffs_12 =>  std_logic_vector(to_signed(       519415, 24)),
      coeffs_13 =>  std_logic_vector(to_signed(       249223, 24)),
      coeffs_14 =>  std_logic_vector(to_signed(        98851, 24)),
      coeffs_15 =>  std_logic_vector(to_signed(        45987, 24)))
;



end architecture archi_tb_firUnit;
