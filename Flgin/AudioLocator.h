#pragma once
#include "Audio.h"
class AudioLocator
{
public:
	static Audio* GetAudio() { return m_Service; }
	static void Provide(Audio* service) { m_Service = service; }
private:
	static Audio* m_Service;
};
Audio* AudioLocator::m_Service{ nullptr };