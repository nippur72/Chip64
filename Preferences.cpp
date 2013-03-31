//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Preferences.h"
#include "Palette.h"
#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "Slider"
#pragma link "Input"
#pragma link "Campo"
#pragma resource "*.dfm"

TFormSetup *FormSetup;

extern AnsiString PaletteName;
extern HellPalette WPal;
extern TColor TXFontColor;
extern TColor TXFontColor1;
extern TColor RXFontColor;
extern TColor RXBGColor;
extern TColor TXBGColor;
extern TColor RXCodesColor;


//---------------------------------------------------------------------------
__fastcall TFormSetup::TFormSetup(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TFormSetup::ButtonBrowseLogClick(TObject *Sender)
{
        AnsiString Source;
        TEdit *dest;
        if(Sender==ButtonBrowseMixer)
        {
           Source = EditMixerProgram->Text;
           dest = EditMixerProgram;
        }

        TOpenDialog *L = new TOpenDialog(0);
        L->InitialDir = ExtractFilePath(Source);
        L->FileName = ExtractFileName(Source);
        if(L->Execute())
        {
           dest->Text = L->FileName;
        }
        delete L;
}

//---------------------------------------------------------------------------


void __fastcall TFormSetup::ButtonChooseColorClick(TObject *Sender)
{
    if(OpenDialogColor->Execute())
    {
        PaletteName = OpenDialogColor->FileName;
        WPal.Load(PaletteName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::Button5Click(TObject *Sender)
{
        ColorDialog1->Color = TXFontColor;
        if(ColorDialog1->Execute())
        {
           TXFontColor = ColorDialog1->Color;
           FormMain->ChangeFont();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::Button4Click(TObject *Sender)
{
    ColorDialog1->Color = RXFontColor;
    if(ColorDialog1->Execute())
    {
       RXFontColor = ColorDialog1->Color;
       FormMain->ChangeFont();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::Button6Click(TObject *Sender)
{
    ColorDialog1->Color = TXFontColor1;
    if(ColorDialog1->Execute())
    {
       TXFontColor1 = ColorDialog1->Color;
       FormMain->ChangeFont();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::Button3Click(TObject *Sender)
{
        ColorDialog1->Color = TXBGColor;
        if(ColorDialog1->Execute())
        {
           TXBGColor = ColorDialog1->Color;
           FormMain->ChangeFont();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::ButtonRXBGClick(TObject *Sender)
{
        ColorDialog1->Color = RXBGColor;
        if(ColorDialog1->Execute())
        {
           RXBGColor = ColorDialog1->Color;
           FormMain->ChangeFont();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::Button7Click(TObject *Sender)
{
    ColorDialog1->Color = RXCodesColor;
    if(ColorDialog1->Execute())
    {
       RXCodesColor = ColorDialog1->Color;
       FormMain->ChangeFont();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSetup::ButtonBrowseWD5GNRClick(TObject *Sender){
        AnsiString Source;
        TEdit *dest;
        if(Sender==ButtonBrowseMixer)
        {
           Source = EditMixerProgram->Text;
           dest = EditMixerProgram;
        }
        else if(Sender==ButtonBrowseWD5GNR)
        {
           Source = EditLogger32Program->Text;
           dest = EditLogger32Program;
        }

        TOpenDialog *L = new TOpenDialog(0);
        L->InitialDir = ExtractFilePath(Source);
        L->FileName = ExtractFileName(Source);
        if(L->Execute())
        {
           dest->Text = L->FileName;
        }
        delete L;
}
//---------------------------------------------------------------------------
