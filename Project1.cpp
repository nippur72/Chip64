//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

USERES("Project1.res");
USERES("ResourceFile.res");
USEFORM("About.cpp", FormAbout);
USEFORM("DefineButton.cpp", FormDefineButton);
USEFORM("Preferences.cpp", FormSetup);
USEFORM("UnitFormPaste.cpp", FormPaste);
USEFORM("Unit1.cpp", FormMain);
USEUNIT("PTT.cpp");
USEUNIT("Options.cpp");
USEUNIT("PSKDecoder.cpp");
USEUNIT("Decimator.cpp");
USEUNIT("GoodFFT.cpp");
USEUNIT("PSKTransmitter.cpp");
USEUNIT("ComplexFIR.cpp");
USEUNIT("VITERBI.cpp");
USEUNIT("Interleaver.cpp");
USEUNIT("Varicode.cpp");
USEUNIT("Palette.cpp");
USEUNIT("CW.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "IZ8BLY Stream";
        Application->CreateForm(__classid(TFormMain), &FormMain);
        Application->CreateForm(__classid(TFormAbout), &FormAbout);
        Application->CreateForm(__classid(TFormDefineButton), &FormDefineButton);
        Application->CreateForm(__classid(TFormSetup), &FormSetup);
        Application->CreateForm(__classid(TFormPaste), &FormPaste);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------

