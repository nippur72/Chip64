#include <vcl.h>
#pragma hdrstop

#include "DefineButton.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TFormDefineButton *FormDefineButton;

//---------------------------------------------------------------------------

__fastcall TFormDefineButton::TFormDefineButton(TComponent* Owner) : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormDefineButton::EditButtonTextKeyPress(TObject *Sender, char &Key)
{
   /*
    if(Key==13)
    {
       EditButtonLabel->SetFocus();
       Key = 0;
    }
   */
}
//---------------------------------------------------------------------------

void __fastcall TFormDefineButton::EditButtonLabelKeyPress(TObject *Sender,char &Key)
{
    if(Key==13)
    {
       ButtonOK->SetFocus();
       Key = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDefineButton::FormShow(TObject *Sender)
{
     EditButtonText->SelStart = EditButtonText->Text.Length();
     EditButtonText->SelLength = 1;
     EditButtonText->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormDefineButton::ClearButtonClick(TObject *Sender)
{
        EditButtonLabel->Text="";
        EditButtonText->Text="";
}
//---------------------------------------------------------------------------


