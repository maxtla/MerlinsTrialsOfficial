#ifndef SOUND_H
#define SOUND_H
#include "Dsound.h"

class Sound
{
private:
	LPDIRECTSOUND8 sDevice;
	LPDIRECTSOUNDBUFFER8* secondaryBuffer;
	HWND wndHandle;

	HRESULT createDevice();
	
public:
	HRESULT createSecondaryBuffer(int lengthOfWavInSecs);
};

#endif
