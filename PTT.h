//---------------------------------------------------------------------------
#ifndef PTTH
#define PTTH

class PTTClass
{
public:
   int CurrentPort;  // 0-none, com1, com2...
   HANDLE hCom;      // handle og communication port
   DCB dcb;          //

   void SetPort(int port);
   void Open();
   void Close();
   void On();
   void Off();
};

//---------------------------------------------------------------------------
#endif
