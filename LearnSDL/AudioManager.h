#pragma once

#include "AssetManager.h"

class AudioManager
{
private:
	static AudioManager* sInstance;

	AssetManager* mAssetManager;

public:
	static AudioManager* Instance();
	static void Release();

	void PlayMusic(const std::string& filename, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(const std::string& filename, int loops = 0, int channel = 0);
	void PauseSFX();
	void ResumeSFX();

private:
	AudioManager();
	~AudioManager();
};