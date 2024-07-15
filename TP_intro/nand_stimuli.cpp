#include "nand_stimuli.h"



void Nand_stimuli::stim()
{
  wait();
  s1 = 1;
  wait();
  s2 = 1;
  wait();
  s1 = 0;
  wait(1);
  s2 = 0;
  wait();
  s1 = 1;
  s2 = 1;
  wait();
  s2 = 0;
  wait();
  s1 = 0;
  wait(8);
};
 
