#pragma once
class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(int frequency, int duration) = 0;
	virtual void stopAllSounds() = 0;
};