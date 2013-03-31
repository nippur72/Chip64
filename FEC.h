#ifndef FECH
#define FECH

#include "Viterbi.h"

class FEC
{
public:
    int level;
    Viterbi Encoder;
    ParallelViterbi Decoder;

    AnsiString EncBuffer;

    FEC();
    ~FEC();

    void Reset();
    AnsiString Encode(AnsiString Data);
    void DecodeString(AnsiString Data, int confidence);
};

#endif


