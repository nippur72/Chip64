//---------------------------------------------------------------------------

#ifndef PaletteH
#define PaletteH

#include <vcl.h>

class HellPalette
{
public:
   TColor Colore[256];
   void Load(AnsiString NomeFile);
   void MakeSeedPalette(float gamma);
   HellPalette();
};

//---------------------------------------------------------------------------
#endif
