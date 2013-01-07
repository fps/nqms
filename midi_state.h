#ifndef NQMS_MIDI_STATE_HH
#define NQMS_MIDI_STATE_HH

#include <jack/types.h>
#include <vector>

struct midi_state 
{
	struct voice
	{
		jack_nframes_t attack_frame;
		unsigned int attack_velocity;
		
		jack_nframes_t release_frame;
		unsigned int release_velocity;
		
		enum { IDLE, ATTACK, RELEASE } state;
		
		voice()
		:
			state(IDLE)
		{
			
		}
	};
	
	std::vector<voice> voices;
	
	midi_state(unsigned int polyphony)
	:
		voices(polyphony)
	{
		
	}
	
	void attack(jack_nframes_t frame, unsigned int note, unsigned int velocity)
	{
		
	}
};

#endif
