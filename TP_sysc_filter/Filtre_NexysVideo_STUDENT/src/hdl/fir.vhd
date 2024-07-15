library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity fir is

  generic (
    dwidth : natural := 24;
    ntaps  : natural := 15);

  port (
    din          : in  std_logic_vector(dwidth-1 downto 0);
    dout         : out std_logic_vector(dwidth-1 downto 0);
    config_sw    : in  std_logic_vector(4 downto 0);  --inutilise dans le TP majeure
    clk          : in  std_logic;
    rst          : in  std_logic;
    ce           : in  std_logic;  -- signal de validation de din a la frequence des echantillons audio
    dbg_output_0 : out std_logic_vector(7 downto 0);  --inutilise dans le TP majeure
    dbg_output_1 : out std_logic_vector(7 downto 0);  --inutilise dans le TP majeure
    dbg_output_2 : out std_logic;       --inutilise dans le TP majeure
    dbg_output_3 : out std_logic;       --inutilise dans le TP majeure
    dbg_output_4 : out std_logic       --inutilise dans le TP majeure
--    dout_valid   : out std_logic
    );

end fir;

architecture myarch of fir is

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

  type coeffArray is array(0 to 15) of std_logic_vector(23 downto 0);
  signal D_in, D_out : std_logic_vector(23 downto 0);
  signal coeffs,coeffs0,coeffs1, coeffs2, coeffs3 : coeffArray;

