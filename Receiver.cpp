//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
#include "Receiver.h"
#include "Palette.h"
#include "DebugWindow.h"

extern HellPalette WPal;

//#ifdef INTEGER_MATH
#include "Correlator16_IntegerMath.cpp"
#include "Correlator32_IntegerMath.cpp"
#include "Correlator64_IntegerMath.cpp"
#include "Correlator64_1_IntegerMath.cpp"
#include "Correlator128_IntegerMath.cpp"
//#endif

Receiver::Receiver()
{
    samplerate = 6300;
    pixelsize  = 21;
    modulation = MODE_BPSK;
    freq = 1000;
    String ThePath = ExtractFilePath(Application->ExeName);
    QF.Load(ThePath+"/Filters/normal.fir");
    DL.SetSize(pixelsize);
    PnSeq = 0;
    oversample = 1;
    SetOversample();

    _QF[0].Load(ThePath+"/Filters/normal.fir");
    _QF[1].Load(ThePath+"/Filters/normal.fir");
    _QF[2].Load(ThePath+"/Filters/normal.fir");
    _QF[3].Load(ThePath+"/Filters/normal.fir");
    _DL[0].SetSize(pixelsize);
    _DL[1].SetSize(pixelsize);
    _DL[2].SetSize(pixelsize);
    _DL[3].SetSize(pixelsize);
    _phase[0] = 0;
    _phase[1] = 0;
    _phase[2] = 0;
    _phase[3] = 0;

    BitClock.SetSize(21);
    BitClock.SetDelay(512);
    AVFDelay.SetSize(BitClock.n_steps/2);
    Clocked = false;
    IntegerMath = true;
}

void Receiver::SetPnSeq()
{
    if(Clocked)
    {
      pnsize = PnSeq[0].size;
      CodeBuf.SetSize(pnsize);
      Rxseq.SetSize(pnsize);
      Phaseseq.SetSize(pnsize);
      PhaseBuf.SetSize(pnsize);
      SetOversample();
    }
    else
    {
      pnsize = PnSeq[0].size;
      CodeBuf.SetSize(pnsize*pixelsize);
      Rxseq.SetSize(pnsize);
      Phaseseq.SetSize(pnsize);
      PhaseBuf.SetSize(pnsize*pixelsize);
      SetOversample();
    }
}

void Receiver::SetOversample()
{
    if(!Clocked)
    {
           if(modulation==MODE_QPSK) Clock.SetSize(oversample*pnsize/2);
      else if(modulation==MODE_BPSK) Clock.SetSize(oversample*pnsize);
      else if(modulation==MODE_MSK)  Clock.SetSize(oversample*pnsize);
    }
    else
    {
           if(modulation==MODE_QPSK) Clock.SetSize(pnsize/2);
      else if(modulation==MODE_BPSK) Clock.SetSize(pnsize);
      else if(modulation==MODE_MSK)  Clock.SetSize(pnsize);
    }
}

Receiver::~Receiver()
{
    if(PnSeq) delete [] PnSeq;
}

// do audio processing at 6300 Hz

