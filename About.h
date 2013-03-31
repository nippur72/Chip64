//---------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TButton *Button1;
        TPanel *Panel3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label5;
        TImage *Image1;
        TMemo *Memo2;
        TLabel *Label3;
        void __fastcall Label3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
