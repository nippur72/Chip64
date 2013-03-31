//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PTT.h"
#include "Logger32.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern Logger32 Log32;

void PTTClass::SetPort(int Port)
{
   Close();
   CurrentPort = Port;
}

void PTTClass::Open()
{
    AnsiString Port;

    switch(CurrentPort)
    {
       case  0 : return;
       case  1 : Port = "COM1"; break;
       case  2 : Port = "COM2"; break;
       case  3 : Port = "COM3"; break;
       case  4 : Port = "COM4"; break;
       case  5 : Port = "COM5"; break;
       case  6 : Port = "COM6"; break;
       case  7 : Port = "COM7"; break;
       case  8 : Port = "COM8"; break;
       case  9 : Port = "COM9"; break;
       case 10 : Log32.Message(LOGGER32_CLIENT_PTT_LOGGER); return;
    }

    hCom = CreateFile (
        Port.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // comm devices must be opened w/exclusive-access
        NULL, // no security attrs
        OPEN_EXISTING, // comm devices must use OPEN_EXISTING
        0,    // not overlapped I/O
        NULL  // hTemplate must be NULL for comm devices */
    );

    /* handle error */
    if(hCom == INVALID_HANDLE_VALUE)
    {
        AnsiString Msg = AnsiString("Cannot open ") + Port;
        Application->MessageBox(Msg.c_str(),"COM Port",MB_OK | MB_ICONSTOP);
        return;
    }

    GetCommState(hCom,&dcb);
    dcb.BaudRate = 1200;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fDtrControl = 0;
    dcb.fRtsControl = 0;
    SetCommState(hCom, &dcb);

    // tell Logger32 I have control over PTT
    Log32.Message(LOGGER32_CLIENT_PTT_CLIENT);
}

void PTTClass::Close()
{
    if(CurrentPort==0 || CurrentPort==10) return;
    if(hCom!=INVALID_HANDLE_VALUE) CloseHandle(hCom);
    hCom = INVALID_HANDLE_VALUE;
}

void PTTClass::On()
{
  if(CurrentPort==0)
  {
     return;
  }
  else if(CurrentPort==10)
  {
     Log32.Message(LOGGER32_CLIENT_PTT_ON);
  }
  else
  {
     dcb.fRtsControl = 2;
     dcb.fDtrControl = 2;
     SetCommState(hCom, &dcb);
  }
}

void PTTClass::Off()
{
  if(CurrentPort==0)
  {
     return;
  }
  else if(CurrentPort==10)
  {
     Log32.Message(LOGGER32_CLIENT_PTT_OFF);
  }
  else
  {
     dcb.fRtsControl = 0;
     dcb.fDtrControl = 0;
     SetCommState(hCom, &dcb);
  }
}