void Receiver::Process_Audio(float *vec, int size)
{
    float s,I,Q,Iold,Qold;

    float ph,phold;

    for(int i=0;i<size;i++)
    {
      s = vec[i];

      I = s * sin(phase);
      Q = s * cos(phase);

      phase += (2*M_PI*freq)/samplerate;
      if(phase>2*M_PI) phase -= 2*M_PI;

      QF.FilterFIR(I,Q);
      I = QF.I;
      Q = QF.Q;

      // difference phase detection
      if(I==0.0 && Q==0.0) ph=0;
      else ph = atan2(I, Q);
      phold = DL.Delay(ph);
      dph = ph-phold;

      // normalize from 0..2*PI
      if(dph<0) dph = 2*M_PI+dph;
      else if(dph>2*M_PI) dph = dph-2*M_PI;

      if(modulation==MODE_QPSK)
      {
        DecodeQPSK(dph,I,Q);
        CodeBuf.Delay(I);
        CodeBuf.Delay(Q);
        PhaseBuf.Delay(err_phase(dph));
      }
      else if(modulation==MODE_BPSK)
      {
        DecodeBPSK(dph,I);
        CodeBuf.Delay(I);
        PhaseBuf.Delay(err_phase(dph));
      }
      else if(modulation==MODE_MSK)
      {
        DecodeMSK(dph,I);
        CodeBuf.Delay(I);
        PhaseBuf.Delay(err_phase(dph));
      }

      static int kkk;
      if(++kkk%(pixelsize/oversample)==0)
      {
         if(IntegerMath)
         {
//#ifdef INTEGER_MATH
            //for(int t=0;t<pnsize;t++) _rxseq[(pnsize-1)-t] = (int)(100000*CodeBuf.buff[t*pixelsize]);
            //for(int t=0;t<pnsize;t++) _rxseq[t] = (int)(100000*CodeBuf.buff[((t*pixelsize)+CodeBuf.last)%(pnsize*pixelsize)]);
            for(int t=0;t<pnsize;t++) _rxseq[t] = (int)(100000*CodeBuf.buff[((t*pixelsize)+CodeBuf.last)%(pnsize*pixelsize)]);
//#else
         } else {
            //for(int t=0;t<pnsize;t++) Rxseq.chip[(pnsize-1)-t] = CodeBuf.buff[t*pixelsize];
            for(int t=0;t<pnsize;t++) Rxseq.chip[t] = CodeBuf.buff[((t*pixelsize)+CodeBuf.last)%(pnsize*pixelsize)];
//#endif
         }
         //for(int t=0;t<pnsize;t++) Phaseseq.buff[(pnsize-1)-t] = PhaseBuf.buff[t*pixelsize];
         for(int t=0;t<pnsize;t++) Phaseseq.buff[t] = PhaseBuf.buff[((t*pixelsize)+PhaseBuf.last)%(pnsize*pixelsize)];
         Process_Rxseq();
      }
    }
}

void Receiver::Process_Audio_Clocked(float *vec, int size)
{
    float s,I,Q,Iold,Qold;

    float ph,ampl;
    static float phold=0;

    for(int i=0;i<size;i++)
    {
      s = vec[i];

      I = s * sin(phase);
      Q = s * cos(phase);

      phase += (2*M_PI*freq)/samplerate;
      if(phase>2*M_PI) phase -= 2*M_PI;

      QF.FilterFIR(I,Q);
      I = QF.I;
      Q = QF.Q;

      ampl = I*I+Q*Q;

      if(BitClock.SymbolSynchAVF(ampl))
      {
        // difference phase detection
        if(I==0.0 && Q==0.0) ph=0;
        else ph = atan2(I, Q);
        dph = ph-phold;
        phold = ph;

        // normalize from 0..2*PI
        if(dph<0) dph = 2*M_PI+dph;
        else if(dph>2*M_PI) dph = dph-2*M_PI;

        dph = AVFDelay.Delay(dph);

        if(modulation==MODE_QPSK)
        {
          DecodeQPSK(dph,I,Q);
          CodeBuf.Delay(I);
          CodeBuf.Delay(Q);
          PhaseBuf.Delay(err_phase(dph));
        }
        else if(modulation==MODE_BPSK)
        {
          DecodeBPSK(dph,I);
          CodeBuf.Delay(I);
          PhaseBuf.Delay(err_phase(dph));
        }
        else if(modulation==MODE_MSK)
        {
          DecodeMSK(dph,I);
          CodeBuf.Delay(I);
          PhaseBuf.Delay(err_phase(dph));
        }

        ShowBitShape();

//#ifdef INTEGER_MATH
        if(IntegerMath)
        {
            //for(int t=0;t<pnsize;t++) _rxseq[(pnsize-1)-t] = (int)(100000*CodeBuf.buff[t*pixelsize]);
            for(int t=0;t<pnsize;t++) _rxseq[t] = (int)(100000*CodeBuf.buff[((t)+CodeBuf.last)%(pnsize)]);
//#else
        } else {
            //for(int t=0;t<pnsize;t++) Rxseq.chip[(pnsize-1)-t] = CodeBuf.buff[t*pixelsize];
            for(int t=0;t<pnsize;t++) Rxseq.chip[t] = CodeBuf.buff[((t)+CodeBuf.last)%(pnsize)];
//#endif
        }
        //for(int t=0;t<pnsize;t++) Phaseseq.buff[(pnsize-1)-t] = PhaseBuf.buff[t*pixelsize];
        for(int t=0;t<pnsize;t++) Phaseseq.buff[t] = PhaseBuf.buff[((t)+PhaseBuf.last)%(pnsize)];
        Process_Rxseq();
      }
    }
}

