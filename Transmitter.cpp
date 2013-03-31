//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>

#pragma hdrstop
#include <stdlib.h>
#include "Unit1.h"
#include "Sequences.h"
#include "Transmitter.h"
#include "ComplexFir.h"
#include "GoodFFT.h"

#define MAXSAMPLES (44100*10)

extern AnsiString CallSign;

Transmitter::Transmitter()
{
    SampleRate  = 44100;
    pixelsize   = 147;

    modulation  = MODE_BPSK;
    freq = 1000;
    freqoffset = 0.0;
    Samples = new float[MAXSAMPLES];
}

void Transmitter::SetPnSeq()
{
    pnsize = PnSeq[0].size;
}

Transmitter::~Transmitter()
{
    delete [] Samples;
}

void Transmitter::PrepareTX()
{
    Inew = 1;
    Iold = 0;
    Qnew = 1;
    Qold = 0;
    phase = 0;

    _Inew[0] = 1;
    _Inew[1] = 1;
    _Inew[2] = 1;
    _Inew[3] = 1;

    _phase[0] = 0;
    _phase[1] = 0;
    _phase[2] = 0;
    _phase[3] = 0;

    Stream = "";
    NSamples = 0;
    //Fec.Reset();
}

void Transmitter::SendChar(int ch)
{
    //Stream += Fec.Encode(VC.EncodeChar(ch));
    Stream += VC.EncodeChar(ch);
    ProcessStream();
}

void Transmitter::SendPreamble()
{
    SendChar(0);
    SendChar(1);
    for(int t=1;t<=CallSign.Length();t++) SendChar(CallSign.LowerCase()[t]);
    SendChar(2);
}

void Transmitter::SendPostamble()
{
    SendChar(4);
    SendChar(0);
    SendChar(0);
    SendChar(0);
}

void Transmitter::ProcessStream()
{
    AnsiString Dummy;

    while(Stream.Length()>=nbits)
    {
      Dummy = Stream.SubString(1,nbits);
      Stream = Stream.SubString(nbits+1,Stream.Length()-nbits);

      int index;
      float polarity;
      bool negative;

      StringToAlphabet(Dummy, nbits, index, negative);

      if(negative) polarity = -1.0;
      else polarity = +1.0;

      for(int t=0;t<pnsize;t++)
      {
         chips[t] = PnSeq[index].chip[t] * polarity;
      }

      /*
      //@@debug
      AnsiString Deb="";
      for(int t=0;t<pnsize;t++)
      {
         Deb += chips[t] == BIT1 ? AnsiString("1") : AnsiString("0");
      }
      Deb = Deb;
      */

      /* debug
      TStringList *s = new TStringList;
      for(int t=0;t<128;t++)
      {
         s->Add(AnsiString(t)+AnsiString(" ")+PnSeq[t].ToString());
      }
      s->SaveToFile("c:\\x.txt");
      delete s;
      */

      chipsize = pnsize;

           if(modulation==MODE_BPSK) ProcessStreamBPSK();
      else if(modulation==MODE_MSK ) ProcessStreamMSK();
      else if(modulation==MODE_QPSK) ProcessStreamQPSK();
    }
}

void Transmitter::ProcessStreamBPSK()
{
    float s,shape,I;

    for(int t=0;t<chipsize;t++)
    {
        // differential encoding
        Iold = Inew; if(chips[t]==-1) Inew = -Inew;

        for(int i=0;i<pixelsize;i++)
        {
           phase += freq * 2*M_PI / SampleRate;
           if(phase>2*M_PI) phase -=2*M_PI;
           s=sin(phase);
           shape=cos( (M_PI/(pixelsize*2))*(float)i );
           shape*=shape;
           I = (Iold*shape + Inew*(1.0-shape))*s;

           Samples[NSamples++] = I;
        }
    }
}


void Transmitter::ProcessStreamMSK()
{
    float s,shape,I;

    float baudrate = 150/2;

    for(int t=0;t<chipsize;t++)
    {
        float shift;

        if(chips[t]==-1) shift=-baudrate; else shift=baudrate;

        for(int i=0;i<pixelsize;i++)
        {
           phase += (freq+shift) * 2*M_PI / SampleRate;
           if(phase>2*M_PI) phase -=2*M_PI;
           I = sin(phase);
           Samples[NSamples++] = I;
        }
    }
}


void Transmitter::ProcessStreamQPSK()
{
    float s,c,shape,I,Q;

    static int last_state;
    int curr_state;

    for(int t=0;t<chipsize;t+=2)
    {
        // differential encoding
        Iold = Inew;
        Qold = Qnew;

        I = chips[t];
        Q = chips[t+1];
        //Q = QDL.Delay(chips[t+1]);

             if(I==-1 && Q==-1) curr_state = (last_state + 2) & 3;
        else if(I==-1 && Q==+1) curr_state = (last_state + 1) & 3;
        else if(I==+1 && Q==-1) curr_state = (last_state + 3) & 3;
        else if(I==+1 && Q==+1) curr_state = (last_state + 0) & 3;

             if(curr_state==0) { Inew =  1; Qnew= 0; }
        else if(curr_state==1) { Inew =  0; Qnew=-1; }
        else if(curr_state==2) { Inew = -1; Qnew= 0; }
        else if(curr_state==3) { Inew =  0; Qnew= 1; }

        last_state = curr_state;

        for(int i=0;i<pixelsize;i++)
        {
           phase += freq * 2*M_PI / SampleRate;
           if(phase>2*M_PI) phase -=2*M_PI;
           s=sin(phase);
           c=cos(phase);
           shape=cos( (M_PI/(pixelsize*2))*(float)i );
           shape*=shape;
           I = (Iold*shape + Inew*(1.0-shape))*s;
           Q = (Qold*shape + Qnew*(1.0-shape))*c;

           Samples[NSamples++] = I+Q;
        }
    }
}

void Transmitter::StringToAlphabet(AnsiString Dummy, int nbits, int &index, bool &negative)
{
    index = 0;
    int t;
    if(Dummy[1]=='0')
    {
       negative = false;
       for(t=0;t<nbits-1;t++)
       {
          if(Dummy[nbits-t]=='1') index |= (1<<t);
       }
    }
    else
    {
       negative = true;
       for(t=0;t<nbits-1;t++)
       {
          if(Dummy[nbits-t]=='0') index |= (1<<t);
       }
    }
}

