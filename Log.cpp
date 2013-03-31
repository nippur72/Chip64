//---------------------------------------------------------------------------
#include <vcl.h>
#include <clipbrd.hpp>
#pragma hdrstop

#include "Log.h"
#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "Campo"
#pragma link "Input"
#pragma resource "*.dfm"

TFormLog *FormLog;

extern AnsiString ThePath;
extern AnsiString PendingCall;
extern AnsiString OtherCall;
extern AnsiString OtherName;
extern AnsiString OtherQTH;
extern AnsiString OtherRST;
extern AnsiString RST;

extern bool UTCTimeLog;

void FileWriteString(int H,AnsiString s);
AnsiString FormatAdif(AnsiString FieldName, AnsiString Value);

extern int IZ8BLY;

//---------------------------------------------------------------------------
__fastcall TFormLog::TFormLog(TComponent* Owner): TForm(Owner)
{
     IZ8BLY = RegisterWindowMessage("IZ8BLY");
}

//---------------------------------------------------------------------------

void __fastcall TFormLog::Button2Click(TObject *Sender)
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
void __fastcall TFormLog::ButtonLogClick(TObject *Sender)
{
        if(EditQRZ->Text=="") return;

        int H;
        AnsiString LogName = ThePath + "\\stream.adi";

        if(FileExists(LogName))
        {
           H = FileOpen(LogName,fmOpenReadWrite);
           if(H<0)
           {
              Application->MessageBox("Cannot write to log","IZ8BLY PSK31 Lab",MB_OK | MB_ICONSTOP);
              return;
           }
           FileSeek(H,0,2);
        }
        else
        {
           H = FileCreate(LogName);
           if(H<0)
           {
              Application->MessageBox("Cannot write to log","IZ8BLY PSK31 Lab",MB_OK | MB_ICONSTOP);
              return;
           }
           FileWriteString(H,"Created by IZ8BLY PSK31 Lab\r\n<EOH>\r\n");
        }

        AnsiString Linea;

        TDateTime TD;
        if(UTCTimeLog)
        {
           SYSTEMTIME SystemTime;
           GetSystemTime(&SystemTime);
           TD = SystemTimeToDateTime(SystemTime);
        }
        else
        {
           TD = TDateTime().CurrentDateTime();
        }

        Linea = FormatAdif("CALL",EditQRZ->Text) +
                FormatAdif("NAME",EditName->Text)+
                FormatAdif("QTH",EditQTH->Text)+
                FormatAdif("RST_RCVD",EditRSTReceived->Text)+
                FormatAdif("RST_SENT",EditRSTSent->Text)+
                FormatAdif("FREQ",EditFrequency->Text)+
                FormatAdif("MODE","STREAM")+
                FormatAdif("QSO_DATE",TD.FormatString("yyyymmdd"))+
                FormatAdif("TIME_ON",TD.FormatString("hhmm"))+
                FormatAdif("COMMENT",EditComments->Text)+
                "<EOR>\r\n";

        FileWriteString(H,Linea);
        FileClose(H);

        char oldclip[2048];
        Clipboard()->GetTextBuf(oldclip,2048);

        Clipboard()->SetTextBuf(Linea.c_str());
        SendMessage(HWND_BROADCAST,IZ8BLY,0,0);
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

void __fastcall TFormLog::FormShow(TObject *Sender)
{
        EditQRZ->SetFocus();
}

//---------------------------------------------------------------------------

void __fastcall TFormLog::EditQRZChange(TObject *Sender)
{
        if(EditQRZ->Text=="*") EditQRZ->Text=PendingCall;
        OtherCall = EditQRZ->Text;
        Clipboard()->SetTextBuf(OtherCall.c_str());
}

//---------------------------------------------------------------------------
void __fastcall TFormLog::EditNameChange(TObject *Sender)
{
        OtherName = EditName->Text;
}


void __fastcall TFormLog::FormClose(TObject *Sender, TCloseAction &Action)
{
      Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditQTHChange(TObject *Sender)
{
        OtherQTH = EditQTH->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditRSTSentChange(TObject *Sender)
{
        RST = EditRSTSent->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditRSTReceivedChange(TObject *Sender)
{
        OtherRST = EditRSTReceived->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditQRZDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditQRZ->Text = EditQRZ->Text + AnsiString(buf);
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditNameDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditName->Text = EditName->Text + AnsiString(buf);
}
//---------------------------------------------------------------------------

void __fastcall TFormLog::EditQTHDblClick(TObject *Sender)
{
        char buf[20];
        Clipboard()->GetTextBuf(buf,20);
        EditQTH->Text = EditQTH->Text + AnsiString(buf);
}
//---------------------------------------------------------------------------