void Receiver::RunCorrelator(float &maxcorrel, int &maxidx, bool &polarity)
{
    maxcorrel = Rxseq.Correlate(PnSeq[0]);
    maxidx    = 0;
    polarity  = false;

    float mincorrel = maxcorrel;
    int minidx = 0;
    int nseq = (1<<(nbits-1));
    for(int z=1;z<nseq;z++)
    {
        float j = Rxseq.Correlate(PnSeq[z]);
        if(j>maxcorrel) { maxcorrel = j; maxidx = z; }
        if(j<mincorrel) { mincorrel = j; minidx = z; }
    }

    mincorrel=-mincorrel;
    if(mincorrel>maxcorrel)
    {
       polarity=true;
       maxcorrel = mincorrel;
       maxidx = minidx;
    }
}

void Receiver::Process_Rxseq()
{
    float maxcorrel;
    int   maxidx;
    bool  polarity;

//#ifdef INTEGER_MATH
    if(IntegerMath)
    {
       int _maxcorrel;
       if(pnsize==64) RunCorrelator64(_maxcorrel,maxidx,polarity);
       else if(pnsize==16) RunCorrelator16(_maxcorrel,maxidx,polarity);
       else if(pnsize==32) RunCorrelator32(_maxcorrel,maxidx,polarity);
       else if(pnsize==128) RunCorrelator128(_maxcorrel,maxidx,polarity);
       maxcorrel = (float)_maxcorrel / 100000.0;
    }
//#else
    else
    {
       RunCorrelator(maxcorrel,maxidx,polarity);
    }
//#endif

    _maxidx[Clock.current_step]   = maxidx;
    _polarity[Clock.current_step] = polarity;

    _dph[Clock.current_step] = Phaseseq.Average()*2;

    if(Clock.SymbolSynch_simple(maxcorrel))
    {
       maxidx   = _maxidx[Clock.last_peak_pos];
       polarity = _polarity[Clock.last_peak_pos];

       ShowCorrelationWaterfall();
       DoAFC_PSK(_dph[Clock.last_peak_pos]);
       FormMain->PhaseScope1->Ampl = 1;
       FormMain->PhaseScope1->Phase = _dph[Clock.last_peak_pos];
       confidence = 100*(Clock.amp_buf[Clock.last_peak_pos])/pnsize;
       FormMain->NeedleMetric->Progress = confidence;

       // symbol decode
       AnsiString Dummy = AlphabetToString(nbits,maxidx,polarity);
       for(int y=0;y<Dummy.Length();y++)
       {
          output_bits[output_nbits++] = Dummy[y+1];
       }

       /* with FEC
       int fec_conf = Clock.amp_buf[Clock.last_peak_pos]*4;
       if(fec_conf>255) fec_conf = 255;
       Fec.DecodeString(Dummy,fec_conf);
       if(Fec.Decoder.output_nbits)
       {
          FormMain->NeedleFecMetric->Progress = Fec.Decoder.metric / (5 * 9);   // (Pathsize+1)*K
       }
       for(int y=0;y<Fec.Decoder.output_nbits;y++)
       {
          output_bits[output_nbits++] = Fec.Decoder.output_bits[y];
       }
       Fec.Decoder.output_nbits=0;
       */
    }
}

