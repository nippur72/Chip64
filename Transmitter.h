//---------------------------------------------------------------------------

#ifndef TransmitterH
#define TransmitterH

#include "Varicode.h"
#include "Sequences.h"
#include "DelayLine.h"

class Transmitter
{
public:
    float SampleRate;
    float samplerate;
    float sampleratetune;
    int pixelsize;

    int modulation;

    int nbits;
    int nwalsh;

    float freq;
    float freqoffset;

    float phase;
    int Inew,Qnew;
    int Iold,Qold;

    int   _Inew[4];
    int   _Iold[4];
    float _phase[4];

    float *Samples;
    int NSamples;

    Varicode VC;
    //FEC Fec;

    Transmitter();
    ~Transmitter();

    void SetPnSeq();

    void PrepareTX();
    void SendChar(int ch);
    void SendPreamble();
    void SendPostamble();

    void ProcessStream();
    void ProcessStreamBPSK();
    void ProcessStreamMSK();
    void ProcessStreamQPSK();

    AnsiString Stream;

    Sequence *PnSeq;
    int pnsize;

    float chips[2048];
    int chipsize;

    void StringToAlphabet(AnsiString Dummy, int nbits, int &index, bool &negative);
};

//---------------------------------------------------------------------------
#endif
