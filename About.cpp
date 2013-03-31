//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TFormAbout *FormAbout;

//---------------------------------------------------------------------------

__fastcall TFormAbout::TFormAbout(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TFormAbout::Label3Click(TObject *Sender)
{
    WinExec("explorer.exe http://xoomer.virgilio.it/aporcino",SW_SHOWMAXIMIZED);        
}
//---------------------------------------------------------------------------

