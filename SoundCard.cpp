#pragma hdrstop

#include "SoundCard.h"

SoundCard SC;

void CALLBACK waveInProcCallBack(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
    SC.waveInProc(hwi,uMsg,dwInstance,dwParam1,dwParam2 );
}

void CALLBACK waveOutProcCallBack(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
    SC.waveOutProc(hwo,uMsg,dwInstance,dwParam1,dwParam2);
}

SoundCard::SoundCard()
{
    InSoundCard  = 0;
    OutSoundCard = 0;

    InHandleDevice  = 0;
    OutHandleDevice = 0;

    InCloseInvoked  = false;
    OutCloseInvoked = false;

    DecodeAudio = 0;
    EncodeAudio = 0;
}

void SoundCard::StartWaveIn()
{
    if(InHandleDevice) return;

    // prepares the format for recording
    WAVEFORMATEX formato;
    formato.wFormatTag      = WAVE_FORMAT_PCM;
    formato.nChannels       = 1;
    formato.nSamplesPerSec  = InSampleRate;
    formato.nAvgBytesPerSec = InSampleRate*2;
    formato.nBlockAlign     = 2;
    formato.wBitsPerSample  = 16;
    formato.cbSize          = 0;

    // opens the device input
    MMRESULT risp = waveInOpen(&InHandleDevice,InSoundCard,&formato,(DWORD)waveInProcCallBack,0,CALLBACK_FUNCTION);
    if(risp)
    {
       AnsiString Dummy = AnsiString(risp);
            if(risp==MMSYSERR_ALLOCATED   ) Dummy = "MMSYSERR_ALLOCATED";
       else if(risp==MMSYSERR_BADDEVICEID ) Dummy = "MMSYSERR_BADDEVICEID";
       else if(risp==MMSYSERR_NODRIVER    ) Dummy = "MMSYSERR_NODRIVER";
       else if(risp==MMSYSERR_NOMEM       ) Dummy = "MMSYSERR_NOMEM";
       else if(risp==WAVERR_BADFORMAT     ) Dummy = "WAVERR_BADFORMAT";
       Dummy = AnsiString("Can't open input audio device #")+AnsiString(InSoundCard)+". Error code="+Dummy;
       Application->MessageBox(Dummy.c_str(),"Error opening soundcard",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    // send 10 buffers to the device so if there are other
    // windows background operations audio recording isnt affected
    InBufferCount=0;
    for(int t=0;t<MAXINBUFFERS;t++)
    {
        CreateInBuffer();
    }

    // start recording audio
    if(waveInStart(InHandleDevice))
    {
       Application->MessageBox("Error starting recording","",MB_OK | MB_ICONEXCLAMATION);
       return;
    }
}

void SoundCard::StopWaveIn()
{
    if(InHandleDevice==0) return;
    InCloseInvoked = true;
}

void SoundCard::CreateInBuffer()
{
    // create an empty buffer
    WAVEHDR *Header = new WAVEHDR;
    Header->lpData = (char *) new signed short[RXSIZE];
    Header->dwBufferLength = RXSIZE*2;
    Header->dwBytesRecorded = 0;
    Header->dwUser = 0;
    Header->dwFlags = 0;
    Header->dwLoops = 0;

    // prepare it for recording
    if(waveInPrepareHeader(InHandleDevice,Header,sizeof(WAVEHDR)))
    {
       Application->MessageBox("Error preparing audio buffer","",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    // send it to the sound card so it can be filled
    if(waveInAddBuffer(InHandleDevice,Header,sizeof(WAVEHDR)))
    {
       Application->MessageBox("Error sending audio buffer to the device","",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    // keep track of how many buffers are pending
    InBufferCount++;
}

void SoundCard::waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
    switch(uMsg)
    {
        case MM_WIM_OPEN:
           InCloseInvoked = false;
           break;

        case MM_WIM_CLOSE:
           InHandleDevice = 0;
           break;

        case MM_WIM_DATA:
           if(!InCloseInvoked) CreateInBuffer();

           // process the received buffer
           WAVEHDR *H = (WAVEHDR *)dwParam1;
           if(DecodeAudio) DecodeAudio((signed short *)H->lpData,H->dwBytesRecorded/2);
           // buffer destroy
           if(waveInUnprepareHeader(InHandleDevice,H,sizeof(WAVEHDR)))
           {
              Application->MessageBox("Unprepare error","",MB_OK | MB_ICONEXCLAMATION);
              return;
           }
           delete [] H->lpData;
           delete H;

           // keep track of how many buffers are pending
           InBufferCount--;

           // if all buffers have been processed (due to a CloseInvoked) stops the recording
           if(InBufferCount==0)
           {
              InHandleDevice=0;
           }
           break;
    }
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void SoundCard::StartWaveOut()
{
    if(OutHandleDevice) return;

    // prepare audio format for output
    WAVEFORMATEX formato;
    formato.wFormatTag      = WAVE_FORMAT_PCM;
    formato.nChannels       = 1;
    formato.nSamplesPerSec  = OutSampleRate;
    formato.nAvgBytesPerSec = OutSampleRate*2;
    formato.nBlockAlign     = 2;
    formato.wBitsPerSample  = 16;
    formato.cbSize          = 0;

    // open the output device
    MMRESULT risp = waveOutOpen(&OutHandleDevice,OutSoundCard,&formato,(DWORD)waveOutProcCallBack,0,CALLBACK_FUNCTION);

    if(risp)
    {
       AnsiString Dummy = AnsiString(risp);
            if(risp==MMSYSERR_ALLOCATED   ) Dummy = "MMSYSERR_ALLOCATED";
       else if(risp==MMSYSERR_BADDEVICEID ) Dummy = "MMSYSERR_BADDEVICEID";
       else if(risp==MMSYSERR_NODRIVER    ) Dummy = "MMSYSERR_NODRIVER";
       else if(risp==MMSYSERR_NOMEM       ) Dummy = "MMSYSERR_NOMEM";
       else if(risp==WAVERR_BADFORMAT     ) Dummy = "WAVERR_BADFORMAT";
       else if(risp==WAVERR_SYNC          ) Dummy = "WAVERR_SYNC";
       Dummy = AnsiString("Can't open output audio device #")+AnsiString(OutSoundCard)+". Error code="+Dummy;
       Application->MessageBox(Dummy.c_str(),"Error opening soundcard",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    OutBufferCount=0;
    for(int t=0;t<MAXOUTBUFFERS;t++)
    {
        CreateOutBuffer();
    }
}

void SoundCard::StopWaveOut()
{
    if(!OutHandleDevice) return;
    OutCloseInvoked = true;
}

void SoundCard::CreateOutBuffer()
{
    // create a buffer and fill it with the raw sampled data
    WAVEHDR *Header = new WAVEHDR;
    Header->lpData = (char *) new signed short[TXSIZE];

    if(EncodeAudio)
    {
       EncodeAudio((signed short *)Header->lpData,TXSIZE);
    }
    else
    {
       for(int i=0;i<TXSIZE;i++) Header->lpData[i] = 0;
    }

    if(DumpToFile)
    {
       static int file_handle=-1;
       if(file_handle==-1)
       {
          file_handle = FileCreate("c:\\dump.wav");
          WriteWavHeader(file_handle);
       }
       FileWrite(file_handle,Header->lpData,TXSIZE*2);
    }

    Header->dwBufferLength = TXSIZE*2;
    Header->dwBytesRecorded = 0;
    Header->dwUser = 0;
    Header->dwFlags = 0;
    Header->dwLoops = 0;

    // prepare the buffer
    if(waveOutPrepareHeader(OutHandleDevice,Header,sizeof(WAVEHDR))) {
       Application->MessageBox("Error preparing audio buffer","",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    // send it to the sound card
    if(waveOutWrite(OutHandleDevice,Header,sizeof(WAVEHDR))) {
       Application->MessageBox("Error sending audio buffer to the device","",MB_OK | MB_ICONEXCLAMATION);
       return;
    }

    // keep track of how many buffers there are
    OutBufferCount++;
}

void SoundCard::waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
    switch(uMsg)
    {
        case MM_WOM_OPEN:
           OutCloseInvoked = false;
           break;

        case MM_WOM_CLOSE:
           OutHandleDevice = 0;
           break;

        case MM_WOM_DONE:
           if(!OutCloseInvoked) CreateOutBuffer();

           // we have nothing to do with the buffer we outputted so let's destroy it!
           WAVEHDR *H = (WAVEHDR *)dwParam1;

           // unprepare the buffer
           if(waveOutUnprepareHeader(OutHandleDevice,H,sizeof(WAVEHDR))) {
              Application->MessageBox("Error unpreparing buffer","",MB_OK | MB_ICONEXCLAMATION);
              return;
           }
           delete[] H->lpData;
           delete H;
           OutBufferCount--;

           if(OutBufferCount==0)
           {
              OutHandleDevice=0;
           }
           break;
    }
}

void SoundCard::WriteWavHeader(int fh)
{
    int size_riff;
    int size_data;

    char MyHeader[44] = { 'R', 'I', 'F', 'F',
                          ' ', ' ', ' ', ' ',
                          'W', 'A', 'V', 'E',
                          'f', 'm', 't', ' ',
                          0x10,0x00,0x00,0x00,
                          0x01,0x00,0x01/*nchannels*/,0x00,
                          0x44,0xAC/*samplerate*/,0x00,0x00,
                          0x44,0xAC/*samplerate*/,0x02,0x00,
                          0x04,0x00,0x10,0x00,
                          'd','a','t','a',
                          ' ',' ',' ',' ' };

    int duration = 500;

    size_riff=duration*8000*2*1;
    size_data=duration*8000*2*1;

    int DataWav = size_riff +44 - 8;
    int *iptr;

    iptr = (int *)&MyHeader[4];
    *iptr = DataWav;

    DataWav = size_data - 0x2c;
    iptr = (int *)&MyHeader[40];
    *iptr = DataWav;

    FileWrite(fh,MyHeader,44);
}


