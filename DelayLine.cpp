//---------------------------------------------------------------------------

#pragma hdrstop

#include "DelayLine.h"

DelayLine::DelayLine()
{
   buff = 0;
   last = 0;
}

DelayLine::~DelayLine()
{
    if(buff) delete [] buff;
}

void DelayLine::SetSize(int delay_size)
{
   size = delay_size;

   if(buff!=0) delete [] buff;

   buff = new float[size];

   for(int t=0;t<size;t++)
   {
      buff[t] = 0.0;
   }
   last = 0;
}

/*
float DelayLine::Delay(float x)
{
   int i;

   // scroll values
   for(i=size-1;i>0;i--)
   {
      buff[i]=buff[i-1];
   }

   // write input
   buff[0] = x;

   return buff[size-1];
}
*/

float DelayLine::Delay(float x)
{
   float retval = buff[last];
   buff[last] = x;
   last++;
   if(last>=size) last = 0;
   return retval;
}


float DelayLine::Average()
{
   float sum=0;
   for(int t=0;t<size;t++) sum+=buff[t];
   return sum / ((float)size);
}

float DelayLine::FilterAverage(float x)
{
   Delay(x);
   return Average();
}

