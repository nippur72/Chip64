//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

USEFORM("About.cpp", FormAbout);
USEFORM("DefineButton.cpp", FormDefineButton);
USEFORM("Preferences.cpp", FormSetup);
USEFORM("Unit1.cpp", FormMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFormMain), &FormMain);
                 Application->CreateForm(__classid(TFormAbout), &FormAbout);
                 Application->CreateForm(__classid(TFormDefineButton), &FormDefineButton);
                 Application->CreateForm(__classid(TFormSetup), &FormSetup);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------

