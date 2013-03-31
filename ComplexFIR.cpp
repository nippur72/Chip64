//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ComplexFIR.h"

ComplexFIR::ComplexFIR()
{
     ntaps = 0;
}

void ComplexFIR::Load(AnsiString FileName)
{
     int t;

     if(!FileExists(FileName))
     {
        AnsiString Msg = "Cannot load the filter "+FileName;
        Application->MessageBox(Msg.c_str(),"Load FIR filter",MB_OK | MB_ICONSTOP);
        return;
     }

     TStringList *L = new TStringList;
     L->LoadFromFile(FileName);

     ntaps = L->Values["NTaps"].ToInt();

     for(t=0;t<ntaps;t++)
     {
        lastI[t]=0.0;
        lastQ[t]=0.0;
     }

     for(t=0;t<ntaps;t++)
     {
        h[t] = atof(L->Strings[t+1].c_str());
     }

     delete L;
}

void ComplexFIR::Save(AnsiString FileName)
{
     int t;
     AnsiString Dummy;

     TStringList *L = new TStringList;

     /*
     Dummy = AnsiString("NTaps=") + AnsiString(ntaps);
     L->Add(Dummy);
     */

     for(t=0;t<ntaps;t++)
     {
        Dummy = Dummy.sprintf("%f",h[t]);
        L->Add(Dummy);
     }
     L->SaveToFile(FileName);
    delete L;
}

void ComplexFIR::FilterFIR(float InpI, float InpQ)
{
    lastI[pos] = InpI; lastI[pos+ntaps] = InpI;
    lastQ[pos] = InpQ; lastQ[pos+ntaps] = InpQ;

    pos++;
    if(pos>=ntaps) pos=0;

    float *hptr = &h[0];
    float *Iptr = &lastI[pos];
    float *Qptr = &lastQ[pos];

    float Ix = 0.0;
    float Qx = 0.0;

    /*
    for(int t=0;t<ntaps;t++,hptr++)
    {
       Ix+= (*hptr)*(*Iptr++);
       Qx+= (*hptr)*(*Qptr++);
    }
    */

    float *start = &h[0];
    float *end = &h[ntaps];

    for(hptr=start;hptr<end;hptr++)
    {
       Ix+= (*hptr)*(*Iptr++);
       Qx+= (*hptr)*(*Qptr++);
    }

    I = Ix;
    Q = Qx;
}

void ComplexFIR::FilterReal(float InpI)
{
    lastI[pos] = InpI; lastI[pos+ntaps] = InpI;

    pos++;
    if(pos>=ntaps) pos=0;

    float *hptr = &h[0];
    float *Iptr = &lastI[pos];

    I = 0.0;
    for(int t=0;t<ntaps;t++,hptr++) I+= (*hptr)*(*Iptr++);
}

void ComplexFIR::SetSize(int size)
{
     ntaps = size;
     pos = 0;
     SumI=0;
     SumQ=0;
     for(int t=0;t<ntaps;t++)
     {
       lastI[t]=0;
       lastQ[t]=0;
     }
}

void ComplexFIR::FilterAverage(float InpI, float InpQ)
{
   SumI += InpI - lastI[pos];
   SumQ += InpQ - lastQ[pos];

   I = SumI / ntaps;
   Q = SumQ / ntaps;

   lastI[pos] = InpI;
   lastQ[pos] = InpQ;

   pos++;
   if(pos>=ntaps) pos = 0;
}

void ComplexFIR::DelayLine(float InpI, float InpQ)
{
   pos++;
   if(pos==ntaps) pos=0;

   lastI[pos]=InpI;
   lastQ[pos]=InpQ;

   int j = pos+1;
   if(j==ntaps) j=0;

   I = lastI[j];
   Q = lastQ[j];
}

double WindowHanning(double phase) { return (1.0+cos(phase))/2; }
double WindowHamming(double phase) { return cos(phase/2); } // not exactly ...
double WindowBlackman2(double phase) { return 0.42+0.5*cos(phase)+0.08*cos(2*phase); } // from Freq 5.1 FFT analyzer
double WindowBlackman3(double phase) { return 0.35875+0.48829*cos(phase)+0.14128*cos(2*phase)+0.01168*cos(3*phase); } // from the Motorola BBS

// FIR shape calculation for a flat response from FreqLow to FreqUpp

void WinFirI(float LowOmega, float UppOmega, float *Shape, int Len, float shift, int windowtype)
{
   int i;
   double time,phase,shape;

   for(i=0;i<Len;i++)
   {
       time=i+(1.0-shift)-(float)Len/2;
       phase=2*M_PI*time/Len;
       if(time==0) shape=UppOmega-LowOmega;
       else shape=(sin(UppOmega*time)-sin(LowOmega*time))/time;

            if(windowtype==WINDOW_RECTANGULAR) Shape[i]=shape/M_PI;
       else if(windowtype==WINDOW_HANNING)     Shape[i]=shape*WindowHanning(phase)/M_PI;
       else if(windowtype==WINDOW_HAMMING)     Shape[i]=shape*WindowHamming(phase)/M_PI;
       else if(windowtype==WINDOW_BLACKMAN2)   Shape[i]=shape*WindowBlackman2(phase)/M_PI;
       else if(windowtype==WINDOW_BLACKMAN3)   Shape[i]=shape*WindowBlackman3(phase)/M_PI;
   }
}

void ComplexFIR::CalculateFir(float LowerFrequency, float UpperFrequency, float SampleFrequency, int shapetype)
{
   float LowOmega;
   float UppOmega;
   float shift = 0;
   SampleFrequency /= 2;
   LowOmega = LowerFrequency / SampleFrequency;
   UppOmega = UpperFrequency / SampleFrequency;
   WinFirI(LowOmega*M_PI,UppOmega*M_PI,h,ntaps,shift,shapetype);
}

