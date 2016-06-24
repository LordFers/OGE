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

#include "OGEAudio.hpp"
class OGESound : public sf::SoundStream{
public:

    void load(const sf::SoundBuffer& buffer){
        // extract the audio samples from the sound buffer to our own container
        m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

        // reset the current playing position
        m_currentSample = 0;

        // initialize the base class
        initialize(buffer.getChannelCount(), buffer.getSampleRate());
    }

private:

    virtual bool onGetData(Chunk& data){
        const int samplesToStream = 50000;
        data.samples = &m_samples[m_currentSample];
        if (m_currentSample + samplesToStream <= m_samples.size()){
            data.sampleCount = samplesToStream;
            m_currentSample += samplesToStream;
            return true;
        }
        else{
            data.sampleCount = m_samples.size() - m_currentSample;
            m_currentSample = m_samples.size();
            return false;
        }
    }

    virtual void onSeek(sf::Time timeOffset){
        m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    }

    std::vector<sf::Int16> m_samples;
    std::size_t m_currentSample;
};

OGESound sound[30];

OGEAudio::OGEAudio(){
    this->lastwave = 0;
    this->midi_run = false;
    this->wave_run = false;
}

void OGEAudio::PlayMIDI(std::string filename){
    music.stop();
	filename = "Resources/midis/" + filename;

    if (!music.openFromFile(filename)){
        std::cout << "Error loading file: " << filename << std::endl;
    }

    music.setPosition(0, 0, 0); //Sound 3D
    music.setPitch(1);
    music.setVolume(50);
    music.setLoop(true);

    // Play it
    music.play();
    midi_run = true;
}

void OGEAudio::PlayWAV(std::string filename){

    if (lastwave >= 30)
		lastwave = 0;

	filename = "Resources/wavs/" + filename;

    soundbuffer.loadFromFile(filename);
    sound[lastwave].load(soundbuffer);
    sound[lastwave].play();
    ++lastwave;

    wave_run = true;
}
