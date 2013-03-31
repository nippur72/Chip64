//---------------------------------------------------------------------------

#pragma hdrstop

#include "PLL.h"

PLL::PLL()
{
   amp_buf = 0;
   half_table = 0;
   amp_delay = 0;

   AVF = 0;
}

PLL::~PLL()
{
   if(amp_buf)    delete [] amp_buf;
   if(half_table) delete [] half_table;
   if(AVF)        delete [] AVF;
}

void PLL::SetSize(int s)
{
   n_steps = s;

   if(amp_buf)    delete [] amp_buf;
   if(half_table) delete [] half_table;
   if(AVF)        delete [] AVF;

   amp_buf    = new float[n_steps];
   half_table = new int[n_steps];
   AVF        = new DelayLine[n_steps];

   for(int t=0;t<n_steps;t++)
   {
      half_table[t] = (t+(n_steps/2)) % n_steps;
   }
   Reset();
}

void PLL::Reset()
{
   for(int i=0;i<n_steps;i++) amp_buf[i]=0.0;
}

void PLL::SetDelay(int delay)
{
   amp_delay = delay;
   for(int t=0;t<n_steps;t++) AVF[t].SetSize(delay);
}

// *** This clock routine adapted from Moe Wheatley AE4JY WinPSK *** //

bool PLL::SymbolSynch(float ampl)
{
   bool trigger;

   // perform averaging of a single step
   if(amp_delay==0) amp_buf[current_step] = ampl;
   else             amp_buf[current_step] = (amp_buf[current_step]*(amp_delay-1.0) + ampl)/amp_delay;

   // see if at middle of symbol
   if(current_step==Peak_Pos) trigger = true;
   else trigger = false;
   last_peak_pos = Peak_Pos;

   // don't change pk pos until halfway into next bit.
   if(current_step==half_table[Peak_Pos]) Peak_Pos = New_Peak_Pos;

   current_step++;

   // here every symbol time
   step_clock += 1000;
   if(step_clock >= (n_steps*1000))
   {
       step_clock -= (n_steps*1000);  // keep phase bounded
       current_step = 0;
       float max = amp_buf[0];
       for(int i=0;i<n_steps;i++)
       {
          if(amp_buf[i] >= max)
          {
            New_Peak_Pos = i;
            max = amp_buf[i];
          }
       }
   }
   return trigger;
}

// *** This clock routine adapted from Moe Wheatley AE4JY WinPSK *** //
// version with average filters
bool PLL::SymbolSynchAVF(float ampl)
{
   bool trigger;

   // perform averaging of a single step
   AVF[current_step].Delay(ampl);
   amp_buf[current_step] = AVF[current_step].Average();

   // see if at middle of symbol
   if(current_step==Peak_Pos) trigger = true;
   else trigger = false;
   last_peak_pos = Peak_Pos;

   // don't change pk pos until halfway into next bit.
   if(current_step==half_table[Peak_Pos]) Peak_Pos = New_Peak_Pos;

   current_step++;

   // here every symbol time
   step_clock += 1000;
   if(step_clock >= (n_steps*1000))
   {
       step_clock -= (n_steps*1000);  // keep phase bounded
       current_step = 0;
       float max = amp_buf[0];
       for(int i=0;i<n_steps;i++)
       {
          if(amp_buf[i] >= max)
          {
            New_Peak_Pos = i;
            max = amp_buf[i];
          }
       }
   }
   return trigger;
}



bool PLL::SymbolSynch_simple(float ampl)
{
   //amp_buf[current_step] = ampl;

   if(amp_delay==0) amp_buf[current_step] = ampl;
   else             amp_buf[current_step] = (amp_buf[current_step]*(amp_delay-1.0) + ampl)/amp_delay;

   current_step++;
   if(current_step >= n_steps)
   {
      current_step = 0;
      float max = amp_buf[0];
      for(int i=0;i<n_steps;i++)
      {
         if(amp_buf[i] >= max)
         {
           last_peak_pos = i;
           max = amp_buf[i];
         }
      }
      return true;
   }
   return false;
}


/*
// with scan range
bool PLL::SymbolSynch_simple(float ampl)
{
   if(amp_delay==0) amp_buf[current_step] = ampl;
   else             amp_buf[current_step] = (amp_buf[current_step]*(amp_delay-1.0) + ampl)/amp_delay;

   current_step++;
   if(current_step >= n_steps)
   {
      current_step = 0;
      float max = amp_buf[last_peak_pos];
      int range = 21;
      int start = last_peak_pos-range; if(start<0) start = 0;
      int end   = last_peak_pos+range; if(end>n_steps) end = n_steps;

      for(int i=start;i<end;i++)
      {
         if(amp_buf[i] >= max)
         {
           last_peak_pos = i;
           max = amp_buf[i];
         }
      }
      return true;
   }
   return false;
}
*/
