//---------------------------------------------------------------------------

#ifndef PLLH
#define PLLH

#include "DelayLine.h"

class PLL
{
public:
   int n_steps;              // number of steps to divide the symbol
   int current_step;         // current step
   int step_clock;           // hiresolution step (in 1000th)

   float *amp_buf;           // averaged amplitude of the symbol (symbol shape)
   float amp_delay;          // IIR factor for step average
   int last_peak_pos;        // position in the array of the last peak detected

   DelayLine *AVF;

   int Peak_Pos;
   int New_Peak_Pos;

   int *half_table;

   PLL();
   ~PLL();

   void SetSize(int nsteps);
   void SetDelay(int delay);
   void Reset();

   bool SymbolSynch(float ampl);
   bool SymbolSynchAVF(float ampl);
   bool SymbolSynch_simple(float ampl);
};

#endif
