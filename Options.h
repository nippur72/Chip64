//---------------------------------------------------------------------------
#ifndef OptionsH
#define OptionsH

#define OPT_INT    0
#define OPT_BOOL   1
#define OPT_STRING 2
#define OPT_DOUBLE 3
#define OPT_FLOAT  4

struct Option
{
   AnsiString Nome;
   int Tipo;
   void *VarPtr;
   AnsiString Default;
};

class Options
{
public:
     TStringList *Config;
     AnsiString ConfigName;
     struct Option Opzioni[100];
     int Num;

     Options();
     ~Options();
     void Add(AnsiString Nome,int Tipo,AnsiString Default, void *VarPtr);
     void Load();
     void Save();
};

AnsiString btoa(bool x);  // on/off bool to ascii
bool atob(AnsiString x);   // on/off ascii to bool

//---------------------------------------------------------------------------
#endif
