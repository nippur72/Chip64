//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#pragma hdrstop

#include "Options.h"
#include "Unit1.h"

Options::Options()
{
   Num = 0;
   Config = new TStringList;
}

Options::~Options()
{
   Num = 0;
   delete Config;
}


void Options::Add(AnsiString Nome,int Tipo,AnsiString Default,void *VarPtr)
{
    Opzioni[Num].Nome    = Nome;
    Opzioni[Num].Tipo    = Tipo;
    Opzioni[Num].VarPtr  = VarPtr;
    Opzioni[Num].Default = Default;
    Num++;
}

void Options::Load()
{
    int *int_ptr;
    bool *bool_ptr;
    AnsiString *string_ptr;
    double *double_ptr;
    float *float_ptr;
    AnsiString Dummy;
    int x,L;

    if(FileExists(ConfigName)) Config->LoadFromFile(ConfigName);

    for(int t=0;t<Num;t++)
    {
       Dummy = Config->Values[Opzioni[t].Nome];
       if(Dummy=="") Dummy = Opzioni[t].Default;

       switch(Opzioni[t].Tipo)
       {
          case OPT_INT:
               int_ptr = (int *)Opzioni[t].VarPtr;
               *int_ptr = atoi(Dummy.c_str());
               break;

          case OPT_BOOL:
               bool_ptr = (bool *)Opzioni[t].VarPtr;
               *bool_ptr = atob(Dummy.c_str());
               break;

          case OPT_STRING:
               while(x = Dummy.AnsiPos("\\r\\n"))
               {
                  L = Dummy.Length();
                  Dummy = Dummy.SubString(1,x-1)+AnsiString("\r\n")+Dummy.SubString(x+4,L);
               }

               string_ptr = (AnsiString *)Opzioni[t].VarPtr;
               *string_ptr = Dummy;
               break;

          case OPT_DOUBLE:
               double_ptr = (double *)Opzioni[t].VarPtr;
               *double_ptr = Dummy.ToDouble();
               break;

          case OPT_FLOAT:
               float_ptr = (float *)Opzioni[t].VarPtr;
               *float_ptr = atof(Dummy.c_str()); //(float) Dummy.ToDouble();
               break;
       }
    }
}


void Options::Save()
{
    int *int_ptr;
    bool *bool_ptr;
    AnsiString *string_ptr;
    double *double_ptr;
    float *float_ptr;

    int x,L;
    AnsiString Dummy;

    for(int t=0;t<Num;t++)
    {
       switch(Opzioni[t].Tipo)
       {
          case OPT_INT:
               int_ptr = (int *)Opzioni[t].VarPtr;
               Config->Values[Opzioni[t].Nome] = *int_ptr;
               break;

          case OPT_BOOL:
               bool_ptr = (bool *)Opzioni[t].VarPtr;
               Config->Values[Opzioni[t].Nome] = btoa(*bool_ptr);
               break;

          case OPT_STRING:
               string_ptr = (AnsiString *)Opzioni[t].VarPtr;
               Dummy = *string_ptr;
               while(x = Dummy.AnsiPos("\r\n"))
               {
                  L = Dummy.Length();
                  Dummy = Dummy.SubString(1,x-1)+"\\r\\n"+Dummy.SubString(x+2,L);
               }
               Config->Values[Opzioni[t].Nome] = Dummy;
               break;

          case OPT_DOUBLE:
               double_ptr = (double *)Opzioni[t].VarPtr;
               Config->Values[Opzioni[t].Nome] = *double_ptr;
               break;

          case OPT_FLOAT:
               float_ptr = (float *)Opzioni[t].VarPtr;
               Config->Values[Opzioni[t].Nome] = FloatToAnsiString(*float_ptr);
               break;
       }
    }
    Config->SaveToFile(ConfigName);
}

AnsiString btoa(bool x)
{
    if(x) return AnsiString("on");
    else return AnsiString("off");
}

bool atob(AnsiString x)
{
    if(x=="on") return true;
    else return false;
}



