//---------------------------------------------------------------------------

#ifndef ComplexFIRH
#define ComplexFIRH

#include <vcl.h>

#define WINDOW_RECTANGULAR 0
#define WINDOW_HANNING     1
#define WINDOW_HAMMING     2
#define WINDOW_BLACKMAN2   3
#define WINDOW_BLACKMAN3   4

class ComplexFIR
{
public:
   int ntaps;                 // numero di taps
   float h[2048];             // vettore dei taps
   float lastI[2048];         // vettore degli ultimi elementi
   float lastQ[2048];         // vettore degli ultimi elementi
   float I,Q;
   int pos;

   float SumI,SumQ;

   ComplexFIR();

   void Load(AnsiString FileName);
   void Save(AnsiString FileName);

   void FilterFIR(float I, float Q);
   void FilterReal(float InpR);
   void FilterAverage(float I, float Q);
   void SetSize(int size);
   void DelayLine(float InpI, float InpQ);
   void CalculateFir(float LowerFrequency, float UpperFrequency, float SampleFrequency, int shapetype);
};


//---------------------------------------------------------------------------

#endif
