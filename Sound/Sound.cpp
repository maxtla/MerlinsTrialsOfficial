#include "Sound.h"

HRESULT Sound::createDevice()
{	
	HRESULT hr = 0;
	hr = DirectSoundCreate8(NULL, &this->sDevice, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = this->sDevice->SetCooperativeLevel(this->wndHandle, DSSCL_PRIORITY); 
	if (FAILED(hr))
	{
		return hr;
	}
	
	DSCAPS dscaps;
	dscaps.dwSize = sizeof(DSCAPS);
	hr = this->sDevice->GetCaps(&dscaps);
	if (FAILED(hr))
	{
		return hr;
	}
	//GetSpeakerConfig
}

HRESULT Sound::createSecondaryBuffer(int lengthOfWavInSecs = 3)
{
	WAVEFORMATEX wfx;
	memset(&wfx, 0, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = 22050;
	wfx.nBlockAlign = 4;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.wBitsPerSample = 16;

	DSBUFFERDESC dsbdesc;
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY
		| DSBCAPS_GLOBALFOCUS;
	dsbdesc.dwBufferBytes = lengthOfWavInSecs * wfx.nAvgBytesPerSec;
	dsbdesc.lpwfxFormat = &wfx;

	LPDIRECTSOUNDBUFFER pDsb = NULL;
	HRESULT hr = 0;
	hr = this->sDevice->CreateSoundBuffer(&dsbdesc, &pDsb, NULL);
	if (SUCCEEDED(hr))
	{
		hr = pDsb->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)this->secondaryBuffer);
		pDsb->Release();
	}

	return hr;
}
