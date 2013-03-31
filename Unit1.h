//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <MPlayer.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "Slider.h"
#include <OleCtnrs.hpp>
#include <Db.hpp>
#include "PhaseScope.h"
#include "Input.h"
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include "NEEDLE.h"
#include "ImageScope.h"
//---------------------------------------------------------------------------

#define RATE_R1  0
#define RATE_R2  1
#define RATE_R3  2

#define CODE_K0  0
#define CODE_K5  5
#define CODE_K7  7
#define CODE_K9  9

#define MODE_BPSK 0
#define MODE_QPSK 1
#define MODE_MSK  2

#define CLOCKED_DECODING 1

class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *N1;
    TMenuItem *MenuHelp;
    TMenuItem *About1;
    TMenuItem *N2;
    TMenuItem *Transmit1;
    TMenuItem *Receive1;
    TMenuItem *MenuStopTransmit;
    TMenuItem *MenuStartReceive;
    TStatusBar *StatusBar1;
    TImageList *ImageList1;
    TMenuItem *Separator4;
    TMenuItem *SendFile1;
    TMenuItem *N9;
    TMenuItem *Separator5;
    TMenuItem *MenuClearTXbuffer;
        TMenuItem *MenuMacro1;
        TMenuItem *MenuMacro2;
        TMenuItem *MenuMacro3;
        TMenuItem *MenuMacro4;
        TMenuItem *MenuMacro5;
        TMenuItem *MenuMacro6;
        TMenuItem *MenuMacro7;
        TMenuItem *MenuMacro8;
        TMenuItem *MenuMacro9;
        TMenuItem *MenuMacro10;
        TMenuItem *MenuMacro11;
        TMenuItem *MenuMacro12;
    TMenuItem *IZ8BLYWebsite1;
    TMenuItem *N12;
        TImageList *ImageListMenu;
        TMenuItem *Setotheroperatorscallsign1;
        TMenuItem *N4;
        TMenuItem *Endtransmission1;
        TFontDialog *FontDialogRX;
        TFontDialog *FontDialogTX;
        TMenuItem *N6;
        TMenuItem *Sendaheadbuffer1;
        TMenuItem *MenuLogFile;
        TPanel *Panel4;
        TToolBar *ToolBar1;
        TToolButton *ButtonStartRx;
        TToolButton *ToolButton4;
        TToolButton *ToolButton3;
        TToolButton *ToolButton2;
        TToolButton *ToolButtonPreferences;
        TToolButton *ToolButton1;
        TToolButton *ToolButtonClearScreen;
        TToolButton *ToolButtonLog;
        TToolButton *ToolButton6;
        TMenuItem *View1;
        TPanel *Panel7;
        TPanel *Panel2;
        TSplitter *Splitter1;
        TRichEdit *RichEdit1;
        TMemo *EditHell;
        TPanel *PanelLog;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label6;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TCampoMemo *EditQRZ;
        TCampoMemo *EditName;
        TCampoMemo *EditQTH;
        TCampoMemo *EditFrequency;
        TButton *ButtonLog;
        TButton *ButtonLogNewEntry;
        TCampoMemo *EditRSTSent;
        TCampoMemo *EditRSTReceived;
        TCampoMemo *EditComments;
        TMenuItem *MenuViewWFFT;
        TMenuItem *MenuViewScale;
        TSplitter *SplitterWaterfall;
        TPanel *PanelWFFT;
        TImage *ImageWFFT;
        TImage *ImageScaleWFFT;
        TPanel *Panel1;
        TPanel *PanelButtons;
        TLabel *LabelSend1;
        TLabel *LabelSend2;
        TLabel *LabelSend3;
        TLabel *LabelSend4;
        TLabel *LabelSend5;
        TLabel *LabelSend6;
        TLabel *LabelSend7;
        TLabel *LabelSend8;
        TLabel *LabelSend9;
        TLabel *LabelSend10;
        TLabel *LabelSend11;
        TLabel *LabelSend12;
        TButton *ButtonSend6;
        TButton *ButtonSend8;
        TButton *ButtonSend7;
        TButton *ButtonSend11;
        TButton *ButtonSend9;
        TButton *ButtonSend12;
        TButton *ButtonSend10;
        TButton *ButtonSend3;
        TButton *ButtonSend4;
        TButton *ButtonSend5;
        TButton *ButtonSend2;
        TButton *SpeedButtonCQ;
        TButton *ButtonSend1;
        TPanel *PanelMeters;
        TPanel *PanelPhaseScope;
        TLabel *Label14;
        TPhaseScope *PhaseScope1;
        TPanel *PanelFrequencyCounter;
        TLabel *Label1;
        TEdit *EditFreq;
        TUpDown *UpDownFreq;
        TPanel *PanelMetric;
        TNeedle *NeedleMetric;
        TLabel *Label7;
        TCheckBox *CheckBoxAFC;
        TCheckBox *CheckBoxSquelch;
        TImage *ImageCorrelation;
        TSplitter *SplitterCorreloscope;
        TPanel *PanelPower;
        TLabel *Label11;
        TSlider *SliderPowerControl;
        TLabel *Label5;
        TLabel *Label12;
        TPanel *PanelRXFilter;
        TLabel *Label13;
        TSlider *SliderRXFilter;
        TLabel *Label16;
        TLabel *Label17;
        TMenuItem *MenuMode;
        TMenuItem *MenuChip64;
        TMenuItem *MenuChip128;
        TMenuItem *MenuChip32;
        TMenuItem *MenuChip16;
        TMenuItem *N3;
        TMenuItem *Chip128x41;
        TPanel *Panel3;
        TLabel *Label15;
        TPanel *Panel5;
        TImage *ImageBitShape;
        TMenuItem *MenuUnclocked;
        TMenuItem *MenuClocked;
        TMenuItem *N7;
        TMenuItem *MenuFixHyperthreading;
    void __fastcall MenuHelpClick(TObject *Sender);
    void __fastcall AboutClick(TObject *Sender);
    void __fastcall MenuExitClick(TObject *Sender);
    void __fastcall MenuStartReceiveClick(TObject *Sender);
    void __fastcall MenuStopTransmitClick(TObject *Sender);
    void __fastcall EditHellKeyPress(TObject *Sender, char &Key);
    void __fastcall ToolButton2Click(TObject *Sender);
    void __fastcall ToolButton3Click(TObject *Sender);
    void __fastcall ButtonStartRxClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Preferences1Click(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ButtonSendClick(TObject *Sender);
    void __fastcall SendString(AnsiString s);
    void __fastcall SendFile1Click(TObject *Sender);
    void __fastcall Definebutton1Click(int tag);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall MenuClearTXbufferClick(TObject *Sender);
    void __fastcall IZ8BLYWebsite1Click(TObject *Sender);
    void __fastcall ChangeFont();
    void __fastcall DisplayWaterfall(float *vec, int size);
    void __fastcall ShowWaterfallWFFT();
    void __fastcall ShowMetric();
        void __fastcall ButtonOtherCallClick(TObject *Sender);
        void __fastcall ButtonSend1MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall EditHellChange(TObject *Sender);
        void __fastcall Endtransmission1Click(TObject *Sender);
        void __fastcall Speed1Click(TObject *Sender);
        void __fastcall ChooseRXfont1Click(TObject *Sender);
        void __fastcall OpenTXfont1Click(TObject *Sender);
        void __fastcall SpeedButtonCQClick(TObject *Sender);
        void __fastcall Sendaheadbuffer1Click(TObject *Sender);
        void __fastcall MenuLogFileClick(TObject *Sender);
        void __fastcall RichEdit1KeyPress(TObject *Sender, char &Key);
        void __fastcall EditHellKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
        void __fastcall EditFreqChange(TObject *Sender);
        void __fastcall ToolButtonClearScreenClick(TObject *Sender);
        void __fastcall RichEdit1MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ToolButtonLogClick(TObject *Sender);
        void __fastcall MenuMacro1Click(TObject *Sender);
        void __fastcall ImageHzMouseMove(TObject *Sender,TShiftState Shift, int X, int Y);
        void __fastcall ImageBitShapeDblClick(TObject *Sender);
        void __fastcall CheckBoxAFCClick(TObject *Sender);
        void __fastcall ButtonLogNewEntryClick(TObject *Sender);
        void __fastcall ButtonLogClick(TObject *Sender);
        void __fastcall EditQRZChange(TObject *Sender);
        void __fastcall EditNameChange(TObject *Sender);
        void __fastcall EditQTHChange(TObject *Sender);
        void __fastcall EditRSTSentChange(TObject *Sender);
        void __fastcall EditRSTReceivedChange(TObject *Sender);
        void __fastcall EditQRZDblClick(TObject *Sender);
        void __fastcall EditNameDblClick(TObject *Sender);
        void __fastcall EditQTHDblClick(TObject *Sender);
        void __fastcall CheckBoxSquelchClick(TObject *Sender);
        void __fastcall ImageWFFTMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MenuViewWFFTClick(TObject *Sender);
        void __fastcall MenuViewScaleClick(TObject *Sender);
        void __fastcall SplitterWaterfallMoved(TObject *Sender);
        void __fastcall Splitter3Moved(TObject *Sender);
        void __fastcall SpeedButtonCQMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Splitter1Moved(TObject *Sender);
        void __fastcall SplitterCorreloscopeMoved(TObject *Sender);
        void __fastcall SliderRXFilterChange(TObject *Sender);
        void __fastcall MenuChip64Click(TObject *Sender);
        void __fastcall MenuChip128Click(TObject *Sender);
        void __fastcall MenuChip32Click(TObject *Sender);
        void __fastcall MenuChip16Click(TObject *Sender);
        void __fastcall MenuUnclockedClick(TObject *Sender);
        void __fastcall MenuClockedClick(TObject *Sender);
        void __fastcall ImageCorrelationMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MenuFixHyperthreadingClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    __fastcall ~TFormMain();
    void __fastcall EncodeAudio(signed short *buffer, int size);
    void __fastcall DecodeAudio(signed short *buffer, int size);
    void __fastcall DecodeAudioDownsampled(int size);
    void __fastcall UpdateMenu();
    void __fastcall SnapshotSave(int nscroll);
    void __fastcall SnapshotDoSave(AnsiString &NomeFile);
    void __fastcall LoadConfig();
    void __fastcall SaveConfig();
    void __fastcall UpdateButtons();
    unsigned char __fastcall TransmitChar();
    void __fastcall ChangeCMTSpeed(bool render);
    void __fastcall ChangedWaterfall();
    void __fastcall StuffBuff(char Key);
    void __fastcall RXPrintChar(TRichEdit *RE,int code, TColor col);
    void __fastcall RXPrintSpecialChar(TRichEdit *RE,int code);
    void __fastcall RXPrintString(TRichEdit *RE,AnsiString S, TColor col);
    AnsiString __fastcall ParseMetaCommand(AnsiString Command);
    AnsiString __fastcall SScale(double SNR, double &db);
    void __fastcall LogToFile(AnsiString S);
    void __fastcall Tune();
    void __fastcall SystemMessage(AnsiString S);
    void __fastcall UpdateEditFreq();
    AnsiString __fastcall GetSystemInSoundCards();
    AnsiString __fastcall GetSystemOutSoundCards();
    void __fastcall DrawWaterfallScale();
    void __fastcall SetWaterfallPosition();
    void __fastcall StartTransmit();
    void __fastcall StopTransmit();
};

AnsiString FloatToAnsiString(float f);
AnsiString GetRegistryValue(HKEY Cat,AnsiString KeyName,AnsiString KeyValue);
unsigned int Hash(AnsiString s);
void FileWriteString(int H,AnsiString s);
AnsiString FormatAdif(AnsiString FieldName, AnsiString Value);

//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
