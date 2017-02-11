#include "Arduino.h"
#include "defines.h"
#include "SynthArpeggio1.h"

SynthArpeggio1::SynthArpeggio1(Inputs* inputs)
{
  ModuleWavetableOsc *osc = new ModuleWavetableOsc();
  ModuleVCA *vca = new ModuleVCA();
  ModuleArpeggio *arpeggio = new ModuleArpeggio();
  ModuleExtClockReset *seq_reset = new ModuleExtClockReset();
  ModuleENV *env = new ModuleENV();
  ModuleDelay *delay = new ModuleDelay();
  
  arpeggio->clock_input = inputs->gate;
  arpeggio->reset_input = seq_reset;
  arpeggio->root_note_input = inputs->sr;
  arpeggio->pattern_input = inputs->param1;

  // Patch up ocillator
  osc->frequency_input = arpeggio;
  osc->wavetable_input = inputs->mod; 
  
  // Envelope for VCA
  env->trigger_input = inputs->gate;
  env->frequency_input = inputs->param2;
  env->slope_input = new ModuleConstant(2);

  // Patch up VCA
  vca->cv_input = env->output;
  vca->audio_input = osc;
  
  // Patch delay
  delay->audio_input = vca;
  delay->mix_input = inputs->param3;
  delay->feedback_input = new ModuleConstant(2048);
  delay->length_input = inputs->param1;

  this->last_module = delay;
}