void inline Receiver::DecodeBPSK(float dph, float &I)
{
   I = cos(dph);
}

void inline Receiver::DecodeMSK(float dph, float &I)
{
   I = cos(dph);
}

void inline Receiver::DecodeQPSK(float dph, float &I, float &Q)
{
        if(dph < M_PI/2)   { I = cos(dph*2);          Q = +1.0; }
   else if(dph < M_PI)     { I = -1.0;                Q = +cos((dph-M_PI/2)*2); }
   else if(dph < 3*M_PI/2) { I = -cos((dph-M_PI)*2);  Q = -1.0; }
   else                    { I = +1.0;                Q = -cos((dph-3*M_PI/2)*2); }
}

//***********************************************************************************
//***********************************************************************************
//***********************************************************************************
//***********************************************************************************
//***********************************************************************************
//***********************************************************************************

float Receiver::err_phase(float dph)
{
   float err;
   if(modulation==MODE_BPSK)
   {
       if(dph < M_PI/2)        err = dph;
       else if(dph < M_PI)     err = -(M_PI-dph);
       else if(dph < 3*M_PI/2) err = dph-M_PI;
       else                    err = -((2*M_PI)-dph);
   }
   else if(modulation==MODE_MSK)
   {
       if(dph < M_PI/2)        err = M_PI/2 - dph;
       else if(dph < M_PI)     err = -(dph-M_PI/2);
       else if(dph < 3*M_PI/2) err = dph-3*M_PI/2;
       else                    err = -(3*M_PI/2-dph);
   }
   else
   {
            if(dph < 1*M_PI/4)  err = -(dph);
       else if(dph < 2*M_PI/4)  err = +(2*M_PI/4 - dph);
       else if(dph < 3*M_PI/4)  err = -(dph -2*M_PI/4);
       else if(dph < 4*M_PI/4)  err = +(4*M_PI/4 - dph);
       else if(dph < 5*M_PI/4)  err = -(dph -4*M_PI/4);
       else if(dph < 6*M_PI/4)  err = +(6*M_PI/4 - dph);
       else if(dph < 7*M_PI/4)  err = -(dph -6*M_PI/4);
       else                     err = +(8*M_PI/4 - dph);
   }
   return err;
}

void Receiver::DoAFC_PSK(float dph)
{
   if(!AFC) return;

   if(dph < 0) freq += afc_attack;
   else        freq -= afc_attack;
}


/*
void Receiver::ShowCorrelation()
{
   ShowCorrelationWaterfall();

   float max = pnsize;
   float min = 0;

   if(max-min==0) return;

   float mx = FormMain->ImageBitShape->Width;
   float my = FormMain->ImageBitShape->Height;

   TRect NewRect = Rect(0, 0, mx, my);
   FormMain->ImageBitShape->Canvas->Brush->Color = clBlack;
   FormMain->ImageBitShape->Canvas->FillRect(NewRect);

   FormMain->ImageBitShape->Canvas->Pen->Color = clLime;
   FormMain->ImageBitShape->Canvas->MoveTo(-10,my/2);
   for(int i=0;i<Clock.n_steps;i++)
   {
      float amp = Clock.amp_buf[i];
      float pos = (amp - min) / (max-min);
      FormMain->ImageBitShape->Canvas->LineTo((i*mx)/(Clock.n_steps-1),my-(pos*my));
   }

   FormMain->ImageBitShape->Canvas->Pen->Color = (TColor) 0x00FAF0B0;
   FormMain->ImageBitShape->Canvas->MoveTo((Clock.last_peak_pos*mx)/(Clock.n_steps-1),0);
   FormMain->ImageBitShape->Canvas->LineTo((Clock.last_peak_pos*mx)/(Clock.n_steps-1),my);

   FormMain->ImageBitShape->ControlStyle = FormMain->ImageBitShape->ControlStyle << csOpaque;
   FormMain->ImageBitShape->Invalidate();
}
*/

