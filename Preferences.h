//---------------------------------------------------------------------------
#ifndef PreferencesH
#define PreferencesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "Slider.h"
#include "Input.h"
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormSetup : public TForm
{
__published:	// IDE-managed Components
    TButton *OK;
        TButton *Button1;
        TPageControl *PageControlSetup;
        TTabSheet *TabSheetComPort;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox9;
        TLabel *Label24;
        TEdit *EditMixerProgram;
        TButton *ButtonBrowseMixer;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox1;
        TCampoMemo *EditCallSign;
        TLabel *Label1;
        TCampoMemo *EditStationName;
        TLabel *Label2;
        TCampoMemo *EditStationQTH;
        TLabel *Label3;
        TCampoMemo *EditStationLocator;
        TLabel *Label5;
        TCampoMemo *EditStationEmail;
        TLabel *Label6;
        TOpenDialog *OpenDialogColor;
        TGroupBox *GroupBox5;
        TColorDialog *ColorDialog1;
        TButton *ButtonRXBG;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TTabSheet *TabSheet4;
        TRadioGroup *RadioGroupWaterfallDisplay;
        TButton *ButtonChooseColor;
        TRadioGroup *RadioGroupWaterfallSpeed;
        TGroupBox *GroupBox7;
        TLabel *Label14;
        TLabel *Label15;
        TCampoMemo *CampoMemoStartFrequency;
        TCampoMemo *CampoMemoEndFrequency;
        TLabel *Label12;
        TCampoMemo *EditCenterQRG;
        TGroupBox *GroupBox6;
        TLabel *Label16;
        TLabel *Label17;
        TComboBox *ComboBoxInSoundCard;
        TComboBox *ComboBoxOutSoundCard;
        TGroupBox *GroupBox2;
        TLabel *Label11;
        TLabel *Label10;
        TCampoMemo *EditAFCAttack;
        TCampoMemo *EditSquelch;
        TLabel *Label4;
        TComboBox *ComboBoxOversample;
        TRadioGroup *RadioGroupPTT;
        TGroupBox *GroupBox12;
        TLabel *Label28;
        TEdit *EditLogger32Program;
        TButton *ButtonBrowseWD5GNR;
        TCheckBox *CheckBoxLogger32Load;
        TCheckBox *CheckBoxLogger32Close;
        TCheckBox *CheckBoxLogger32ClientOnTop;
        void __fastcall ButtonBrowseLogClick(TObject *Sender);
        void __fastcall ButtonChooseColorClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall ButtonRXBGClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall ButtonBrowseWD5GNRClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TFormSetup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSetup *FormSetup;
//---------------------------------------------------------------------------
#endif



