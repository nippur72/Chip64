//---------------------------------------------------------------------------
#ifndef DefineButtonH
#define DefineButtonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDefineButton : public TForm
{
__published:	// IDE-managed Components
        TMemo *EditButtonText;
        TEdit *EditButtonLabel;
        TLabel *Label1;
        TLabel *Label2;
        TButton *ButtonOK;
        TButton *Button2;
        TBevel *Bevel1;
        TButton *ClearButton;
        void __fastcall EditButtonTextKeyPress(TObject *Sender, char &Key);
        void __fastcall EditButtonLabelKeyPress(TObject *Sender,
          char &Key);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ClearButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDefineButton(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDefineButton *FormDefineButton;
//---------------------------------------------------------------------------
#endif

