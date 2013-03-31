//---------------------------------------------------------------------------
#ifndef LogH
#define LogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "Campo.h"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "Input.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormLog : public TForm
{
__published:	// IDE-managed Components
        TCampoMemo *EditQRZ;
        TLabel *Label1;
        TCampoMemo *EditName;
        TLabel *Label2;
        TCampoMemo *EditQTH;
        TLabel *Label3;
        TCampoMemo *EditFrequency;
        TLabel *Label6;
        TButton *ButtonLog;
        TButton *Button2;
        TLabel *Label8;
        TLabel *Label9;
        TCampoMemo *EditRSTSent;
        TCampoMemo *EditRSTReceived;
        TLabel *Label10;
        TCampoMemo *EditComments;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ButtonLogClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EditQRZChange(TObject *Sender);
        void __fastcall EditNameChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall EditQTHChange(TObject *Sender);
        void __fastcall EditRSTSentChange(TObject *Sender);
        void __fastcall EditRSTReceivedChange(TObject *Sender);
        void __fastcall EditQRZDblClick(TObject *Sender);
        void __fastcall EditNameDblClick(TObject *Sender);
        void __fastcall EditQTHDblClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TFormLog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLog *FormLog;
//---------------------------------------------------------------------------
#endif
