#include <stdio.h>
#include <vcl.h>
#include <clipbrd.hpp>

#pragma hdrstop

#include "About.h"
#include "Preferences.h"
#include "DefineButton.h"
#include "Log.h"
#include "Logger32.h"
#include "PTT.h"
#include "Options.h"
#include "Receiver.h"
#include "Transmitter.h"
#include "Viterbi.h"
#include "Palette.h"
#include "Unit1.h"
#include "SoundCard.h"
#include "GoodFFT.h"
#include "Debug.h"
#include "Sequences.h"

#pragma link "Slider"
#pragma link "PhaseScope"
#pragma link "Input"
#pragma link "NEEDLE"
#pragma link "ImageScope"

#pragma package(smart_init)
#pragma resource "*.dfm"

//***************************************************************** user data

extern SoundCard SC;

TFormMain *FormMain;        // Main tx/rx form

/**** config ****/
Options Config;             // the configuration
int  PTTPort;               // PPT port number (0=none)

AnsiString CallSign;        // Ham callsign
AnsiString StationName;     //
AnsiString StationQTH;      //
AnsiString StationLocator;  //
AnsiString StationEmail;    //

HellPalette WPal;
AnsiString PaletteName;

float CenterQRG;

AnsiString CQString;

int ClockDelay;

int RXFontSize; AnsiString RXFontName; bool RXFontBold; TColor RXFontColor;
int TXFontSize; AnsiString TXFontName; bool TXFontBold; TColor TXFontColor;

TColor TXFontColor1;
TColor RXCodesColor;
TColor RXBGColor;
TColor TXBGColor;

PTTClass PTT;              // PTT via com port

AnsiString ThePath;        // the path of the program

// user definable buttons
AnsiString Button1Text,Button1Label;
AnsiString Button2Text,Button2Label;
AnsiString Button3Text,Button3Label;
AnsiString Button4Text,Button4Label;
AnsiString Button5Text,Button5Label;
AnsiString Button6Text,Button6Label;
AnsiString Button7Text,Button7Label;
AnsiString Button8Text,Button8Label;
AnsiString Button9Text,Button9Label;
AnsiString Button10Text,Button10Label;
AnsiString Button11Text,Button11Label;
AnsiString Button12Text,Button12Label;

Logger32 Log32;

// tools
AnsiString SendFileFolder;
AnsiString MixerProgram;

// window position and state
int WindowTop;
int WindowLeft;
int WindowWidth;
int WindowHeight;
bool WindowMaximized;

AnsiString OtherCall,OtherName,OtherRST,RST,OtherQTH;
bool LogState;

AnsiString SendBuffer;

int LastPos=0;

bool LogFile;
int LogHandle=0;
AnsiString LogName;

int Rate;
int BaudRate;
int Modulation;
int KMode;

Receiver    RX;
Transmitter TX;

float *fb;

float cpu_load;

int WaterfallSize;
int TransmitBoxSize;
int CorreloscopeSize;

bool HorizontalWaterfall;
bool FrequencyScale;

GoodFFT WFFT;            // Waterfall FFT display settings

int HWaterfallStart;     // Waterfall FFT Display start range
int HWaterfallBand;      // Waterfall FFT Display end range
int WaterfallSpeed;      // Refresh rate of waterfall
bool WaterfallLogScale;  // true if waterfall has log scale, false = linear scale
bool Overdrive;          // true if there is audio overdrive at input - used to make red the waterfall

Varicode VC;             // Varicode decoder

bool Squelch;
int squelch_thereshold;   // squelch thereshold level
float confidence;         // confidence of decoded bits
float last_confidence;    // confidence measured last time for seeing if dropped down

enum RadioStates { paused, rx, tx } RadioState;
bool FlushInvoked;
int FlushCount;

Debug deb;

Debug CPULoad;

#define downsample_to 7

//************************************************************** end user data

void DecodeAudioRoutine(signed short *buffer, int size)
{
    FormMain->DecodeAudio(buffer,size);
}

void EncodeAudioRoutine(signed short *buffer, int size)
{
    FormMain->EncodeAudio(buffer,size);
}

const crCursorWaterfall = 5;

__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
       // collega Soundcard a Form
       SC.DecodeAudio = DecodeAudioRoutine;
       SC.EncodeAudio = EncodeAudioRoutine;

       SC.DumpToFile = false;

       RadioState = paused;

       fb = new float[65536*32];

       Application->Icon=Icon;  // bug fix

       HCURSOR i = LoadCursor(HInstance,"CursorWaterfall");
       Screen->Cursors[crCursorWaterfall] = i;

       ThePath = ExtractFilePath(Application->ExeName);

       LogName = ThePath + "\\chip64log.txt";

       // set MODE A by default
       // @@@@ MenuModeMFSK16Click(this);

       // setup the configuration
       Config.ConfigName = ThePath + "\\iz8bly.ini";

       // general options
       Config.Add("CallSign"            ,OPT_STRING, "NOCALL", &CallSign);
       Config.Add("Name"                ,OPT_STRING, "", &StationName);
       Config.Add("QTH"                 ,OPT_STRING, "", &StationQTH);
       Config.Add("Locator"             ,OPT_STRING, "", &StationLocator);
       Config.Add("Email"               ,OPT_STRING, "", &StationEmail);

       Config.Add("CQString"        ,OPT_STRING, "CQ CQ CQ de $QRZ $QRZ $QRZ\r\nCQ CQ CQ de $QRZ $QRZ $QRZ\r\nCQ CQ CQ de $QRZ $QRZ $QRZ\r\npse K $off ", &CQString);
       Config.Add("Button1Label"    ,OPT_STRING, "RRR",        &Button1Label );  Config.Add("Button1Text" ,OPT_STRING, "RRR $OTHER de $QRZ\r\n ", &Button1Text );
       Config.Add("Button2Label"    ,OPT_STRING, "Hello",      &Button4Label );  Config.Add("Button4Text" ,OPT_STRING, "Hello dr $OTHERNAME in $OTHERQTH many thanks for replying my call, ", &Button4Text );
       Config.Add("Button3Label"    ,OPT_STRING, "My name",    &Button2Label );  Config.Add("Button2Text" ,OPT_STRING, "My name is $NAME qth $QTH ", &Button2Text );
       Config.Add("Button4Label"    ,OPT_STRING, "Give RST",   &Button7Label );  Config.Add("Button7Text" ,OPT_STRING, "Many tnx for $OTHERRST your RST is $RST $RST = ", &Button7Text );
       Config.Add("Button5Label"    ,OPT_STRING, "ID",         &Button5Label );  Config.Add("Button5Text" ,OPT_STRING, "$STATION ", &Button5Text );
       Config.Add("Button6Label"    ,OPT_STRING, "Station",    &Button9Label );  Config.Add("Button9Text" ,OPT_STRING, "\r\n*** Station de $QRZ ***\r\nRTX:\t\r\nANT:\t\r\nPWR:\t\r\nPC:\t\r\n***\r\n", &Button9Text );
       Config.Add("Button7Label"    ,OPT_STRING, "Break-In",   &Button3Label );  Config.Add("Button3Text" ,OPT_STRING, "de $QRZ $QRZ bk bk $off ", &Button3Text );
       Config.Add("Button8Label"    ,OPT_STRING, "QRZ?",       &Button6Label );  Config.Add("Button6Text" ,OPT_STRING, "QRZ QRZ de $QRZ pse K $off", &Button6Text );
       Config.Add("Button9Label"    ,OPT_STRING, "KN",         &Button8Label );  Config.Add("Button8Text" ,OPT_STRING, "$OTHER de $QRZ pse kn $off ", &Button8Text );
       Config.Add("Button10Label"   ,OPT_STRING, "TIME",       &Button10Label ); Config.Add("Button10Text",OPT_STRING, "$DATE $UTC ($TIME local) ", &Button10Text );
       Config.Add("Button11Label"   ,OPT_STRING, "73 SK",      &Button11Label ); Config.Add("Button11Text",OPT_STRING, "My best 73 dr $OTHERNAME hpe cuagn.\r\n$OTHER de $QRZ 73 SK SK $OFF ", &Button11Text );
       Config.Add("Button12Label"   ,OPT_STRING, "BTU",        &Button12Label ); Config.Add("Button12Text",OPT_STRING, " $OTHER de $QRZ pse kn $off ", &Button12Text );

       Config.Add("PaletteName"         ,OPT_STRING, "", &PaletteName);
       Config.Add("CenterQRG"           ,OPT_FLOAT,  "1500", &CenterQRG);

       Config.Add("HWaterfallBand"      ,OPT_INT,    "3100", &HWaterfallBand);
       Config.Add("HWaterfallStart"     ,OPT_INT,    "100",  &HWaterfallStart);

       Config.Add("WaterfallSize"       ,OPT_INT,   "175",  &WaterfallSize);
       Config.Add("TransmitBoxSize"     ,OPT_INT,   "48",   &TransmitBoxSize);
       Config.Add("CorreloscopeSize"    ,OPT_INT,   "73",   &CorreloscopeSize);

       Config.Add("HorizontalWaterfall" ,OPT_BOOL,   "on",  &HorizontalWaterfall);
       Config.Add("FrequencyScale"      ,OPT_BOOL,   "on",  &FrequencyScale);

       Config.Add("AFCAttack"           ,OPT_FLOAT, "0.1",  &RX.afc_attack);
       Config.Add("AFC"                 ,OPT_BOOL,  "on",   &RX.AFC);
       Config.Add("Squelch"             ,OPT_BOOL,  "on",   &Squelch);
       Config.Add("SquelchThereshold"   ,OPT_INT,   "5",    &squelch_thereshold);

       Config.Add("Oversample"          ,OPT_INT,    "3", &RX.oversample);

       Config.Add("SendFileFolder"      ,OPT_STRING, "c:\\windows\\desktop", &SendFileFolder);
       Config.Add("MixerProgram"        ,OPT_STRING, "SNDVOL32", &MixerProgram);
       Config.Add("Logtofile"           ,OPT_BOOL,   "on",       &LogFile);
       Config.Add("Freq"                ,OPT_FLOAT,  "1000",     &RX.freq );

       Config.Add("WaterfallLog"        ,OPT_BOOL,   "on",     &WaterfallLogScale );
       Config.Add("WaterfallSpeed"      ,OPT_INT,    "1",      &WaterfallSpeed );

       Config.Add("LogState"            ,OPT_BOOL,   "off",      &LogState);

       Config.Add("IntegerMath"         ,OPT_BOOL,   "on",       &RX.IntegerMath);

       Config.Add("PTTPort"            ,OPT_INT,   "0",   &PTTPort);
       Config.Add("Logger32Program"    ,OPT_STRING,"",    &Log32.Logger32Program);
       Config.Add("Logger32Load"       ,OPT_BOOL,  "off", &Log32.Logger32Load);
       Config.Add("Logger32Close"      ,OPT_BOOL,  "off", &Log32.Logger32Close);
       Config.Add("Logger32ClientOnTop",OPT_BOOL,  "off", &Log32.Logger32ClientOnTop);

       Config.Add("InSoundCard"        ,OPT_INT,   "0",   &SC.InSoundCard);
       Config.Add("OutSoundCard"       ,OPT_INT,   "0",   &SC.OutSoundCard);

       // window position
       Config.Add("WindowTop"          ,OPT_INT,    "0",    &WindowTop);
       Config.Add("WindowLeft"         ,OPT_INT,    "0",    &WindowLeft);
       Config.Add("WindowWidth"        ,OPT_INT,    "0",    &WindowWidth);
       Config.Add("WindowHeight"       ,OPT_INT,    "0",    &WindowHeight);
       Config.Add("WindowMaximized"    ,OPT_BOOL,   "on",   &WindowMaximized);

       // font
       Config.Add("RXFontName" ,OPT_STRING, "Arial", &RXFontName );
       Config.Add("RXFontSize" ,OPT_INT,    "10",    &RXFontSize );
       Config.Add("RXFontBold" ,OPT_BOOL,   "off",   &RXFontBold );
       Config.Add("RXFontColor",OPT_INT,    "-1",    &RXFontColor);
       Config.Add("TXFontName" ,OPT_STRING, "Arial", &TXFontName );
       Config.Add("TXFontSize" ,OPT_INT,    "10",    &TXFontSize );
       Config.Add("TXFontBold" ,OPT_BOOL,   "off",   &TXFontBold );
       Config.Add("TXFontColor",OPT_INT,    "-1",    &TXFontColor);
       Config.Add("TXFontColor1",OPT_INT,   "255",   &TXFontColor1);

       Config.Add("RXBGColor"    ,OPT_INT,   "16777215",   &RXBGColor);
       Config.Add("TXBGColor"    ,OPT_INT,   "13498364",   &TXBGColor);
       Config.Add("RXCodesColor" ,OPT_INT,   "16711680",   &RXCodesColor);

       Config.Load();

       Log32.SetMainWindowHandle((int)Handle);

       if(!WindowMaximized)
       {
         if(WindowTop   ==0) WindowTop    = Top;
         if(WindowLeft  ==0) WindowLeft   = Left;
         if(WindowWidth ==0) WindowWidth  = Width;
         if(WindowHeight==0) WindowHeight = Height;
       }

       if(WindowMaximized)
       {
          WindowState = wsMaximized;
       }
       else
       {
         Top = WindowTop;
         Left = WindowLeft;
         Width = WindowWidth;
         Height = WindowHeight;
       }

       if(Log32.Logger32ClientOnTop)
       {
          if(FormStyle!=fsStayOnTop) FormStyle = fsStayOnTop;
       }
       else
       {
          if(FormStyle!=fsNormal) FormStyle = fsNormal;
       }

       ChangeFont();

       if(PaletteName!="") WPal.Load(PaletteName);

       if(!LogState) PanelLog->Visible=false;

       EditFreq->Text = RX.freq;

       CheckBoxAFC->Checked = RX.AFC;
       CheckBoxSquelch->Checked = Squelch;
       MenuChip64Click(this);
       RX.SetOversample();

       WFFT.SetSize(1<<(9+WaterfallSpeed));
       WFFT.SetWindow(WINDOW_RC);
       //WFFT.SetWindowFilter(0,0.5,4000,WINDOW_HANNING);

       if(!HorizontalWaterfall) MenuViewWFFTClick(this);
       if(!FrequencyScale) MenuViewScaleClick(this);

       PTT.SetPort(PTTPort);
       PTT.Open();

       UpdateMenu();
       UpdateButtons();

       EditHell->SetFocus();

       // start receive
       ButtonStartRxClick(this);
}

