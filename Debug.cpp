
#pragma hdrstop

#include "Debug.h"

Debug::Debug()
{
   ntimes = 0;
   accumulated_counter.LowPart = 0;
   debug_on_exit = false;

   QueryPerformanceFrequency(&FrequencyCounter);
}

Debug::~Debug()
{
   if(ntimes==0) return;
   if(!debug_on_exit) return;

   TStringList *L = new TStringList;

   double elapsed = 1000.0*((double)accumulated_counter.LowPart)/((double)FrequencyCounter.LowPart);
   double average_elapsed = elapsed / (double) ntimes;

   L->Add("Number of times called:"+AnsiString(ntimes));
   L->Add("Elapsed time msec:"+AnsiString(elapsed));
   L->Add("Average elapsed time msec:"+AnsiString(average_elapsed));

   L->SaveToFile("c:\\debug.txt");

   delete L;
}

void Debug::Start()
{
   QueryPerformanceCounter(&count);
}

void Debug::End()
{
   LARGE_INTEGER nowcount;
   QueryPerformanceCounter(&nowcount);

   int elapsed = nowcount.LowPart-count.LowPart;
   accumulated_counter.LowPart += elapsed;
   ntimes++;

   elapsed_msec = 1000.0*((float)elapsed)/((float)FrequencyCounter.LowPart);
}


