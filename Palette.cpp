//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma hdrstop

#include "Palette.h"

HellPalette::HellPalette()
{
    MakeSeedPalette(1);
}

void HellPalette::MakeSeedPalette(float gamma)
{
    int rr,gg,bb;

    for(int t=0;t<256;t++)
    {
       rr = 255-(255*pow((float)t/256,1/gamma));
       gg = rr;
       bb = rr;
       Colore[t] = (TColor) (rr + gg*256 + bb*65536);
    }
}

void HellPalette::Load(AnsiString NomeFile)
{
   if(FileExists(NomeFile))
   {
      if(ExtractFileExt(NomeFile)==".pal")
      {
        TStringList *TextFile = new TStringList;
        TextFile->LoadFromFile(NomeFile);
        for(int t=0;t<256;t++)
        {
           int red,green,blue;
           sscanf(TextFile->Strings[t].c_str(),"%d %d %d",&red,&green,&blue);
           Colore[t] = (TColor) (blue*0x010000 + green*0x000100 + red*0x000001);
        }
        delete TextFile;
      }
      else if(ExtractFileExt(NomeFile)==".act")
      {
         int fh = FileOpen(NomeFile,fmOpenRead);
         unsigned char *buf = new unsigned char[768];
         FileRead(fh,buf,768);
         FileClose(fh);
         for(int t=0;t<256;t++)
         {
           int red,green,blue;
           red   = buf[t*3+0];
           green = buf[t*3+1];
           blue  = buf[t*3+2];
           Colore[255-t] = (TColor) (blue*0x010000 + green*0x000100 + red*0x000001);
        }
        delete [] buf;
      }
   }
   else
   {
      MakeSeedPalette(1);
   }
}