void Receiver::ShowCorrelationWaterfall()
{
   int mx = FormMain->ImageCorrelation->Width;
   int my = FormMain->ImageCorrelation->Height;

   TColor col;
   HDC HandleCanvas = FormMain->ImageCorrelation->Canvas->Handle;
   FormMain->ImageCorrelation->Canvas->Lock();
   BitBlt(HandleCanvas,0,0,mx,my,HandleCanvas,0,-1,SRCCOPY);

   int hx=0;

   int idx_factor = 256 / pnsize ;

   for(int t=0;t<mx;t++)
   {
       int c = (t * Clock.n_steps) / mx;

       int c1 = ((t-1) * Clock.n_steps) / mx;
       int c2 = ((t+1) * Clock.n_steps) / mx;
       if(c1<0) c1=0;
       if(c2>Clock.n_steps-1) c2=Clock.n_steps-1;

       int index = idx_factor * ((2*Clock.amp_buf[c]+Clock.amp_buf[c1]+Clock.amp_buf[c2])/4);
       //int index = (int) Clock.amp_buf[c]*4;

       if(index>255) index=255;
       if(index<0) index = 0;
       //col = (TColor) (index) * 0x010101;
       col = WPal.Colore[255-index];
       SetPixel(HandleCanvas,hx,0,col);
       hx++;
   }

   // show max correlation point
   hx = (mx * Clock.last_peak_pos / Clock.n_steps);
   SetPixel(HandleCanvas,hx,0,clRed);
   SetPixel(HandleCanvas,hx-1,0,clWhite);
   SetPixel(HandleCanvas,hx+1,0,clWhite);

   FormMain->ImageCorrelation->ControlStyle = FormMain->ImageCorrelation->ControlStyle << csOpaque;
   FormMain->ImageCorrelation->Invalidate();
   FormMain->ImageCorrelation->Canvas->Unlock();
}


AnsiString Receiver::AlphabetToString(int nb, int codenr, bool negative)
{
   AnsiString R="";

   for(int t=nb-1;t>=0;t--)
   {
      if(negative)
      {
         if(codenr & (1<<t)) R+="0"; else R+="1";
      }
      else
      {
         if(codenr & (1<<t)) R+="1"; else R+="0";
      }
   }
   return R;
}

void Receiver::ShowBitShape()
{
   // display
   int mx,my,i;
   float amp,pos;
   float min = BitClock.amp_buf[0];
   float max = BitClock.amp_buf[0];
   for(i=0;i<BitClock.n_steps;i++)
   {
      if(BitClock.amp_buf[i] < min) min = BitClock.amp_buf[i];
      if(BitClock.amp_buf[i] > max) max = BitClock.amp_buf[i];
   }

   if(max-min==0) return;

   mx = FormMain->ImageBitShape->Width;
   my = FormMain->ImageBitShape->Height;

   TRect NewRect = Rect(0, 0, mx, my);
   FormMain->ImageBitShape->Canvas->Brush->Color = clBlack;
   FormMain->ImageBitShape->Canvas->FillRect(NewRect);

   FormMain->ImageBitShape->Canvas->Pen->Color = clLime;
   FormMain->ImageBitShape->Canvas->MoveTo(-10,my/2);
   for(i=0;i<BitClock.n_steps;i++)
   {
      amp = BitClock.amp_buf[i];
      pos = (amp - min) / (max-min);
      FormMain->ImageBitShape->Canvas->LineTo((i*mx)/(BitClock.n_steps-1),my-(pos*my));
   }

   FormMain->ImageBitShape->Canvas->Pen->Color = (TColor) 0x00FAF0B0;
   FormMain->ImageBitShape->Canvas->MoveTo((BitClock.last_peak_pos*mx)/(BitClock.n_steps-1),0);
   FormMain->ImageBitShape->Canvas->LineTo((BitClock.last_peak_pos*mx)/(BitClock.n_steps-1),my);

   FormMain->ImageBitShape->ControlStyle = FormMain->ImageBitShape->ControlStyle << csOpaque;
   FormMain->ImageBitShape->Invalidate();
}

