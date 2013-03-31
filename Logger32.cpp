//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Logger32.h"

Logger32::Logger32()
{
   Logger32Msg = RegisterWindowMessage("LOGGER32");
   Message(LOGGER32_CLIENT_START);
}

Logger32::~Logger32()
{
   if(Logger32Close) Message(LOGGER32_CLIENT_CLOSE_RQ);
   Message(LOGGER32_CLIENT_END);
}

void Logger32::SetMainWindowHandle(int handle)
{
   MainWindowHandle = handle;
   if(Logger32Load) StartLogger(Logger32Program);
}

void Logger32::Message(int msg)
{
   SendMessage(HWND_BROADCAST,Logger32Msg,msg,MainWindowHandle);
}

void Logger32::StartLogger(AnsiString Logger32Exe)
{
    AnsiString LoggerPath = ExtractFilePath(Logger32Exe);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si,0,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_SHOWNA;

    // WinExec(Logger32Program.c_str(),SW_SHOWNA);

    if(CreateProcess( Logger32Exe.c_str(),   // pointer to name of executable module
                   NULL,                     // pointer to command line string
                   NULL,                     // pointer to process security attributes
                   NULL,                     // pointer to thread security attributes
                   false,                    // handle inheritance flag
                   0,                        // creation flags
                   NULL,                     // pointer to new environment block
                   LoggerPath.c_str(),       // pointer to current directory name
                   &si,                      // pointer to STARTUPINFO
                   &pi))                     // pointer to PROCESS_INFORMATION
    {
        WaitForInputIdle(pi.hProcess,1000);
    }

    Message(LOGGER32_CLIENT_START);
}

