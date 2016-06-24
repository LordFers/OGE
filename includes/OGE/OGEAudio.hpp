/*****************************************************************************
*   Open-source Game Engine (OGE) 0.1.0 programmed in C++
******************************************************************************
*   Copyright (C) 2016 - Fernando Alan Quinteros, 10th Dec 2015.
*   http://email:lordfers@gmail.com
******************************************************************************
*   This program is open-source and free software.
*   OGE used the standard libraries CEGUI 8.4.x and DirectX 9.
*   https://github.com/LordFers/OGE.git
*****************************************************************************/
#ifndef _H_AUDIO_
#define _H_AUDIO_

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class OGEAudio{
    public:
		OGEAudio::OGEAudio();
        void OGEAudio::PlayMIDI(std::string);
        void OGEAudio::PlayWAV(std::string);

	private:
        bool midi_run;
        bool wave_run;
        float counter;

        sf::Music music;
        sf::SoundBuffer soundbuffer;
        int lastwave;
};

#endif // _H_AUDIO_
