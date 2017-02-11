#include "Arduino.h"
#include "ModuleExtClockReset.h"
#include "defines.h"

ModuleExtClockReset::ModuleExtClockReset()
{

  // 'ext_clocked' records the status (on or off) of the external clock input
  this->ext_clocked = false;

  // 'ext_clock_count' helps determine whether a reset occurred
  // This counter is incremented whenever there is NO external clock detected.
  // Once this counter reaches a certain level, it's assumed that there is no
  // external clock, and a reset is triggered.
  this->ext_clock_counter = 88400;
}

uint16_t ModuleExtClockReset::compute()
{
  this->ext_clock_counter++;

  // Check value at the external clock input.  If it goes high, then
  // reset the ext_clock_counter

  uint32_t clock_input_value = this->readInput(clock_input);

  if((clock_input_value < MID_CV) && ext_clocked) ext_clocked = false;

  if((clock_input_value >= MID_CV) && !ext_clocked)
  {
    ext_clocked = true;
    ext_clock_counter = 0;
  }

  // If 4 seconds have passed, then trigger a reset
  // 88400 is 4 x 22,100, which is our interrupt rate
  if(ext_clock_counter >= 88400)
  {
    // Avoid overflow of ext_clock_counter
    ext_clock_counter = 88400;
    return(MAX_CV);
  }
  // If there has been a clock pulse on the external clock input
  // recently, then reset is 0
  else
  {
    return(0);
  }
}
