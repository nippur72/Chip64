//---------------------------------------------------------------------------

#ifndef SoundCardH
#define SoundCardH

#include <vcl.h>
#include <mmsystem.h>

#define RXSIZE        2100
#define TXSIZE        2100
#define MAXINBUFFERS  8
#define MAXOUTBUFFERS 8

class SoundCard
{
public:
    int InSoundCard;
    HWAVEIN InHandleDevice;    // handle of wave in device
    int InBufferCount;         // Number of in buffers that are pendent
    bool InCloseInvoked;       // Wave in stop procedure invoked
    int InSampleRate;          // Samplerate of soundcard

    int OutSoundCard;
    HWAVEOUT OutHandleDevice;  // handle of wave out device
    int OutBufferCount;        // number of pending out blocks
    bool OutCloseInvoked;      // Wave out stop procedure invoked
    int OutSampleRate;         // Samplerate of soundcard

    bool DumpToFile;           // write raw samples to file

    SoundCard();
    void StartWaveIn();
    void StopWaveIn();
    void CreateInBuffer();
    void waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    void StartWaveOut();
    void StopWaveOut();
    void CreateOutBuffer();
    void waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    void (*DecodeAudio)(signed short *data, int size);
    void (*EncodeAudio)(signed short *data, int size);

    void WriteWavHeader(int fh);
};


//---------------------------------------------------------------------------
#endif
