//---------------------------------------------------------------------------
#ifndef ReceiverH
#define ReceiverH

#include "ComplexFIR.h"
#include "Varicode.h"
#include "FEC.h"
#include "GoodFFT.h"
#include "DelayLine.h"
#include "PLL.h"
#include "Sequences.h"

//@@
#include "ImageScope.h"
#include "Debug.h"
#include "GoodFFT.h"

//#define INTEGER_MATH 1

class Receiver
{
public:
    float samplerate;           // Standard

    ComplexFIR QF;              // quadrature detector low pass filter
    DelayLine  DL;              // delay line for differential phase decoding

    ComplexFIR _QF[4];          // quadrature detector low pass filter
    DelayLine  _DL[4];          // delay line for differential phase decoding
    float _phase[4];            // NCO current phase

    int pixelsize;              // number of samples of 1 chip at 6300 hz
    int oversample;             // oversample factor
    int pnsize;                 // length of pn-codes

    int modulation;

    char output_bits[8192];     // bits decoded
    int output_nbits;           // number of bits decoded
    int metric;                 // measured metric for last decoded bit-stream
    float confidence;           // metric measure in percentage for squelch

    float freq;                 // NCO frequency
    float phase;                // NCO current phase
    float dph;

    int nbits;
    int nwalsh;

    DelayLine CodeBuf;
    Sequence *PnSeq;
    Sequence Rxseq;

    DelayLine PhaseBuf;
    DelayLine Phaseseq;

    AnsiString AlphabetToString(int nbits, int codenr, bool negative);

    bool AFC;                   // AFC is active
    float afc_attack;           // afc attack rate

    //FEC Fec;

    PLL Clock;                  // Symbol Synchronizer (clock)
    PLL BitClock;
    DelayLine AVFDelay;

    bool Clocked;

    Debug deb;

    Receiver();
    ~Receiver();

    void SetPnSeq();
    void Process_Audio(float *vec, int size);
    void Receiver::Process_Audio_Clocked(float *vec, int size);

    void RunCorrelator(float &maxcorrel, int &maxidx, bool &polarity);

    void RunCorrelator16(int &maxcorrel, int &maxidx, bool &polarity);
    void RunCorrelator32(int &maxcorrel, int &maxidx, bool &polarity);
    void RunCorrelator64(int &maxcorrel, int &maxidx, bool &polarity);
    void RunCorrelator64_1(int &maxcorrel, int &maxidx, bool &polarity);
    void RunCorrelator128(int &maxcorrel, int &maxidx, bool &polarity);
    void Process_Rxseq();

    void DecodeQPSK(float dph, float &I, float &Q);
    void DecodeBPSK(float dph, float &I);
    void DecodeMSK(float dph, float &I);

    void DoAFC_PSK(float dph);
    void ShowCorrelation();
    void ShowCorrelationWaterfall();
    void ShowBitShape();

    void SetOversample();

    float err_phase(float dph);

    int   _maxidx[4096];
    bool  _polarity[4096];
    float _dph[4096];

    bool IntegerMath;

//#ifdef INTEGER_MATH
    int _rxseq[4096];
//#endif
};

//---------------------------------------------------------------------------

#endif
