#ifndef Logger32H
#define Logger32H

#define LOGGER32_LOGGER32_START      1
#define LOGGER32_LOGGER32_END        2
#define LOGGER32_CLIENT_START        3
#define LOGGER32_CLIENT_END          4
#define LOGGER32_CLIENT_CLOSE_RQ     5
#define LOGGER32_CLIENT_PTT_LOGGER   6
#define LOGGER32_CLIENT_PTT_CLIENT   7
#define LOGGER32_CLIENT_PTT_ON       8
#define LOGGER32_CLIENT_PTT_OFF      9
#define LOGGER32_CLIENT_LOG_DATA     10

class Logger32
{
private:
   int Logger32Msg;
   int MainWindowHandle;

public:
   AnsiString Logger32Program;
   bool Logger32Load;
   bool Logger32Close;
   bool Logger32ClientOnTop;

   Logger32();
   ~Logger32();
   void SetMainWindowHandle(int handle);
   void StartLogger(AnsiString Logger32Exe);
   void Message(int msg);
};

#endif
