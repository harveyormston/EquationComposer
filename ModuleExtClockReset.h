/*
 *  +----------------------+
 *  | ModuleExtClockReset  |
 *  |----------------------|
 *  > clock_input          |
 *  |               output >
 *  +----------------------+
 *
 *  ------------------------------------------------------------------------------
 *  Detect a reset on the external clock. A reset is triggered if no clock pulse has been
 *  received on the external clock input for 4 seconds
*/

#ifndef ModuleExtClockReset_h
#define ModuleExtClockReset_h

#include "Arduino.h"
#include "Module.h"

class ModuleExtClockReset : public Module
{
  public:
    ModuleExtClockReset();
    uint16_t compute();

    // Inputs
    Module *clock_input;

  private:
    uint32_t rate;
    boolean ext_clocked;
    uint32_t ext_clock_counter = 88400;
};

#endif
