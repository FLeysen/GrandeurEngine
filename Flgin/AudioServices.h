#pragma once
#include "Audio.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <string>
#include <iostream>

class DefaultAudio final : public Audio
{
public:
	void playSound(int frequency, int duration) override { Beep(frequency, duration); }
	void stopAllSounds() override { PlaySound(NULL, NULL, 0); };
};

class MuteLoggerAudio final : public Audio
{
public:
	void playSound(int frequency, int duration) override { std::wcout << L"Beep at: " << frequency << " hertz for " << duration << " milliseconds\n"; }
	void stopAllSounds() override { PlaySound(NULL, NULL, 0); }
};