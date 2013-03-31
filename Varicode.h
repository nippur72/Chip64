//---------------------------------------------------------------------------

#ifndef VaricodeH
#define VaricodeH

#define VARICODESIZE 256

class Varicode
{
public:
    int out[2048];
    int outsize;

    AnsiString Table[VARICODESIZE];
    AnsiString Buffer;
    Varicode();
    int Decode(int bit);
    void DecodeString(AnsiString S, int *out, int &size);
    void DecodeBuffer(char *source, int L);
    void DecodeBufferSimple(char *source, int L);
    AnsiString EncodeChar(int ch);
    AnsiString EncodeCharSimple(int ch);
    void MakeTable();
};

//---------------------------------------------------------------------------
#endif