begin  -- myarch

  -- octave:
    --   a=.9; (round(fir1(15, a)/sqrt(sum(fir1(15, a).^2))*2**22))'

  coeffs0(0) <= std_logic_vector(to_signed(         31844, 24));
  coeffs0(1) <= std_logic_vector(to_signed(         10391, 24));
  coeffs0(2) <= std_logic_vector(to_signed(         34092, 24));
  coeffs0(3) <= std_logic_vector(to_signed(        -27474, 24));
  coeffs0(4) <= std_logic_vector(to_signed(       -366783, 24));
  coeffs0(5) <= std_logic_vector(to_signed(       -159217, 24));
  coeffs0(6) <= std_logic_vector(to_signed(      -1786435, 24));
  coeffs0(7) <= std_logic_vector(to_signed(       2332771, 24));
  coeffs0(8) <= std_logic_vector(to_signed(       2332771, 24));
  coeffs0(9) <= std_logic_vector(to_signed(      -1786435, 24));
  coeffs0(10) <= std_logic_vector(to_signed(      -159217, 24));
  coeffs0(11) <= std_logic_vector(to_signed(      -366783, 24));
  coeffs0(12) <= std_logic_vector(to_signed(       -27474, 24));
  coeffs0(13) <= std_logic_vector(to_signed(        34092, 24));
  coeffs0(14) <= std_logic_vector(to_signed(        10391, 24));
  coeffs0(15) <= std_logic_vector(to_signed(        31844, 24));

   -- octave:
  --   a=.3; (round(fir1(15, a)/sqrt(sum(fir1(15, a).^2))*2**22))'

   coeffs1(0) <= std_logic_vector(to_signed(       19781, 24));
   coeffs1(1) <= std_logic_vector(to_signed(       -8713, 24));
   coeffs1(2) <= std_logic_vector(to_signed(     -101865, 24));
   coeffs1(3) <= std_logic_vector(to_signed(     -210031, 24));
   coeffs1(4) <= std_logic_vector(to_signed(      -65796, 24));
   coeffs1(5) <= std_logic_vector(to_signed(      589332, 24));
   coeffs1(6) <= std_logic_vector(to_signed(     1611746, 24));
   coeffs1(7) <= std_logic_vector(to_signed(     2406610, 24));
   coeffs1(8) <= std_logic_vector(to_signed(     2406610, 24));
   coeffs1(9) <= std_logic_vector(to_signed(     1611746, 24));
   coeffs1(10) <= std_logic_vector(to_signed(     589332, 24));
   coeffs1(11) <= std_logic_vector(to_signed(     -65796, 24));
   coeffs1(12) <= std_logic_vector(to_signed(    -210031, 24));
   coeffs1(13) <= std_logic_vector(to_signed(    -101865, 24));
   coeffs1(14) <= std_logic_vector(to_signed(      -8713, 24));
   coeffs1(15) <= std_logic_vector(to_signed(      19781, 24));

  
   -- octave:
  --   a=.001; (round(fir1(15, a)/sqrt(sum(fir1(15, a).^2))*2**22))'

  coeffs2(0) <= std_logic_vector(to_signed(   137359  , 24));
  coeffs2(1) <= std_logic_vector(to_signed(   205642  , 24));
  coeffs2(2) <= std_logic_vector(to_signed(   398685  , 24));
  coeffs2(3) <= std_logic_vector(to_signed(   683108  , 24));
  coeffs2(4) <= std_logic_vector(to_signed(   1009732 , 24));
  coeffs2(5) <= std_logic_vector(to_signed(   1322081 , 24));
  coeffs2(6) <= std_logic_vector(to_signed(   1566147 , 24));
  coeffs2(7) <= std_logic_vector(to_signed(   1699729 , 24));
  coeffs2(8) <= std_logic_vector(to_signed(   1699729 , 24));
  coeffs2(9) <= std_logic_vector(to_signed(   1566147 , 24));
  coeffs2(10) <= std_logic_vector(to_signed(  1322081 , 24));
  coeffs2(11) <= std_logic_vector(to_signed(  1009732 , 24));
  coeffs2(12) <= std_logic_vector(to_signed(  683108  , 24));
  coeffs2(13) <= std_logic_vector(to_signed(  398685  , 24));
  coeffs2(14) <= std_logic_vector(to_signed(  205642  , 24));
  coeffs2(15) <= std_logic_vector(to_signed(  137359  , 24));

     -- octave:
  --  a=[.2 .9]; (round(fir1(15, a,"pass")/sqrt(sum(fir1(15, a,"pass").^2))*2**22))'


  coeffs3(0) <= std_logic_vector(to_signed(        31844 , 24));
  coeffs3(1) <= std_logic_vector(to_signed(        10391 , 24));
  coeffs3(2) <= std_logic_vector(to_signed(        34092 , 24));
  coeffs3(3) <= std_logic_vector(to_signed(       -27474 , 24));
  coeffs3(4) <= std_logic_vector(to_signed(      -366783 , 24));
  coeffs3(5) <= std_logic_vector(to_signed(      -159217 , 24));
  coeffs3(6) <= std_logic_vector(to_signed(     -1786435 , 24));
  coeffs3(7) <= std_logic_vector(to_signed(      2332771 , 24));
  coeffs3(8) <= std_logic_vector(to_signed(      2332771 , 24));
  coeffs3(9) <= std_logic_vector(to_signed(     -1786435 , 24));
  coeffs3(10) <= std_logic_vector(to_signed(     -159217 , 24));
  coeffs3(11) <= std_logic_vector(to_signed(     -366783 , 24));
  coeffs3(12) <= std_logic_vector(to_signed(      -27474 , 24));
  coeffs3(13) <= std_logic_vector(to_signed(       34092 , 24));
  coeffs3(14) <= std_logic_vector(to_signed(       10391 , 24));
  coeffs3(15) <= std_logic_vector(to_signed(       31844 , 24));

  prc : process (config_sw(3 downto 0), coeffs0,coeffs1,coeffs2, coeffs3) is
  begin  -- process prc
    case to_integer(unsigned(config_sw(3 downto 0))) is
      when 0      => coeffs <=coeffs0;
      when 1      => coeffs <=coeffs1;
      when 2      => coeffs <=coeffs2;
      when 3      => coeffs <=coeffs3;
      when others => coeffs <= (others => (others => '0'));
    end case;
  end process prc;
  
--FIR over 24 bits an 16 TAPS

  firUnit_1 : entity work.top_level
    port map (
      clk               => clk,
      rst               => rst,
      data_in           => din,
      valid_in          => ce,
      data_out          => D_out,
      valid_out         => open,
      coeffs_0  => coeffs(0) ,
      coeffs_1  => coeffs(1),
      coeffs_2  => coeffs(2),
      coeffs_3  => coeffs(3),
      coeffs_4  => coeffs(4),
      coeffs_5  => coeffs(5),
      coeffs_6  => coeffs(6),
      coeffs_7  => coeffs(7),
      coeffs_8  => coeffs(8),
      coeffs_9  => coeffs(9),
      coeffs_10 => coeffs(10),
      coeffs_11 => coeffs(11),
      coeffs_12 => coeffs(12),
      coeffs_13 => coeffs(13),
      coeffs_14 => coeffs(14),
      coeffs_15 => coeffs(15))
;


-- End of FIR

  dout <= D_out when config_sw(4) = '1' else din;
 
end myarch;