__fastcall TFormMain::~TFormMain()
{
       delete [] fb;

       WindowMaximized = (WindowState == wsMaximized);
       if(!WindowMaximized)
       {
         WindowTop    = Top;
         WindowLeft   = Left;
         WindowWidth  = Width;
         WindowHeight = Height;
       }
       Config.Save();
       PTT.Close();
       if(LogHandle>0) FileClose(LogHandle);
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::DecodeAudio(signed short *buffer, int size)
{
    if(RadioState != rx) return;

    CPULoad.Start();

    /*
    // converts to float and normalize
    for(int i=0;i<size;i++)
    {
       fb[i]=((float) buffer[i])/32767.0;
    }
    DecodeAudioDownsampled(size);
    */

    static int downsampler_counter=0;
    static float downsampler_value=0;
    static int downsampler_size=0;

    for(int i=0;i<size;i++)
    {
       downsampler_value += ((float) buffer[i])/32767.0;
       downsampler_counter++;
       if(downsampler_counter>=downsample_to)
       {
          downsampler_counter-=downsample_to;
          fb[downsampler_size] = downsampler_value/downsample_to;
          downsampler_value=0;
          downsampler_size++;
          if(downsampler_size==512)
          {
             DecodeAudioDownsampled(downsampler_size);
             downsampler_size=0;
          }
       }
    }

    CPULoad.End();

    float r = 1000.0 * (float) size / (float) SC.InSampleRate;
    float cpu_this = 100.0*CPULoad.elapsed_msec/r;
    cpu_load = (cpu_load*19.0+cpu_this)/20.0;
}

void __fastcall TFormMain::DecodeAudioDownsampled(int size)
{
    DisplayWaterfall(fb,size);

    if(RX.Clocked)
    {
       RX.Process_Audio_Clocked(fb,size);
    }
    else
    {
       RX.Process_Audio(fb,size);
    }

    if(RX.output_nbits>0)
    {
        VC.DecodeBuffer(RX.output_bits,RX.output_nbits);
        RX.output_nbits = 0;

        confidence = RX.confidence;
        if(Squelch && (confidence < squelch_thereshold))
        {
            VC.outsize = 0;
            //if(last_confidence >= squelch_thereshold) RXPrintString(RichEdit1,"[...]",RXCodesColor);
        }
        last_confidence = confidence;
        ShowMetric();
    }

    // print data on screen
    for(int i=0;i<VC.outsize;i++)
    {
       int ch = VC.out[i];
       RXPrintChar(RichEdit1,ch,RXFontColor);
       if(ch==0) StatusBar1->Panels->Items[0]->Text = "RX-Idle";
       else StatusBar1->Panels->Items[0]->Text = "RX";
    }
    VC.outsize = 0;

    // refresh menus
    static int ccc;
    ccc += size;
    if(ccc>4000)
    {
       UpdateMenu();
       ccc = 0;
    }
}

void __fastcall TFormMain::RXPrintString(TRichEdit *RE, AnsiString S, TColor col)
{
   int L = S.Length();
   for(int i=1;i<=L;i++) RXPrintChar(RE,S[i],col);
}

void __fastcall TFormMain::RXPrintSpecialChar(TRichEdit *RE, int code)
{
    AnsiString Dummy;

//         if(code==1)  Dummy = "\r\nTransmission de: ";
         if(code==1)  Dummy = AnsiString("\r\n[")+Now()+"] Transmission de: ";
    else if(code==2)  Dummy = "\r\nText:\r\n";
    //else if(code==3)  Dummy = "\r\n<ETX>\r\n";
    else if(code==4)  Dummy = "\r\nEnd of transmission\r\n";
    /*
    else if(code==5)  Dummy = "<ENQ>";
    else if(code==6)  Dummy = "<ACK>";
    else if(code==7)  Dummy = "<BEL>";
    else if(code==10) Dummy = "<LF>";
    else if(code==11) Dummy = "<VT>";
    else if(code==12) Dummy = "<FF>";
    else if(code==14) Dummy = "<SO>";
    else if(code==15) Dummy = "<SI>";
    else if(code==16) Dummy = "<DLE>";
    else if(code==17) Dummy = "<DC1>";
    else if(code==18) Dummy = "<DC2>";
    else if(code==19) Dummy = "<DC3>";
    else if(code==20) Dummy = "<DC4>";
    else if(code==21) Dummy = "<NAK>";
    else if(code==22) Dummy = "<SYN>";
    else if(code==23) Dummy = "<ETB>";
    else if(code==24) Dummy = "<CAN>";
    else if(code==25) Dummy = "<EM>";
    else if(code==26) Dummy = "<SUB>";
    else if(code==27) Dummy = "<ESC>";
    else if(code==28) Dummy = "<FS>";
    else if(code==29) Dummy = "<GS>";
    else if(code==30) Dummy = "<RS>";
    else if(code==31) Dummy = "<US>";
    */

    RE->SelStart = RE->Text.Length();
    RE->SelAttributes->Color = RXCodesColor;
    RE->SelText=Dummy;
}

void __fastcall TFormMain::RXPrintChar(TRichEdit *RE, int code, TColor col)
{
   AnsiString S;
   AnsiString C = AnsiString((char)code);
   int L;

   /*
   for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
   {
      ServerSocket1->Socket->Connections[i]->SendText(C);
   }
   */

   RE->SelAttributes->Color = col;

   switch(code)
   {
      case 0:
      case 127:
         break;

      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 10:
      case 11:
      case 12:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
      case 28:
      case 29:
      case 30:
      case 31:
         RXPrintSpecialChar(RE,code);
         break;

      case 8:
         RE->SelStart = RE->Text.Length()-1;
         RE->SelLength = 1;
         if(RE->SelText==AnsiString("\n"))
         {
            RE->SelStart = RE->Text.Length()-2;
            RE->SelLength = 2;
         }
         RE->SetSelTextBuf("");
         LogToFile(C);
         break;

      case 13:
         S = AnsiString("\r\n");
         RE->SelStart = RE->Text.Length();
         RE->SelLength = 1;
         RE->SetSelTextBuf(S.c_str());
         LogToFile(S);
         break;

      default:
         if(code>=32 || code==9)
         {
           S = C;
           RE->SelStart = RE->Text.Length();
           RE->SelLength = 1;
           RE->SetSelTextBuf(S.c_str());
           LogToFile(S);
         }
         break;
   }
}

void __fastcall TFormMain::DisplayWaterfall(float *vec, int size)
{
    for(int i=0;i<size;i++)
    {
       if(vec[i]<=-1.0 || vec[i]>=1.0) Overdrive=true;
       WFFT.ReceiveIQ(vec[i],0);

       if(WFFT.InCounter == 0)
       {
         if(FormMain->PanelWFFT->Visible)
         {
           WFFT.CalcFFT();
           ShowWaterfallWFFT();
         }
       }
    }
}

void __fastcall TFormMain::ShowWaterfallWFFT()
{
   int hy,hx,mx,my,t,size,off,sp1,sp2;

   size = (WFFT.fftsize*HWaterfallBand)/(SC.InSampleRate/7);
   off = 1+(WFFT.fftsize*HWaterfallStart)/(SC.InSampleRate/7);

   float max;
   float min;
   float cx;

   static float slow_max=0;
   static float Spectra[4096];

   if(WaterfallLogScale)
   {
     max = min = log(1+WFFT.Ampl[off]);
     for(t=0;t<size;t++)
     {
         Spectra[t] = log(1+WFFT.Ampl[t+off]);
         if(Spectra[t]>max) max = Spectra[t];
         if(Spectra[t]<min) min = Spectra[t];
     }
   }
   else
   {
     max = min = WFFT.Ampl[off];
     for(t=0;t<size;t++)
     {
         Spectra[t] = WFFT.Ampl[t+off];
         if(Spectra[t]>max) max = Spectra[t];
         if(Spectra[t]<min) min = Spectra[t];
     }
   }

   slow_max = slow_max * 0.8 + max * 0.2;
   max = slow_max;

   if(max-min != 0.0) cx = 256 / (max-min);
   else cx=1;

   mx = ImageWFFT->Width;
   my = ImageWFFT->Height;

   TColor col;
   HDC HandleCanvas = ImageWFFT->Canvas->Handle;
   ImageWFFT->Canvas->Lock();

   if(HorizontalWaterfall) BitBlt(HandleCanvas,0,0,mx,my,HandleCanvas,0,-1,SRCCOPY);
   else BitBlt(HandleCanvas,0,0,mx,my,HandleCanvas,+1,0,SRCCOPY);

   if(HorizontalWaterfall)
   {
      hx = 0;
      hy = 0; // hy-1
   }
   else
   {
      hx=mx;
      hy=my-1;
   }

   int end;
   if(HorizontalWaterfall) end=mx;
   else end=my;

   for(t=0;t<end;t++)
   {
       int c = (t * size) / (end);
       int c1 = ((t-1) * size) / (end);
       int c2 = ((t+1) * size) / (end);
       if(c1<0) c1=0;
       if(c2>size-1) c2=size-1;

       int index = (int) ((Spectra[c]-min)*cx+0.5*(Spectra[c1]-min)*cx+ 0.5*(Spectra[c2]-min)*cx)/2;
       //int index = (int) (Spectra[c]-min)*cx;

       if(index>255) index=255;
       if(index<0) index = 0;
       if(WaterfallLogScale) index = 255-index;
       if(Overdrive) col = (TColor) (0xFFFFFF - index*0x010100);
       else col = WPal.Colore[index];
       if(HorizontalWaterfall)
       {
          SetPixel(HandleCanvas,hx,hy,col);
          hx++;
       }
       else
       {
          SetPixel(HandleCanvas,hx,hy,col);
          hy--;
       }
   }

   if(HorizontalWaterfall)
   {
     SetPixel(HandleCanvas,mx*(RX.freq-HWaterfallStart)/HWaterfallBand,16,clRed);
     SetPixel(HandleCanvas,-1+mx*(RX.freq-HWaterfallStart)/HWaterfallBand,16,clWhite);
     SetPixel(HandleCanvas,+1+mx*(RX.freq-HWaterfallStart)/HWaterfallBand,16,clWhite);
   }
   else
   {
     SetPixel(HandleCanvas,ImageWFFT->Width-16,ImageWFFT->Height-my*(RX.freq-HWaterfallStart)/HWaterfallBand,clRed);
     SetPixel(HandleCanvas,ImageWFFT->Width-16,-1+ImageWFFT->Height-my*(RX.freq-HWaterfallStart)/HWaterfallBand,clWhite);
     SetPixel(HandleCanvas,ImageWFFT->Width-16,+1+ImageWFFT->Height-my*(RX.freq-HWaterfallStart)/HWaterfallBand,clWhite);
   }

   ImageWFFT->ControlStyle = ImageWFFT->ControlStyle << csOpaque;
   ImageWFFT->Invalidate();
   ImageWFFT->Canvas->Unlock();
   Overdrive=false;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    SC.StopWaveIn();
    SC.StopWaveOut();

    while(1)
    {
       Application->ProcessMessages();
       if(SC.InHandleDevice==0 && SC.OutHandleDevice==0) break;
    }
}

void __fastcall TFormMain::EncodeAudio(signed short *data, int size)
{
   unsigned char c;
   int t,i;

   // if we are not transmitting fill the buffer with silence
   if(RadioState != tx)
   {
      for(t=0;t<size;t++) data[t] = 0;
      return;
   }

   // poll audio data from transmitter
   while(TX.NSamples < size)
   {
      c = TransmitChar();
      TX.SendChar(c);
      if(c!=10) RXPrintChar(RichEdit1,c,TXFontColor1);
   }

   int volumelevel = (32000*SliderPowerControl->Position) / 100;

   // copy into audio buffer
   for(t=0;t<size;t++) data[t] = TX.Samples[t]*volumelevel;

   // move ahead transmit buffer
   for(t=size,i=0;t<TX.NSamples;t++,i++) TX.Samples[i] = TX.Samples[t];
   TX.NSamples -= size;

   if(FlushInvoked)
   {
     if(SendBuffer.Length()==0 && FlushCount==0)
     {
        FlushCount = TX.NSamples;
        TX.SendPostamble();
        FlushCount = TX.NSamples - FlushCount;
     }

     if(FlushCount>0)
     {
        FlushCount-=size;
        if(FlushCount<0)
        {
           FlushInvoked=false;
           StopTransmit();
           EditHell->OnChange = 0;
           EditHell->Lines->Add("<EOT>");
           EditHell->Lines->Add("");
           LastPos = EditHell->Text.Length();
           EditHell->OnChange = EditHellChange;
        }
     }
   }

   UpdateMenu();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuHelpClick(TObject *Sender)
{
   AnsiString Cmd = AnsiString("explorer.exe ")+ThePath+AnsiString("help\\help.htm");
   WinExec(Cmd.c_str(),SW_SHOWMAXIMIZED);
}


void __fastcall TFormMain::AboutClick(TObject *Sender)
{
    FormAbout->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuExitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::MenuStartReceiveClick(TObject *Sender)
{
    ButtonStartRxClick(this);
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::MenuStopTransmitClick(TObject *Sender)
{
    StopTransmit();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateMenu()
{
    AnsiString Dummy;

    float bps = RX.samplerate / RX.pixelsize;

    /*
    switch(Rate)
    {
        case RATE_R1:
             MenuUncoded->Checked = true;
             MenuModeR2->Checked = false;
             MenuModeR3->Checked = false;
             Dummy = "Uncoded";
             break;
        case RATE_R2:
             MenuUncoded->Checked = false;
             MenuModeR2->Checked = true;
             MenuModeR3->Checked = false;
             Dummy = "R=1/2,";
             break;
        case RATE_R3:
             MenuUncoded->Checked = false;
             MenuModeR2->Checked = false;
             MenuModeR3->Checked = true;
             Dummy = "R=1/3,";
             break;
    }

    if(Rate!=RATE_R1) switch(KMode)
    {
       case CODE_K5:
          MenuModeK5->Checked = true;
          MenuModeK7->Checked = false;
          MenuModeK9->Checked = false;
          Dummy = Dummy + " K=5";
          break;
       case CODE_K7:
          MenuModeK5->Checked = false;
          MenuModeK7->Checked = true;
          MenuModeK9->Checked = false;
          Dummy = Dummy + " K=7";
          break;
       case CODE_K9:
          MenuModeK5->Checked = false;
          MenuModeK7->Checked = false;
          MenuModeK9->Checked = true;
          Dummy = Dummy + " K=9";
          break;
    }
    StatusBar1->Panels->Items[2]->Text = Dummy;
    */

    /*
    if(RX.qpsk)
    {
       MenuBPSK->Checked = false;
       MenuQPSK->Checked = true;
       Dummy = "QPSK";
       bps *= 2;
    }
    else
    {
       MenuBPSK->Checked = true;
       MenuQPSK->Checked = false;
       Dummy = "BPSK";
    }
    StatusBar1->Panels->Items[3]->Text = Dummy;
    */

    /*
    switch(BaudRate)
    {
        case BAUD_3:
             MenuMode3->Checked = true;
             MenuMode7->Checked = false;
             MenuMode15->Checked = false;
             MenuMode31->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = false;
             MenuMode125->Checked = false;
             Dummy = "3.90625 baud";
             break;
        case BAUD_7:
             MenuMode3->Checked = false;
             MenuMode7->Checked = true;
             MenuMode15->Checked = false;
             MenuMode31->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = false;
             MenuMode125->Checked = false;
             Dummy = "7.8125 baud";
             break;
        case BAUD_15:
             MenuMode3->Checked = false;
             MenuMode7->Checked = false;
             MenuMode15->Checked = true;
             MenuMode31->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = false;
             MenuMode125->Checked = false;
             Dummy = "15.625 baud";
             break;
        case BAUD_31:
             MenuMode3->Checked = false;
             MenuMode7->Checked = false;
             MenuMode31->Checked = true;
             MenuMode15->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = false;
             MenuMode125->Checked = false;
             Dummy = "31.25 baud";
             break;
        case BAUD_62:
             MenuMode3->Checked = false;
             MenuMode7->Checked = false;
             MenuMode31->Checked = false;
             MenuMode15->Checked = false;
             MenuMode64->Checked = true;
             MenuMode250->Checked = false;
             MenuMode125->Checked = false;
             Dummy = "62.5 baud";
             break;
        case BAUD_125:
             MenuMode3->Checked = false;
             MenuMode7->Checked = false;
             MenuMode15->Checked = false;
             MenuMode31->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = false;
             MenuMode125->Checked = true;
             Dummy = "125 baud";
             break;
        case BAUD_250:
             MenuMode3->Checked = false;
             MenuMode7->Checked = false;
             MenuMode15->Checked = false;
             MenuMode31->Checked = false;
             MenuMode64->Checked = false;
             MenuMode250->Checked = true;
             MenuMode125->Checked = false;
             Dummy = "250 baud";
             break;
    }
    StatusBar1->Panels->Items[4]->Text = Dummy;
    */

    StatusBar1->Panels->Items[5]->Text = FormatFloat("0.00",bps)+" baud";
    StatusBar1->Panels->Items[4]->Text = FormatFloat("0.00",RX.nbits*bps/RX.pnsize)+" bps";

    if(RadioState==rx)
    {
       ButtonStartRx->Down = true;
       //StatusBar1->Panels->Items[0]->Text = "RX";
    }
    else if(RadioState==tx)
    {
       if(FlushInvoked) Dummy = "Closing";
       else Dummy = "TX";
       StatusBar1->Panels->Items[0]->Text = Dummy;
    }
    else if(RadioState==paused)
    {
       ButtonStartRx->Down = false;
       StatusBar1->Panels->Items[0]->Text = "Paused";
    }

    MenuFixHyperthreading->Checked = !RX.IntegerMath;

    MenuLogFile->Checked = LogFile;

    int l = SendBuffer.Length();
    if(l>0) Dummy = "Buffer: "+AnsiString(l);
    else Dummy = "Empty";
    StatusBar1->Panels->Items[1]->Text = Dummy;

    if(RadioState==rx) StatusBar1->Panels->Items[6]->Text = "CPU load: " + FormatFloat("0",cpu_load)+"%";
    else StatusBar1->Panels->Items[6]->Text = "CPU load: ---";

    // Ora UTC
    SYSTEMTIME SystemTime;
    GetSystemTime(&SystemTime);
    AnsiString Expanded = SystemTimeToDateTime(SystemTime).FormatString("ddd d mmm - hh:mm:ss");
    StatusBar1->Panels->Items[7]->Text = Expanded+" UTC";

    if(LogState) ToolButtonLog->Down=true;
    else ToolButtonLog->Down=false;

    UpdateEditFreq();
}

void __fastcall TFormMain::EditHellKeyPress(TObject *Sender, char &Key)
{
    if(Key==8)
    {
       StuffBuff(Key);
       LastPos = EditHell->Text.Length()-1;
       if(LastPos<=0) LastPos=0;
    }
    if(EditHell->SelStart!=EditHell->Text.Length())
    {
       EditHell->SelStart=EditHell->Text.Length(); //Key=0;
    }
}

void __fastcall TFormMain::StuffBuff(char Key)
{
    int L=SendBuffer.Length();

    // avoid to transmit the LF character
    if(Key==10) return;

    // rubbot last char if not already sent else send code 0x08
    if(Key==8 && L>1) SendBuffer = SendBuffer.SubString(1,L-1);
    else              SendBuffer = SendBuffer + AnsiString(Key);

    L=SendBuffer.Length();

    // there is nothing to transmit?
    if(L==0) return;

    // do not transmit if first char is '*'
    if(SendBuffer[1]=='*') return;

    // see if we need to start transmit
    if(RadioState != tx)  StartTransmit();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton2Click(TObject *Sender)
{
   AnsiString CmdLine = MixerProgram + " /play";
   WinExec(CmdLine.c_str(),SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton3Click(TObject *Sender)
{
   AnsiString CmdLine = MixerProgram + " /record";
   WinExec(CmdLine.c_str(),SW_SHOWNORMAL);
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonStartRxClick(TObject *Sender)
{
    ButtonStartRx->Down = !ButtonStartRx->Down;
    if(RadioState == paused)
    {
       SC.InSampleRate  = 44100;
       SC.OutSampleRate = 44100;
       SC.StartWaveIn();
       SC.StartWaveOut();
       RadioState = rx;
    }
    else
    {
       SC.StopWaveIn();
       SC.StopWaveOut();
       RadioState = paused;
    }
    UpdateMenu();
}

//---------------------------------------------------------------------------


AnsiString __fastcall TFormMain::GetSystemInSoundCards()
{
    int NumDevices;
    AnsiString List;

    NumDevices = waveInGetNumDevs();
    for(int t=0;t<NumDevices;t++)
    {
       WAVEINCAPS capacita;
       waveInGetDevCaps(t,&capacita,sizeof(capacita));
       AnsiString Dummy = AnsiString(capacita.szPname);
       List = List + Dummy + "\r\n";
    }
    return List;
}

AnsiString __fastcall TFormMain::GetSystemOutSoundCards()
{
    int NumDevices;
    AnsiString List;

    NumDevices = waveOutGetNumDevs();
    for(int t=0;t<NumDevices;t++)
    {
       WAVEOUTCAPS capacita;
       waveOutGetDevCaps(t,&capacita,sizeof(capacita));
       AnsiString Dummy = AnsiString(capacita.szPname);
       List = List + Dummy + "\r\n";
    }
    return List;
}

void __fastcall TFormMain::Preferences1Click(TObject *Sender)
{
    FormSetup->RadioGroupPTT->ItemIndex = PTTPort;
    FormSetup->EditCallSign->Text = CallSign;
    FormSetup->EditStationName->Text = StationName;
    FormSetup->EditStationQTH->Text = StationQTH;
    FormSetup->EditStationLocator->Text = StationLocator;
    FormSetup->EditStationEmail->Text = StationEmail;

    FormSetup->EditCenterQRG->Text = CenterQRG;

    FormSetup->RadioGroupWaterfallSpeed->ItemIndex = WaterfallSpeed;

    FormSetup->EditSquelch->Text = squelch_thereshold;

    FormSetup->EditAFCAttack->Text = FormatFloat("0.000",RX.afc_attack);

    FormSetup->ComboBoxOversample->Text = RX.oversample;

    FormSetup->EditLogger32Program->Text = Log32.Logger32Program;
    FormSetup->CheckBoxLogger32Load->Checked = Log32.Logger32Load;
    FormSetup->CheckBoxLogger32Close->Checked = Log32.Logger32Close;
    FormSetup->CheckBoxLogger32ClientOnTop->Checked = Log32.Logger32ClientOnTop;

    FormSetup->EditMixerProgram->Text = MixerProgram;

    if(WaterfallLogScale) FormSetup->RadioGroupWaterfallDisplay->ItemIndex = 0;
    else FormSetup->RadioGroupWaterfallDisplay->ItemIndex = 1;

    FormSetup->ComboBoxInSoundCard->Items->Text = GetSystemInSoundCards();
    FormSetup->ComboBoxInSoundCard->ItemIndex = SC.InSoundCard;
    FormSetup->ComboBoxOutSoundCard->Items->Text = GetSystemOutSoundCards();
    FormSetup->ComboBoxOutSoundCard->ItemIndex = SC.OutSoundCard;

    FormSetup->CampoMemoStartFrequency->Text = HWaterfallStart;
    FormSetup->CampoMemoEndFrequency->Text   = HWaterfallStart+HWaterfallBand;

    if(FormSetup->ShowModal()==mrOk)
    {
        PTT.Close();
        PTTPort = FormSetup->RadioGroupPTT->ItemIndex;
        PTT.SetPort(PTTPort);
        PTT.Open();

        Log32.Logger32Program     = FormSetup->EditLogger32Program->Text;
        Log32.Logger32Load        = FormSetup->CheckBoxLogger32Load->Checked;
        Log32.Logger32Close       = FormSetup->CheckBoxLogger32Close->Checked;
        Log32.Logger32ClientOnTop = FormSetup->CheckBoxLogger32ClientOnTop->Checked;

        if(Log32.Logger32ClientOnTop) FormStyle = fsStayOnTop;
        else FormStyle = fsNormal;

        CallSign       = FormSetup->EditCallSign->Text;
        StationName    = FormSetup->EditStationName->Text;
        StationQTH     = FormSetup->EditStationQTH->Text;
        StationLocator = FormSetup->EditStationLocator->Text;
        StationEmail   = FormSetup->EditStationEmail->Text;

        CenterQRG = atof(FormSetup->EditCenterQRG->Text.c_str());

        squelch_thereshold = FormSetup->EditSquelch->Text.ToInt();
        RX.afc_attack = atof(FormSetup->EditAFCAttack->Text.c_str());
        RX.oversample = FormSetup->ComboBoxOversample->Text.ToInt();
        RX.SetOversample();

        UpdateMenu();

        WaterfallSpeed = FormSetup->RadioGroupWaterfallSpeed->ItemIndex;
        WFFT.SetSize(1<<(9+WaterfallSpeed));

        WaterfallLogScale = (FormSetup->RadioGroupWaterfallDisplay->ItemIndex == 0);

        MixerProgram = FormSetup->EditMixerProgram->Text;

        if(FormSetup->ComboBoxInSoundCard->ItemIndex  != SC.InSoundCard ||
           FormSetup->ComboBoxOutSoundCard->ItemIndex != SC.OutSoundCard )
        {
           SC.InSoundCard = FormSetup->ComboBoxInSoundCard->ItemIndex;
           SC.OutSoundCard = FormSetup->ComboBoxOutSoundCard->ItemIndex;
           if(RadioState!=paused) ButtonStartRxClick(this);
        }

        HWaterfallStart = FormSetup->CampoMemoStartFrequency->Text.ToInt();
        HWaterfallBand  = FormSetup->CampoMemoEndFrequency->Text.ToInt() - HWaterfallStart;

        /*
        if(HWaterfallStart < 100) HWaterfallStart = 100;
        if((HWaterfallBand+HWaterfallStart) > 4000 || (HWaterfallBand<50))
        {
           HWaterfallStart = 100;
           HWaterfallBand = 2900;
        }
        */
        DrawWaterfallScale();

        UpdateButtons();
    };
}

void __fastcall TFormMain::FormResize(TObject *Sender)
{
    SetWaterfallPosition();

    EditHell->Height = TransmitBoxSize;

    ImageScaleWFFT->Picture->Bitmap->Height = PanelWFFT->Height;
    ImageScaleWFFT->Picture->Bitmap->Width = PanelWFFT->Width;

    ImageWFFT->Picture->Bitmap->Height = PanelWFFT->Height;
    ImageWFFT->Picture->Bitmap->Width = PanelWFFT->Width;

    ImageCorrelation->Picture->Bitmap->Height = ImageCorrelation->Height;
    ImageCorrelation->Picture->Bitmap->Width  = ImageCorrelation->Width;

    DrawWaterfallScale();

    UpdateButtons();

    /*
    int spaceleft = PanelLogo->Left - PanelWaterfall->Left;
    PanelWaterfall->Width = spaceleft * 0.5;
    PanelDelay->Left = PanelWaterfall->Left + PanelWaterfall->Width+1;
    PanelDelay->Width = spaceleft * 0.5;
    */
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonSendClick(TObject *Sender)
{
    AnsiString Text;

    if(Sender==ButtonSend1) Text = Button1Text;
    if(Sender==ButtonSend2) Text = Button2Text;
    if(Sender==ButtonSend3) Text = Button3Text;
    if(Sender==ButtonSend4) Text = Button4Text;
    if(Sender==ButtonSend5) Text = Button5Text;
    if(Sender==ButtonSend6) Text = Button6Text;
    if(Sender==ButtonSend7) Text = Button7Text;
    if(Sender==ButtonSend8) Text = Button8Text;
    if(Sender==ButtonSend9) Text = Button9Text;
    if(Sender==ButtonSend10) Text= Button10Text;
    if(Sender==ButtonSend11) Text= Button11Text;
    if(Sender==ButtonSend12) Text= Button12Text;

    SendString(Text);
}

void __fastcall TFormMain::SendString(AnsiString Stringa)
{
    EditHell->Text = EditHell->Text+Stringa;
    EditHell->SelStart = EditHell->Text.Length();
    EditHell->SelLength = 1;
    EditHell->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SendFile1Click(TObject *Sender)
{
    TOpenDialog *DialogFile = new TOpenDialog(this);
    DialogFile->InitialDir = ExtractFilePath(SendFileFolder);
    DialogFile->FileName = ExtractFileName(SendFileFolder);
    if(DialogFile->Execute())
    {
       TStringList *TextFile = new TStringList;
       TextFile->LoadFromFile(DialogFile->FileName);
       SendFileFolder = DialogFile->FileName;
       SendString(TextFile->Text);
    }
    delete DialogFile;
}

//---------------------------------------------------------------------------


void __fastcall TFormMain::UpdateButtons()
{
   ButtonSend1->Caption = Button1Label;
   ButtonSend2->Caption = Button2Label;
   ButtonSend3->Caption = Button3Label;
   ButtonSend4->Caption = Button4Label;
   ButtonSend5->Caption = Button5Label;
   ButtonSend6->Caption = Button6Label;
   ButtonSend7->Caption = Button7Label;
   ButtonSend8->Caption = Button8Label;
   ButtonSend9->Caption = Button9Label;
   ButtonSend10->Caption = Button10Label;
   ButtonSend11->Caption = Button11Label;
   ButtonSend12->Caption = Button12Label;

   // on two rows

     int bs = ((PanelButtons->Width - ButtonSend1->Left)-4)/6-1;
     ButtonSend1->Width = bs;
     ButtonSend2->Left = ButtonSend1->Left+ButtonSend1->Width+1; ButtonSend2->Width = bs;
     ButtonSend3->Left = ButtonSend2->Left+ButtonSend2->Width+1; ButtonSend3->Width = bs;
     ButtonSend4->Left = ButtonSend3->Left+ButtonSend3->Width+1; ButtonSend4->Width = bs;
     ButtonSend5->Left = ButtonSend4->Left+ButtonSend4->Width+1; ButtonSend5->Width = bs;
     ButtonSend6->Left = ButtonSend5->Left+ButtonSend5->Width+1; ButtonSend6->Width = bs;
     ButtonSend7->Width = bs;
     ButtonSend8->Left  = ButtonSend7->Left+ButtonSend7->Width+1;   ButtonSend8->Width = bs;
     ButtonSend9->Left  = ButtonSend8->Left+ButtonSend8->Width+1;   ButtonSend9->Width = bs;
     ButtonSend10->Left = ButtonSend9->Left+ButtonSend9->Width+1;   ButtonSend10->Width = bs;
     ButtonSend11->Left = ButtonSend10->Left+ButtonSend10->Width+1; ButtonSend11->Width = bs;
     ButtonSend12->Left = ButtonSend11->Left+ButtonSend11->Width+1; ButtonSend12->Width = bs;

     LabelSend1->Width = ButtonSend1->Width;  LabelSend1->Left = ButtonSend1->Left;
     LabelSend2->Width = ButtonSend2->Width;  LabelSend2->Left = ButtonSend2->Left;
     LabelSend3->Width = ButtonSend3->Width;  LabelSend3->Left = ButtonSend3->Left;
     LabelSend4->Width = ButtonSend4->Width;  LabelSend4->Left = ButtonSend4->Left;
     LabelSend5->Width = ButtonSend5->Width;  LabelSend5->Left = ButtonSend5->Left;
     LabelSend6->Width = ButtonSend6->Width;  LabelSend6->Left = ButtonSend6->Left;
     LabelSend7->Width = ButtonSend7->Width;  LabelSend7->Left = ButtonSend7->Left;
     LabelSend8->Width = ButtonSend8->Width;  LabelSend8->Left = ButtonSend8->Left;
     LabelSend9->Width = ButtonSend9->Width;  LabelSend9->Left = ButtonSend9->Left;
     LabelSend10->Width = ButtonSend10->Width;  LabelSend10->Left = ButtonSend10->Left;
     LabelSend11->Width = ButtonSend11->Width;  LabelSend11->Left = ButtonSend11->Left;
     LabelSend12->Width = ButtonSend12->Width;  LabelSend12->Left = ButtonSend12->Left;

     ButtonSend12->Visible = ButtonSend12->Left+ButtonSend12->Width < PanelButtons->Width;
     ButtonSend11->Visible = ButtonSend11->Left+ButtonSend11->Width < PanelButtons->Width;
     ButtonSend10->Visible = ButtonSend10->Left+ButtonSend10->Width < PanelButtons->Width;
     ButtonSend9->Visible = ButtonSend9->Left+ButtonSend9->Width < PanelButtons->Width;
     ButtonSend8->Visible = ButtonSend8->Left+ButtonSend8->Width < PanelButtons->Width;
     ButtonSend7->Visible = ButtonSend7->Left+ButtonSend7->Width < PanelButtons->Width;
     ButtonSend6->Visible = ButtonSend6->Left+ButtonSend6->Width < PanelButtons->Width;
     ButtonSend5->Visible = ButtonSend5->Left+ButtonSend5->Width < PanelButtons->Width;
     ButtonSend4->Visible = ButtonSend4->Left+ButtonSend4->Width < PanelButtons->Width;
     ButtonSend3->Visible = ButtonSend3->Left+ButtonSend3->Width < PanelButtons->Width;
     ButtonSend2->Visible = ButtonSend2->Left+ButtonSend2->Width < PanelButtons->Width;
     ButtonSend1->Visible = ButtonSend1->Left+ButtonSend1->Width < PanelButtons->Width;

     LabelSend12->Visible = LabelSend12->Left+LabelSend12->Width < PanelButtons->Width;
     LabelSend11->Visible = LabelSend11->Left+LabelSend11->Width < PanelButtons->Width;
     LabelSend10->Visible = LabelSend10->Left+LabelSend10->Width < PanelButtons->Width;
     LabelSend9->Visible = LabelSend9->Left+LabelSend9->Width < PanelButtons->Width;
     LabelSend8->Visible = LabelSend8->Left+LabelSend8->Width < PanelButtons->Width;
     LabelSend7->Visible = LabelSend7->Left+LabelSend7->Width < PanelButtons->Width;
     LabelSend6->Visible = LabelSend6->Left+LabelSend6->Width < PanelButtons->Width;
     LabelSend5->Visible = LabelSend5->Left+LabelSend5->Width < PanelButtons->Width;
     LabelSend4->Visible = LabelSend4->Left+LabelSend4->Width < PanelButtons->Width;
     LabelSend3->Visible = LabelSend3->Left+LabelSend3->Width < PanelButtons->Width;
     LabelSend2->Visible = LabelSend2->Left+LabelSend2->Width < PanelButtons->Width;
     LabelSend1->Visible = LabelSend1->Left+LabelSend1->Width < PanelButtons->Width;


   /*
   else
   {
     int bs = (PanelButtons->Height-4)/13;

     SpeedButtonCQ->Top = (PanelButtons->Height - (bs*13))/2;
     SpeedButtonCQ->Height = bs-1;

     ButtonSend1->Top  = SpeedButtonCQ->Top+SpeedButtonCQ->Height+1; ButtonSend1->Height = bs-1;
     ButtonSend2->Top  = ButtonSend1->Top+ButtonSend1->Height+1;   ButtonSend2->Height = bs-1;
     ButtonSend3->Top  = ButtonSend2->Top+ButtonSend2->Height+1;   ButtonSend3->Height = bs-1;
     ButtonSend4->Top  = ButtonSend3->Top+ButtonSend3->Height+1;   ButtonSend4->Height = bs-1;
     ButtonSend5->Top  = ButtonSend4->Top+ButtonSend4->Height+1;   ButtonSend5->Height = bs-1;
     ButtonSend6->Top  = ButtonSend5->Top+ButtonSend5->Height+1;   ButtonSend6->Height = bs-1;
     ButtonSend7->Top  = ButtonSend6->Top+ButtonSend6->Height+1;   ButtonSend7->Height = bs-1;
     ButtonSend8->Top  = ButtonSend7->Top+ButtonSend7->Height+1;   ButtonSend8->Height = bs-1;
     ButtonSend9->Top  = ButtonSend8->Top+ButtonSend8->Height+1;   ButtonSend9->Height = bs-1;
     ButtonSend10->Top = ButtonSend9->Top+ButtonSend9->Height+1;   ButtonSend10->Height = bs-1;
     ButtonSend11->Top = ButtonSend10->Top+ButtonSend10->Height+1; ButtonSend11->Height = bs-1;
     ButtonSend12->Top = ButtonSend11->Top+ButtonSend11->Height+1; ButtonSend12->Height = bs-1;

     SpeedButtonCQ->Width = 55;
     ButtonSend1->Left  = SpeedButtonCQ->Left;  ButtonSend1->Width = SpeedButtonCQ->Width;
     ButtonSend2->Left  = ButtonSend1->Left;    ButtonSend2->Width = ButtonSend1->Width;
     ButtonSend3->Left  = ButtonSend1->Left;    ButtonSend3->Width = ButtonSend2->Width;
     ButtonSend4->Left  = ButtonSend1->Left;    ButtonSend4->Width = ButtonSend3->Width;
     ButtonSend5->Left  = ButtonSend1->Left;    ButtonSend5->Width = ButtonSend4->Width;
     ButtonSend6->Left  = ButtonSend1->Left;    ButtonSend6->Width = ButtonSend5->Width;
     ButtonSend7->Left  = ButtonSend1->Left;    ButtonSend7->Width = ButtonSend6->Width;
     ButtonSend8->Left  = ButtonSend1->Left;    ButtonSend8->Width = ButtonSend7->Width;
     ButtonSend9->Left  = ButtonSend1->Left;    ButtonSend9->Width = ButtonSend8->Width;
     ButtonSend10->Left = ButtonSend1->Left;    ButtonSend10->Width = ButtonSend9->Width;
     ButtonSend11->Left = ButtonSend1->Left;    ButtonSend11->Width = ButtonSend10->Width;
     ButtonSend12->Left = ButtonSend1->Left;    ButtonSend12->Width = ButtonSend11->Width;

     LabelSend1->Top = ButtonSend1->Top;  LabelSend1->Left = ButtonSend1->Left+ButtonSend1->Width;
     LabelSend2->Top = ButtonSend2->Top;  LabelSend2->Left = ButtonSend2->Left+ButtonSend2->Width;
     LabelSend3->Top = ButtonSend3->Top;  LabelSend3->Left = ButtonSend3->Left+ButtonSend3->Width;
     LabelSend4->Top = ButtonSend4->Top;  LabelSend4->Left = ButtonSend4->Left+ButtonSend4->Width;
     LabelSend5->Top = ButtonSend5->Top;  LabelSend5->Left = ButtonSend5->Left+ButtonSend5->Width;
     LabelSend6->Top = ButtonSend6->Top;  LabelSend6->Left = ButtonSend6->Left+ButtonSend6->Width;
     LabelSend7->Top = ButtonSend7->Top;  LabelSend7->Left = ButtonSend7->Left+ButtonSend7->Width;
     LabelSend8->Top = ButtonSend8->Top;  LabelSend8->Left = ButtonSend8->Left+ButtonSend8->Width;
     LabelSend9->Top = ButtonSend9->Top;  LabelSend9->Left = ButtonSend9->Left+ButtonSend9->Width;
     LabelSend10->Top = ButtonSend10->Top;  LabelSend10->Left = ButtonSend10->Left+ButtonSend10->Width;
     LabelSend11->Top = ButtonSend11->Top;  LabelSend11->Left = ButtonSend11->Left+ButtonSend11->Width;
     LabelSend12->Top = ButtonSend12->Top;  LabelSend12->Left = ButtonSend12->Left+ButtonSend12->Width;

     LabelSend1->Width = 22;
     LabelSend2->Width = LabelSend1->Width;
     LabelSend3->Width = LabelSend2->Width;
     LabelSend4->Width = LabelSend3->Width;
     LabelSend5->Width = LabelSend4->Width;
     LabelSend6->Width = LabelSend5->Width;
     LabelSend7->Width = LabelSend6->Width;
     LabelSend8->Width = LabelSend7->Width;
     LabelSend9->Width = LabelSend8->Width;
     LabelSend10->Width = LabelSend9->Width;
     LabelSend11->Width = LabelSend10->Width;
     LabelSend12->Width = LabelSend11->Width;
   }
   */

   /*
   // on signle row
   int bs = (PanelButtons->Width-4)/13;

   SpeedButtonCQ->Left = (PanelButtons->Width - (bs*13))/2;
   SpeedButtonCQ->Width = bs-1;
   SpeedButtonCQ->Height = ButtonSend1->Height;

   ButtonSend1->Left  = SpeedButtonCQ->Left+SpeedButtonCQ->Width+1;ButtonSend1->Width = bs-1;
   ButtonSend2->Left  = ButtonSend1->Left+ButtonSend1->Width+1;   ButtonSend2->Width = bs-1;
   ButtonSend3->Left  = ButtonSend2->Left+ButtonSend2->Width+1;   ButtonSend3->Width = bs-1;
   ButtonSend4->Left  = ButtonSend3->Left+ButtonSend3->Width+1;   ButtonSend4->Width = bs-1;
   ButtonSend5->Left  = ButtonSend4->Left+ButtonSend4->Width+1;   ButtonSend5->Width = bs-1;
   ButtonSend6->Left  = ButtonSend5->Left+ButtonSend5->Width+1;   ButtonSend6->Width = bs-1;
   ButtonSend7->Left  = ButtonSend6->Left+ButtonSend6->Width+1;   ButtonSend7->Width = bs-1;
   ButtonSend8->Left  = ButtonSend7->Left+ButtonSend7->Width+1;   ButtonSend8->Width = bs-1;
   ButtonSend9->Left  = ButtonSend8->Left+ButtonSend8->Width+1;   ButtonSend9->Width = bs-1;
   ButtonSend10->Left = ButtonSend9->Left+ButtonSend9->Width+1;   ButtonSend10->Width = bs-1;
   ButtonSend11->Left = ButtonSend10->Left+ButtonSend10->Width+1; ButtonSend11->Width = bs-1;
   ButtonSend12->Left = ButtonSend11->Left+ButtonSend11->Width+1; ButtonSend12->Width = bs-1;

   ButtonSend2->Top  = ButtonSend1->Top;
   ButtonSend3->Top  = ButtonSend1->Top;
   ButtonSend4->Top  = ButtonSend1->Top;
   ButtonSend5->Top  = ButtonSend1->Top;
   ButtonSend6->Top  = ButtonSend1->Top;
   ButtonSend7->Top  = ButtonSend1->Top;
   ButtonSend8->Top  = ButtonSend1->Top;
   ButtonSend9->Top  = ButtonSend1->Top;
   ButtonSend10->Top = ButtonSend1->Top;
   ButtonSend11->Top = ButtonSend1->Top;
   ButtonSend12->Top = ButtonSend1->Top;

   LabelSend2->Top = LabelSend1->Top;
   LabelSend3->Top = LabelSend1->Top;
   LabelSend4->Top = LabelSend1->Top;
   LabelSend5->Top = LabelSend1->Top;
   LabelSend6->Top = LabelSend1->Top;
   LabelSend7->Top = LabelSend1->Top;
   LabelSend8->Top = LabelSend1->Top;
   LabelSend9->Top = LabelSend1->Top;
   LabelSend10->Top = LabelSend1->Top;
   LabelSend11->Top = LabelSend1->Top;
   LabelSend12->Top = LabelSend1->Top;

   LabelSend1->Width = ButtonSend1->Width;  LabelSend1->Left = ButtonSend1->Left;
   LabelSend2->Width = ButtonSend2->Width;  LabelSend2->Left = ButtonSend2->Left;
   LabelSend3->Width = ButtonSend3->Width;  LabelSend3->Left = ButtonSend3->Left;
   LabelSend4->Width = ButtonSend4->Width;  LabelSend4->Left = ButtonSend4->Left;
   LabelSend5->Width = ButtonSend5->Width;  LabelSend5->Left = ButtonSend5->Left;
   LabelSend6->Width = ButtonSend6->Width;  LabelSend6->Left = ButtonSend6->Left;
   LabelSend7->Width = ButtonSend7->Width;  LabelSend7->Left = ButtonSend7->Left;
   LabelSend8->Width = ButtonSend8->Width;  LabelSend8->Left = ButtonSend8->Left;
   LabelSend9->Width = ButtonSend9->Width;  LabelSend9->Left = ButtonSend9->Left;
   LabelSend10->Width = ButtonSend10->Width;  LabelSend10->Left = ButtonSend10->Left;
   LabelSend11->Width = ButtonSend11->Width;  LabelSend11->Left = ButtonSend11->Left;
   LabelSend12->Width = ButtonSend12->Width;  LabelSend12->Left = ButtonSend12->Left;
   */

   // MENU
   MenuMacro1->Caption = Button1Label;    MenuMacro1->Visible = (MenuMacro1->Caption!="");
   MenuMacro2->Caption = Button2Label;    MenuMacro2->Visible = (MenuMacro2->Caption!="");
   MenuMacro3->Caption = Button3Label;    MenuMacro3->Visible = (MenuMacro3->Caption!="");
   MenuMacro4->Caption = Button4Label;    MenuMacro4->Visible = (MenuMacro4->Caption!="");
   MenuMacro5->Caption = Button5Label;    MenuMacro5->Visible = (MenuMacro5->Caption!="");
   MenuMacro6->Caption = Button6Label;    MenuMacro6->Visible = (MenuMacro6->Caption!="");
   MenuMacro7->Caption = Button7Label;    MenuMacro7->Visible = (MenuMacro7->Caption!="");
   MenuMacro8->Caption = Button8Label;    MenuMacro8->Visible = (MenuMacro8->Caption!="");
   MenuMacro9->Caption = Button9Label;    MenuMacro9->Visible = (MenuMacro9->Caption!="");
   MenuMacro10->Caption = Button10Label;  MenuMacro10->Visible = (MenuMacro10->Caption!="");
   MenuMacro11->Caption = Button11Label;  MenuMacro11->Visible = (MenuMacro11->Caption!="");
   MenuMacro12->Caption = Button12Label;  MenuMacro12->Visible = (MenuMacro12->Caption!="");
}

void __fastcall TFormMain::Definebutton1Click(int tag)
{
    AnsiString Text,Label;
         if(tag==0) { Text = CQString;    Label = "CQ"; }
    else if(tag==1) { Text = Button1Text; Label = Button1Label; }
    else if(tag==2) { Text = Button2Text; Label = Button2Label; }
    else if(tag==3) { Text = Button3Text; Label = Button3Label; }
    else if(tag==4) { Text = Button4Text; Label = Button4Label; }
    else if(tag==5) { Text = Button5Text; Label = Button5Label; }
    else if(tag==6) { Text = Button6Text; Label = Button6Label; }
    else if(tag==7) { Text = Button7Text; Label = Button7Label; }
    else if(tag==8) { Text = Button8Text; Label = Button8Label; }
    else if(tag==9) { Text = Button9Text; Label = Button9Label; }
    else if(tag==10){ Text = Button10Text; Label = Button10Label; }
    else if(tag==11){ Text = Button11Text; Label = Button11Label; }
    else if(tag==12){ Text = Button12Text; Label = Button12Label; }

    FormDefineButton->EditButtonText->Text = Text;
    FormDefineButton->EditButtonLabel->Text = Label;
    if(tag==0) FormDefineButton->Caption = "Define CQ button";
    else       FormDefineButton->Caption = "Define button n."+AnsiString(tag);

    if(FormDefineButton->ShowModal() == mrCancel) return;
    Text = FormDefineButton->EditButtonText->Text;
    Label = FormDefineButton->EditButtonLabel->Text;

         if(tag==0) { CQString = Text; }
    else if(tag==1) { Button1Text = Text; Button1Label = Label; }
    else if(tag==2) { Button2Text = Text; Button2Label = Label; }
    else if(tag==3) { Button3Text = Text; Button3Label = Label; }
    else if(tag==4) { Button4Text = Text; Button4Label = Label; }
    else if(tag==5) { Button5Text = Text; Button5Label = Label; }
    else if(tag==6) { Button6Text = Text; Button6Label = Label; }
    else if(tag==7) { Button7Text = Text; Button7Label = Label; }
    else if(tag==8) { Button8Text = Text; Button8Label = Label; }
    else if(tag==9) { Button9Text = Text; Button9Label = Label; }
    else if(tag==10) { Button10Text = Text; Button10Label = Label; }
    else if(tag==11) { Button11Text = Text; Button11Label = Label; }
    else if(tag==12) { Button12Text = Text; Button12Label = Label; }
    UpdateButtons();
}

//---------------------------------------------------------------------------

unsigned char __fastcall TFormMain::TransmitChar()
{
   unsigned char c;
   int space,crlf;

   int L = SendBuffer.Length();
   if(L==0) return 0;

   c = SendBuffer[1];
   space = SendBuffer.AnsiPos(" ");
   crlf = SendBuffer.AnsiPos("\r");
   if((crlf<space && crlf!=0) || (space==0 && crlf>0) ) space=crlf;
   if(c=='$')
   {
       if(space==0) return 0;
       AnsiString Command = SendBuffer.SubString(2,space-2).UpperCase();
       AnsiString Expanded = ParseMetaCommand(Command);
       L = SendBuffer.Length();
       SendBuffer = Expanded+SendBuffer.SubString(space,L);
       if(Expanded==Command) return '$';
       else return 0;
   }
   else
   {
       SendBuffer = SendBuffer.SubString(2,L-1);
       return c;
   }
}

AnsiString __fastcall TFormMain::ParseMetaCommand(AnsiString Command)
{
      AnsiString Expanded = Command;

      if(Command=="CQ")        Expanded = CQString;
      else if(Command=="QRZ")  Expanded = CallSign;
      else if(Command=="TIME") Expanded = TDateTime().CurrentDateTime().TimeString();
      else if(Command=="UTC")
      {
         SYSTEMTIME SystemTime;
         GetSystemTime(&SystemTime);
         Expanded = SystemTimeToDateTime(SystemTime).TimeString();
      }
      else if(Command=="DATEUTC")
      {
         SYSTEMTIME SystemTime;
         GetSystemTime(&SystemTime);
         Expanded = SystemTimeToDateTime(SystemTime).DateString();
      }
      else if(Command=="DATE")  Expanded = TDateTime().CurrentDateTime().DateString();
      else if(Command=="BUTTON1") Expanded = " " + Button1Text;
      else if(Command=="BUTTON2") Expanded = " " + Button2Text;
      else if(Command=="BUTTON3") Expanded = " " + Button3Text;
      else if(Command=="BUTTON4") Expanded = " " + Button4Text;
      else if(Command=="BUTTON5") Expanded = " " + Button5Text;
      else if(Command=="BUTTON6") Expanded = " " + Button6Text;
      else if(Command=="BUTTON7") Expanded = " " + Button7Text;
      else if(Command=="BUTTON8") Expanded = " " + Button8Text;
      else if(Command=="BUTTON9") Expanded = " " + Button9Text;
      else if(Command=="BUTTON10") Expanded = " " + Button10Text;
      else if(Command=="BUTTON11") Expanded = " " + Button11Text;
      else if(Command=="BUTTON12") Expanded = " " + Button12Text;
      else if(Command=="OTHER")     Expanded = OtherCall;
      else if(Command=="OTHERNAME") Expanded = OtherName;
      else if(Command=="OTHERQTH")  Expanded = OtherQTH;
      else if(Command=="RST")       Expanded = RST;
      else if(Command=="OTHERRST")  Expanded = OtherRST;
      else if(Command=="NOQSO")   { Expanded = ""; OtherCall = ""; UpdateMenu(); }
      else if(Command=="OFF")     { Expanded = ""; Endtransmission1Click(this); }
      else if(Command=="STATION") { Expanded = "\x2"+CallSign + " " + StationName + "\r" + StationQTH +" ("+StationLocator+")\r"+StationEmail+"\x3"; }
      else if(Command.Length()>0)
      {
        if(Command[1]=='C')  {
           int ch = atoi(Command.SubString(2,Command.Length()-1).c_str());
           if(ch<1 || ch>255) ch=32;
           Expanded = " ";
           Expanded[1] = (char)ch;
        }
      }
      return Expanded;
}

void __fastcall TFormMain::N9Click(TObject *Sender)
{
    SpeedButtonCQClick(this);
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuClearTXbufferClick(TObject *Sender)
{
    EditHell->Text = "";
    SendBuffer = "";
    LastPos=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::IZ8BLYWebsite1Click(TObject *Sender)
{
     WinExec("explorer.exe http://www.geocities.com/iz8bly",SW_SHOWMAXIMIZED);
}

//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonOtherCallClick(TObject *Sender)
{
    if(LogState==false) ToolButtonLogClick(this);
    else if(EditHell->Focused() || RichEdit1->Focused()) EditQRZ->SetFocus();
    else EditHell->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonSend1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbRight) Definebutton1Click(((TButton *)Sender)->Tag);
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::EditHellChange(TObject *Sender)
{
      int CurrLen = EditHell->Text.Length();
      if(CurrLen>LastPos)
      {
          int t;
          for(t=LastPos+1;t<=CurrLen;t++)
          {
             StuffBuff(EditHell->Text[t]);
             LastPos++;
          }
      }
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::Endtransmission1Click(TObject *Sender)
{
     FlushInvoked = true;
     FlushCount = 0;
     EditHell->SetFocus();

     /*
     FlushCount = TX.NSamples;
     TX.SendPostamble();
     FlushCount = TX.NSamples - FlushCount;
     FlushInvoked = true;
     RichEdit1->SetFocus();
     */
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Speed1Click(TObject *Sender)
{
     Endtransmission1Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeFont()
{
   FontDialogTX->Font->Name = TXFontName;
   FontDialogTX->Font->Size = TXFontSize;
   FontDialogTX->Font->Color = TXFontColor;
   if(TXFontBold) FontDialogTX->Font->Style = FontDialogTX->Font->Style << fsBold;
   else FontDialogTX->Font->Style = FontDialogTX->Font->Style >> fsBold;

   FontDialogRX->Font->Name = RXFontName;
   FontDialogRX->Font->Size = RXFontSize;
   FontDialogRX->Font->Color = RXFontColor;
   if(RXFontBold) FontDialogRX->Font->Style = FontDialogRX->Font->Style << fsBold;
   else FontDialogRX->Font->Style = FontDialogRX->Font->Style >> fsBold;

   EditHell->Font = FontDialogTX->Font;
   RichEdit1->Font = FontDialogRX->Font;
   EditHell->Color = TXBGColor;
   RichEdit1->Color = RXBGColor;
}

void __fastcall TFormMain::ChooseRXfont1Click(TObject *Sender)
{
   if(FontDialogRX->Execute())
   {
      RXFontName  = FontDialogRX->Font->Name;
      RXFontSize  = FontDialogRX->Font->Size;
      RXFontBold  = FontDialogRX->Font->Style.Contains(fsBold);
      RXFontColor = FontDialogRX->Font->Color;
      ChangeFont();
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OpenTXfont1Click(TObject *Sender)
{
   if(FontDialogTX->Execute())
   {
      TXFontName  = FontDialogTX->Font->Name;
      TXFontSize  = FontDialogTX->Font->Size;
      TXFontBold  = FontDialogTX->Font->Style.Contains(fsBold);
      TXFontColor = FontDialogTX->Font->Color;
      ChangeFont();
   }
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::LogToFile(AnsiString S)
{
    if(!LogFile) return;
    if(LogHandle<=0)
    {
       if(!FileExists(LogName))
       {
          LogHandle = FileCreate(LogName);
       }
       else
       {
          LogHandle = FileOpen(LogName,fmOpenReadWrite);
          FileSeek(LogHandle,0,2);
       }
    }
    FileWrite(LogHandle,S.c_str(),S.Length());
}

void __fastcall TFormMain::SpeedButtonCQClick(TObject *Sender)
{
/*
    AnsiString p,q;

    p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz----------------------------------------------------------------------------------------------------------------------------------------------------------";
    for(int j=0;j<RX.NInterleavers;j++)
    {
       p = TX.IL[j].EncodeLongString(p);
    }
    q = p;
    for(int j=0;j<RX.NInterleavers;j++)
    {
       q = RX.IL[j].DecodeLongString(q);
    }

    Text = Text+"Encoded: "+p+"\r\n"+"Decoded: "+q+"\r\n";
    SendString(Text);
    */

    AnsiString Text;
    Text = "$CQ $OFF ";
    SendString(Text);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Sendaheadbuffer1Click(TObject *Sender)
{
     int L = SendBuffer.Length();
     if(L<1) return;
     if(SendBuffer[1]=='*')
     {
        SendBuffer = SendBuffer.SubString(2,L-1);
        SendString(" ");
     }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuLogFileClick(TObject *Sender)
{
    MenuLogFile->Checked = !MenuLogFile->Checked;
    LogFile = MenuLogFile->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RichEdit1KeyPress(TObject *Sender, char &Key)
{
     EditHell->SetFocus();
     PostMessage(EditHell->Handle,WM_CHAR,Key,Key);
     Key = 0;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::EditHellKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
   if(Key==VK_DELETE) Key=0;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::EditFreqChange(TObject *Sender)
{
     RX.freq = atof(EditFreq->Text.c_str());
     TX.freq = RX.freq;
     DrawWaterfallScale();
}

void __fastcall TFormMain::UpdateEditFreq()
{
   if(!EditFreq->Focused())
   {
      EditFreq->OnChange = 0;
      EditFreq->Text = FormatFloat("0",RX.freq);
      EditFreq->OnChange = EditFreqChange;
   }
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButtonClearScreenClick(TObject *Sender)
{
    RichEdit1->Text = "";
    EditHell->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RichEdit1MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(Button==mbLeft) Clipboard()->SetTextBuf(RichEdit1->SelText.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SystemMessage(AnsiString S)
{
   S = S + "\r\n";
   int l = RichEdit1->Text.Length();
   if(l>0)
   {
      if(RichEdit1->Text[l]!='\n') S = "\r\n" + S;
   }
   RXPrintString(RichEdit1,S,clBlue);
}


void __fastcall TFormMain::ToolButtonLogClick(TObject *Sender)
{
        if(PanelLog->Visible)
        {
           PanelLog->Visible=false;
           EditHell->SetFocus();
        }
        else
        {
           PanelLog->Visible=true;
        }
        LogState = PanelLog->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuMacro1Click(TObject *Sender)
{
      int t=((TComponent *)Sender)->Tag;

      if(t== 1) ButtonSendClick(ButtonSend1);
      if(t== 2) ButtonSendClick(ButtonSend2);
      if(t== 3) ButtonSendClick(ButtonSend3);
      if(t== 4) ButtonSendClick(ButtonSend4);
      if(t== 5) ButtonSendClick(ButtonSend5);
      if(t== 6) ButtonSendClick(ButtonSend6);
      if(t== 7) ButtonSendClick(ButtonSend7);
      if(t== 8) ButtonSendClick(ButtonSend8);
      if(t== 9) ButtonSendClick(ButtonSend9);
      if(t==10) ButtonSendClick(ButtonSend10);
      if(t==11) ButtonSendClick(ButtonSend11);
      if(t==12) ButtonSendClick(ButtonSend12);
}
void __fastcall TFormMain::ImageHzMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
   //if(RX.drawn) RX.DrawLine();
   //RX.LinePos = Y;
   //RX.DrawLine();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ImageBitShapeDblClick(TObject *Sender)
{
   RX.Clock.Reset();
}

void __fastcall TFormMain::CheckBoxAFCClick(TObject *Sender)
{
    RX.AFC = CheckBoxAFC->Checked;
}


AnsiString FloatToAnsiString(float f)
{
    char s[100];
    sprintf(s,"%f",f);
    return AnsiString(s);
}

unsigned int Hash(AnsiString s)
{
    unsigned int hash = 0xFAC2FAC2;
    for(int t=1;t<=s.Length();t++)
    {
       hash += (hash << 1) * (unsigned int)s[t];
    }
    return hash;
}

//---------------------------------------------------------------------------


/******************** GESTIONE DEL LOG ********************************/

void __fastcall TFormMain::ButtonLogNewEntryClick(TObject *Sender)
{
        if(EditQRZ->Text != "" && ButtonLog->Enabled == true)
        {
           if(Application->MessageBox("Current QSO is not logged. Do you want to clear it?","Log",MB_YESNO | MB_ICONWARNING)!=IDYES) return;
        }

        EditQRZ->Text = "";
        EditName->Text = "";
        EditQTH->Text = "";
        //EditFrequency->Text = "";
        //EditRSTSent->Text = "";
        //EditRSTReceived->Text = "";
        EditComments->Text = "";
        EditQRZ->SetFocus();
        ButtonLog->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonLogClick(TObject *Sender)
{
        if(EditQRZ->Text=="") return;

        int H;
        AnsiString LogName = ThePath + "\\chip64.adi";

        if(FileExists(LogName))
        {
           H = FileOpen(LogName,fmOpenReadWrite);
           if(H<0)
           {
              Application->MessageBox("Cannot write to log","IZ8BLY Chip64",MB_OK | MB_ICONSTOP);
              return;
           }
           FileSeek(H,0,2);
        }
        else
        {
           H = FileCreate(LogName);
           if(H<0)
           {
              Application->MessageBox("Cannot write to log","IZ8BLY Chip64",MB_OK | MB_ICONSTOP);
              return;
           }
           FileWriteString(H,"Created by IZ8BLY Chip64\r\n<EOH>\r\n");
        }

        AnsiString Linea;

        Linea = FormatAdif("CALL",EditQRZ->Text) +
                FormatAdif("NAME",EditName->Text)+
                FormatAdif("QTH",EditQTH->Text)+
                FormatAdif("RST_RCVD",EditRSTReceived->Text)+
                FormatAdif("RST_SENT",EditRSTSent->Text)+
                FormatAdif("FREQ",EditFrequency->Text)+
                FormatAdif("MODE","CHIP64")+
                FormatAdif("QSO_DATE",TDateTime().CurrentDateTime().FormatString("yyyymmdd"))+
                FormatAdif("TIME_ON",TDateTime().CurrentDateTime().FormatString("hhmm"))+
                FormatAdif("COMMENT",EditComments->Text)+
                "<EOR>\r\n";

        FileWriteString(H,Linea);
        FileClose(H);

        char oldclip[2048];
        Clipboard()->GetTextBuf(oldclip,2048);

        Clipboard()->SetTextBuf(Linea.c_str());
        Log32.Message(LOGGER32_CLIENT_LOG_DATA);
        Clipboard()->SetTextBuf(oldclip);

        ButtonLog->Enabled = false;
}

AnsiString FormatAdif(AnsiString FieldName, AnsiString Value)
{
   int L = Value.Length();
   AnsiString out;
   if(L>0) out = FieldName = "<" + FieldName+":"+AnsiString(L) +">"+ Value;
   else out = "";
   return out;
}

void FileWriteString(int H,AnsiString s)
{
    FileWrite(H,s.c_str(),s.Length());
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::EditQRZChange(TObject *Sender)
{
   OtherCall = EditQRZ->Text.Trim();
   Clipboard()->SetTextBuf(OtherCall.c_str());
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::EditNameChange(TObject *Sender)
{
        OtherName = EditName->Text.Trim();
}

void __fastcall TFormMain::EditQTHChange(TObject *Sender)
{
        OtherQTH = EditQTH->Text.Trim();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditRSTSentChange(TObject *Sender)
{
        RST = EditRSTSent->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditRSTReceivedChange(TObject *Sender)
{
        OtherRST = EditRSTReceived->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditQRZDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditQRZ->Text = EditQRZ->Text + AnsiString(buf);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditNameDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditName->Text = EditName->Text + AnsiString(buf);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditQTHDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditQTH->Text = EditQTH->Text + AnsiString(buf);
}

/**********************************************************************/
void __fastcall TFormMain::DrawWaterfallScale()
{
      int band = HWaterfallBand;

      // pulisce il rettangolo
      TRect NewRect = Rect(0,0,ImageScaleWFFT->Width,ImageScaleWFFT->Height);
      if(WaterfallLogScale)
      {
           ImageScaleWFFT->Canvas->Brush->Color = clBlack;
           ImageScaleWFFT->Canvas->Font->Color = clWhite;
           ImageScaleWFFT->Canvas->Pen->Color = clWhite;
      }
      else
      {
           ImageScaleWFFT->Canvas->Brush->Color = (TColor) 0x00D1F6FF; //clWhite;
           ImageScaleWFFT->Canvas->Font->Color = clBlack;
           ImageScaleWFFT->Canvas->Pen->Color = clBlack;
      }
      ImageScaleWFFT->Canvas->FillRect(NewRect);

      ImageScaleWFFT->Canvas->Font->Name = "Small Fonts";
      ImageScaleWFFT->Canvas->Font->Size = 7;

      int ff;
      int t;
      int step,major;
      int separation;

      if(HorizontalWaterfall) separation=(ImageScaleWFFT->Width/ImageScaleWFFT->Canvas->TextWidth("00000"));
      else separation=(ImageScaleWFFT->Height/ImageScaleWFFT->Canvas->TextHeight("0"));
      if(separation<1) return;

      step = band / separation;
           if(step <=  1) return;
      else if(step <=  5) step = 5;
      else if(step <= 10) step = 10;
      else if(step <= 20) step = 20;
      else if(step <= 50) step = 50;
      else if(step <=100) step =100;
      else if(step <=200) step =200;
      else step =500;

      for(ff=0;ff<=band;ff+=step)
      {
         if(HorizontalWaterfall) t = (ImageScaleWFFT->Width*ff)/band;
         else t = ImageScaleWFFT->Height-(ImageScaleWFFT->Height*ff)/band;
         AnsiString fs = AnsiString(HWaterfallStart+(int)ff);
         int th = ImageScaleWFFT->Canvas->TextHeight(fs);
         int tw = ImageScaleWFFT->Canvas->TextWidth(fs);
         if(HorizontalWaterfall)
         {
            ImageScaleWFFT->Canvas->TextOut(t-(tw/2),ImageScaleWFFT->Height-9-th, fs);
            ImageScaleWFFT->Canvas->MoveTo(t,ImageScaleWFFT->Height-8);
            ImageScaleWFFT->Canvas->LineTo(t,ImageScaleWFFT->Height);
         }
         else
         {
            ImageScaleWFFT->Canvas->TextOut(6,t-(th/2), fs);
            ImageScaleWFFT->Canvas->MoveTo(0,t);
            ImageScaleWFFT->Canvas->LineTo(5,t);
         }
      }

      if(HorizontalWaterfall) separation=ImageScaleWFFT->Width/4;
      else separation=ImageScaleWFFT->Height/4;
      if(separation<1) return;

      step = band / separation;
           if(step <=  1) return;
      else if(step <=  5) { step =  5; major =   50; }
      else if(step <= 10) { step = 10; major =   50; }
      else if(step <= 20) { step = 20; major =  100; }
      else if(step <= 50) { step = 50; major =  500; }
      else if(step <=100) { step =100; major =  500; }
      else if(step <=200) { step =200; major = 2000; }
      else { step = 500; major = 2000; }

      for(ff=0;ff<band;ff+=step)
      {
         int fifty;
         if(ff % major == 0 ) fifty=3;
         else fifty = 0;
         if(HorizontalWaterfall)
         {
            t = (ImageScaleWFFT->Width*ff)/band;
            ImageScaleWFFT->Canvas->MoveTo(t,ImageScaleWFFT->Height-3-fifty);
            ImageScaleWFFT->Canvas->LineTo(t,ImageScaleWFFT->Height);
         }
         else
         {
            t = ImageScaleWFFT->Height-(ImageScaleWFFT->Height*ff)/band;
            ImageScaleWFFT->Canvas->MoveTo(0,t);
            ImageScaleWFFT->Canvas->LineTo(2+fifty,t);
         }
      }
}


void __fastcall TFormMain::CheckBoxSquelchClick(TObject *Sender)
{
        Squelch = CheckBoxSquelch->Checked;
}

void __fastcall TFormMain::ImageWFFTMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft && Shift.Contains(ssCtrl))
    {
       WaterfallLogScale = !WaterfallLogScale;
       return;
    }

    if(Button==mbLeft)
    {
      int band=HWaterfallBand;
      if(HorizontalWaterfall) RX.freq=HWaterfallStart+(band*(X+1))/ImageWFFT->Width;
      else RX.freq=HWaterfallStart+(band*(ImageWFFT->Height-Y+1))/ImageWFFT->Height;
      if(RX.freq > 3200) RX.freq = 3200;
      if(RX.freq < 200) RX.freq = 200;
    }
    else if(Button==mbRight)
    {
      RX.freq = CenterQRG;
    }
    EditFreq->Text = RX.freq;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ShowMetric()
{
   if(!FormMain->PanelMetric->Visible) return;

   FormMain->NeedleMetric->Progress = confidence;

   /*
   int mx = FormMain->ImageMetric->Width;
   int my = FormMain->ImageMetric->Height;

   static int last_y;

   int y  = ((metric-64-8) * my / (64-8));
   int sq = ((squelch_thereshold-64-8) * my / (64-8));

   //FormMain->ImageMetric->Canvas->Pen->Color = clBlue;
   //FormMain->ImageMetric->Canvas->MoveTo(mx-1,my);
   //FormMain->ImageMetric->Canvas->LineTo(mx-1,my-y);
   //FormMain->ImageMetric->Canvas->Pen->Color = clWhite;
   //FormMain->ImageMetric->Canvas->LineTo(mx-1,0);
   //BitBlt(FormMain->ImageMetric->Canvas->Handle,0,0,mx,my,FormMain->ImageMetric->Canvas->Handle,1,0,SRCCOPY);

   BitBlt(FormMain->ImageMetric->Canvas->Handle,0,0,mx,my,FormMain->ImageMetric->Canvas->Handle,3,0,SRCCOPY);

   TRect NewRect = Rect(mx-3, 0, mx, my);
   FormMain->ImageMetric->Canvas->Brush->Color = clWhite;
   FormMain->ImageMetric->Canvas->FillRect(NewRect);
   FormMain->ImageMetric->Canvas->Pen->Color = clBlue;
   FormMain->ImageMetric->Canvas->MoveTo(mx-4,my-last_y);
   FormMain->ImageMetric->Canvas->LineTo(mx-1,my-y);

   SetPixel(FormMain->ImageMetric->Canvas->Handle,mx-3,my-sq,clRed);
   SetPixel(FormMain->ImageMetric->Canvas->Handle,mx-2,my-sq,clRed);
   SetPixel(FormMain->ImageMetric->Canvas->Handle,mx-1,my-sq,clRed);

   last_y = y;

   FormMain->ImageMetric->ControlStyle = FormMain->ImageMetric->ControlStyle << csOpaque;
   FormMain->ImageMetric->Invalidate();
   */
}


void __fastcall TFormMain::MenuViewWFFTClick(TObject *Sender)
{
        MenuViewWFFT->Checked = !MenuViewWFFT->Checked;
        HorizontalWaterfall = MenuViewWFFT->Checked;
        FormResize(this);
}

void __fastcall TFormMain::MenuViewScaleClick(TObject *Sender)
{
    MenuViewScale->Checked = !MenuViewScale->Checked;
    ImageScaleWFFT->Visible = MenuViewScale->Checked;
    FrequencyScale = MenuViewScale->Checked;
}

void __fastcall TFormMain::SplitterWaterfallMoved(TObject *Sender)
{
    if(HorizontalWaterfall) WaterfallSize=PanelWFFT->Height;
    else WaterfallSize=PanelWFFT->Width;

    Resize();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Splitter3Moved(TObject *Sender)
{
   Resize();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButtonCQMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbRight) Definebutton1Click(((TButton *)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SetWaterfallPosition()
{
   if(HorizontalWaterfall)
   {
      PanelWFFT->Align = alBottom;
      PanelWFFT->Height = WaterfallSize;
      ImageScaleWFFT->Align = alTop;
      ImageScaleWFFT->Height = 19;
      SplitterWaterfall->Align = alBottom;
      ImageWFFT->Cursor = crUpArrow;
   }
   else
   {
      PanelWFFT->Align = alRight;
      PanelWFFT->Width = WaterfallSize;
      ImageScaleWFFT->Align = alRight;
      ImageScaleWFFT->Width = 32;
      SplitterWaterfall->Align = alRight;
      ImageWFFT->Cursor = (TCursor) crCursorWaterfall;
   }

   ImageCorrelation->Height = CorreloscopeSize;
}

void __fastcall TFormMain::StartTransmit()
{
    TX.PrepareTX();
    TX.SendPreamble();
    PTT.On();
    RadioState = tx;

    UpdateMenu();

    // pulisce la finestra
    PhaseScope1->Ampl=0;
    PhaseScope1->Phase=0;
}

void __fastcall TFormMain::StopTransmit()
{
    PTT.Off();
    RadioState = rx;
    SendBuffer = "";
    UpdateMenu();
    RX.Clock.Reset();
}

void __fastcall TFormMain::Splitter1Moved(TObject *Sender)
{
    TransmitBoxSize = EditHell->Height;
    Resize();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::SplitterCorreloscopeMoved(TObject *Sender)
{
    CorreloscopeSize=ImageCorrelation->Height;
    Resize();
}

// this is the final code generator

/*
void __fastcall TFormMain::Button3Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator64(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[32];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<128;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[32]<0) s->Add("       neg ebx");

         for(int j=1;j<32;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+32]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator64_IntegerMath.cpp");
}
*/

/*
// 64x64 one m-seq
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator64_1(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[32];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<64;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[32]<0) s->Add("       neg ebx");

         for(int j=1;j<32;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+32]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator64_1_IntegerMath.cpp");
}
*/

/*
// 128 normale, 2 registri
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator128(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[64];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<256;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[64]<0) s->Add("       neg ebx");

         for(int j=1;j<64;j++)
         {
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+64]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator128_IntegerMath.cpp");
}
*/

/*
// 128 ultima, 2 registri, split a 128
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator128(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[64];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<256;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[64]<0) s->Add("       neg ebx");

         for(int j=1;j<64;j++)
         {
             if(j==32) s->Add("       add eax, 128");
             if(j==32) s->Add("       add edx, 128");

             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4 % 128)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4 % 128)+"]");
             if(RX.PnSeq[t].chip[j+64]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4 % 128)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4 % 128)+"]");
         }
         s->Add("    ");
         s->Add("       add  ecx, ebx     ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator128_IntegerMath.cpp");
}
*/



/*
// 128 con esi, edi
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator128(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[42];                 ");
     s->Add("    int *ptr2 = &_rxseq[84];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<256;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("       push esi                             ");
         s->Add("       push edi                             ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("       mov edi, ptr2                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("       mov esi, [edi]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[42]<0) s->Add("       neg ebx");
         if(RX.PnSeq[t].chip[84]<0) s->Add("       neg esi");

         for(int j=1;j<42;j++)
         {
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");

             if(RX.PnSeq[t].chip[j+42]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");

             if(RX.PnSeq[t].chip[j+84]>0) s->Add("       add esi, [edi+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub esi, [edi+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       add  correl, esi  ");
         s->Add("       pop  edi          ");
         s->Add("       pop  esi          ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator128_IntegerMath.cpp");
}
*/


/*
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator32(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[16];                 ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<64;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)  s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[16]<0) s->Add("       neg ebx");

         for(int j=1;j<16;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+16]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                         s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator32_IntegerMath.cpp");
}
*/

/*
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator16(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[8];                  ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<32;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0) s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[8]<0) s->Add("       neg ebx");

         for(int j=1;j<8;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+8]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                        s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator16_IntegerMath.cpp");
}
*/

/*
// 16x16 short version (1 mseq)
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator16(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[8];                  ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<16;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0) s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[8]<0) s->Add("       neg ebx");

         for(int j=1;j<8;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+8]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                        s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator16_IntegerMath.cpp");
}
*//*
// 256x256 1 mseq
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
     TStringList *s = new TStringList;

     s->Add("void Receiver::RunCorrelator256(int &maxcorrel, int &maxidx, bool &polarity)");
     s->Add("{                                                                           ");
     s->Add("    maxcorrel = 0;                                                          ");
     s->Add("    maxidx    = 0;                                                          ");
     s->Add("    polarity  = false;                                                      ");
     s->Add("");
     s->Add("    int *ptr0 = &_rxseq[0];                  ");
     s->Add("    int *ptr1 = &_rxseq[128];                ");
     s->Add("    int correl;                              ");
     s->Add("");

     for(int t=0;t<256;t++)
     {
         s->Add("    asm                                     ");
         s->Add("    {                                       ");
         s->Add("       push bx                              ");
         s->Add("                                            ");
         s->Add("       mov eax, ptr0                        ");
         s->Add("       mov edx, ptr1                        ");
         s->Add("                                            ");
         s->Add("       mov ecx, [eax]                       ");
         s->Add("       mov ebx, [edx]                       ");
         s->Add("                                            ");

         if(RX.PnSeq[t].chip[0]<0)   s->Add("       neg ecx");
         if(RX.PnSeq[t].chip[128]<0) s->Add("       neg ebx");

         for(int j=1;j<128;j++)
         {
             AnsiString sign;
             if(RX.PnSeq[t].chip[j]>0) s->Add("       add ecx, [eax+"+AnsiString(j*4)+"]");
             else                      s->Add("       sub ecx, [eax+"+AnsiString(j*4)+"]");
             if(RX.PnSeq[t].chip[j+128]>0) s->Add("       add ebx, [edx+"+AnsiString(j*4)+"]");
             else                          s->Add("       sub ebx, [edx+"+AnsiString(j*4)+"]");
         }
         s->Add("    ");
         s->Add("       mov  correl, ecx  ");
         s->Add("       add  correl, ebx  ");
         s->Add("       pop  bx           ");
         s->Add("    }                              ");
         s->Add("");
         s->Add("    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx="+AnsiString(t)+";  }");
         s->Add("    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-"+AnsiString(t)+"; }");
     }
     s->Add("    if(maxidx<0) { maxidx=-maxidx; polarity=true; }");

     s->Add("}");

     s->SaveToFile("c:\\documenti\\c++\\dsss\\Correlator256_IntegerMath.cpp");
}
*/

void __fastcall TFormMain::SliderRXFilterChange(TObject *Sender)
{
    AnsiString FN;
         if(SliderRXFilter->Position==0) FN = "very_narrow.fir";
    else if(SliderRXFilter->Position==1) FN = "narrow.fir";
    else if(SliderRXFilter->Position==2) FN = "normal.fir";
    String ThePath = ExtractFilePath(Application->ExeName);
    RX.QF.Load(ThePath+"/Filters/"+FN);
}

//---------------------------------------------------------------------------


void __fastcall TFormMain::MenuChip64Click(TObject *Sender)
{
    // With 64x64 Walsh Matrix and two m-sequences
    Sequence Mseq0; Mseq0.MSeq(6,POLY65,1);    Mseq0.ZeroPad();
    Sequence Mseq1; Mseq1.MSeq(6,POLY6521,1);  Mseq1.ZeroPad();

    RX.nbits  = 8;   TX.nbits  = RX.nbits;
    RX.nwalsh = 64;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh*2];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq1); j++;
    }

    /*
    // With 64x64 Walsh Matrix and one m-sequence
    Sequence Mseq0; Mseq0.MSeq(6,POLY65,1);    Mseq0.ZeroPad();

    RX.nbits  = 7;   TX.nbits  = RX.nbits;
    RX.nwalsh = 64;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
    }
    */

    RX.SetPnSeq();
    TX.SetPnSeq();

    MenuChip16->Checked = false;
    MenuChip32->Checked = false;
    MenuChip64->Checked = true;
    MenuChip128->Checked = false;
    StatusBar1->Panels->Items[3]->Text = "Chip-64";
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuChip128Click(TObject *Sender)
{
    // With 128x128 Walsh Matrix
    Sequence Mseq0; Mseq0.MSeq(7,POLY73,1);    Mseq0.ZeroPad();
    Sequence Mseq1; Mseq1.MSeq(7,POLY7321,1);  Mseq1.ZeroPad();

    RX.nbits  = 9;    TX.nbits  = RX.nbits;
    RX.nwalsh = 128;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh*2];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq1); j++;
    }

    RX.SetPnSeq();
    TX.SetPnSeq();

    MenuChip16->Checked = false;
    MenuChip32->Checked = false;
    MenuChip64->Checked = false;
    MenuChip128->Checked = true;
    StatusBar1->Panels->Items[3]->Text = "Chip-128";
}

void __fastcall TFormMain::MenuChip32Click(TObject *Sender)
{
    // With 32x32 Walsh Matrix
    Sequence Mseq0; Mseq0.MSeq(5,POLY53,1);    Mseq0.ZeroPad();
    Sequence Mseq1; Mseq1.MSeq(5,POLY5421,1);  Mseq1.ZeroPad();

    RX.nbits  = 7;   TX.nbits  = RX.nbits;
    RX.nwalsh = 32;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh*2];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq1); j++;
    }

    RX.SetPnSeq();
    TX.SetPnSeq();

    MenuChip16->Checked = false;
    MenuChip32->Checked = true;
    MenuChip64->Checked = false;
    MenuChip128->Checked = false;
    StatusBar1->Panels->Items[3]->Text = "Chip-32";
}

void __fastcall TFormMain::MenuChip16Click(TObject *Sender)
{
    /*
    // With 16x16 Walsh Matrix
    Sequence Mseq0; Mseq0.MSeq(4,POLY41,1);  Mseq0.ZeroPad();
    Sequence Mseq1; Mseq1.MSeq(4,POLY43,1);  Mseq1.ZeroPad();

    RX.nbits  = 6;   TX.nbits  = RX.nbits;
    RX.nwalsh = 16;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh*2];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq1); j++;
    }

    RX.SetPnSeq();
    TX.SetPnSeq();
    */

    // With 16x16 Walsh Matrix
    Sequence Mseq0; Mseq0.MSeq(4,POLY41,1);  Mseq0.ZeroPad();

    RX.nbits  = 5;   TX.nbits  = RX.nbits;
    RX.nwalsh = 16;  TX.nwalsh = RX.nwalsh;

    if(RX.PnSeq) delete [] RX.PnSeq;

    RX.PnSeq = new Sequence[RX.nwalsh];
    TX.PnSeq = RX.PnSeq;

    int j=0;
    for(int t=0;t<RX.nwalsh;t++)
    {
       RX.PnSeq[j].Walsh(RX.nwalsh,t); RX.PnSeq[j].Convolve(Mseq0); j++;
    }

    RX.SetPnSeq();
    TX.SetPnSeq();

    MenuChip16->Checked = true;
    MenuChip32->Checked = false;
    MenuChip64->Checked = false;
    MenuChip128->Checked = false;
    StatusBar1->Panels->Items[3]->Text = "Chip-16";
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuUnclockedClick(TObject *Sender)
{
    RX.Clocked = false;
    RX.SetPnSeq();
    MenuUnclocked->Checked = true;
    MenuClocked->Checked = false;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuClockedClick(TObject *Sender)
{
    RX.Clocked = true;
    RX.SetPnSeq();
    MenuUnclocked->Checked = false;
    MenuClocked->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ImageCorrelationMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
/*
    if(Button==mbLeft)
    {
      int band=21*64;
      int pos = (band*X)/ImageCorrelation->Width;
      RX.Clock.last_peak_pos = pos;
    }
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuFixHyperthreadingClick(TObject *Sender)
{
    RX.IntegerMath = !RX.IntegerMath;
    MenuFixHyperthreading->Checked = !RX.IntegerMath;
}
//---------------------------------------------------------------------------

