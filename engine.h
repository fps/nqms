#ifndef NQMS_ENGINE_HH
#define NQMS_ENGINE_HH

#include <jack/ringbuffer.h>

#include <vector>

#include <state.h>

struct engine 
{
	/**
	 * Pass in new engine state through in
	 */
	jack_ringbuffer_t *in;
	
	/**
	 * The old one is passed out through this so it 
	 * can be cleaned up by the main thread
	 */
	jack_ringbuffer_t *out;
	
	state *the_state;
	
	engine() :
		in(0),
		out(0),
		the_state(0) 
	{
		
	}
};

#endif
