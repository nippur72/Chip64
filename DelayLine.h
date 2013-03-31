//---------------------------------------------------------------------------

#ifndef DelayLineH
#define DelayLineH

class DelayLine
{
public:
   float *buff;
   int size;
   int last;

   DelayLine();
   ~DelayLine();
   void SetSize(int delay_size);

   float Delay(float v);

   float Average();
   float FilterAverage(float x);
};

#endif


