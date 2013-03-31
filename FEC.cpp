#pragma hdrstop

#include "FEC.h"

FEC::FEC()
{
   level = 0;
   Encoder.SetParm(2,9);
   Decoder.SetParm(2,9);
}

FEC::~FEC()
{

}

void FEC::Reset()
{
   Encoder.encstate = 0;
   EncBuffer = "";
}

AnsiString FEC::Encode(AnsiString Data)
{
   if(level==0)
   {
      // no FEC
      return Data;
   }
   else if(level==1)
   {
      // punctured rate R=3/4
      EncBuffer+=Encoder.encode(Data);
      AnsiString R;
      while(EncBuffer.Length()>=12)
      {
         R+=EncBuffer.SubString(1,1) +EncBuffer.SubString(2,1) +
            EncBuffer.SubString(4,1) +EncBuffer.SubString(5,1) +
            EncBuffer.SubString(7,1) +EncBuffer.SubString(8,1) +
            EncBuffer.SubString(10,1)+EncBuffer.SubString(11,1);
         EncBuffer = EncBuffer.SubString(13,EncBuffer.Length()-12);
      }
      return R;
   }
   else if(level==2)
   {
      // native rate R=1/2
      return Encoder.encode(Data);
   }
}

void FEC::DecodeString(AnsiString Data, int confidence)
{
   if(level==0)
   {
      for(int t=0;t<Data.Length();t++)
      {
         Decoder.output_bits[Decoder.output_nbits++] = Data[t+1];
      }
      return;
   }
   else if(level==1)
   {
      confidence/=2;
      for(int t=0;t<Data.Length();t++)
      {
         if(Data[t+1]=='1') Decoder.SymbolDecode(128+confidence);
         else               Decoder.SymbolDecode(128-confidence);
         if(t==1 || t==3 || t==5 || t==7) Decoder.SymbolDecode(128);
      }
   }
   else if(level==2)
   {
      confidence/=2;
      for(int t=0;t<Data.Length();t++)
      {
         if(Data[t+1]=='1') Decoder.SymbolDecode(128+confidence);
         else               Decoder.SymbolDecode(128-confidence);
      }
   }
}

