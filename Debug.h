#ifndef DebugH
#define DebugH

#include <vcl.h>

class Debug
{
public:
    int ntimes;
    LARGE_INTEGER FrequencyCounter;
    LARGE_INTEGER accumulated_counter;
    LARGE_INTEGER count;
    float elapsed_msec;
    bool debug_on_exit;

    Debug();
    ~Debug();
    void Start();
    void End();
};

#endif

