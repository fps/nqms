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
	jack_ringbuffer_t *in_ringbuffer;
	
	/**
	 * The old one is passed out through this so it 
	 * can be cleaned up by the main thread
	 */
	jack_ringbuffer_t *out_ringbuffer;
	
	state *the_state;
	
	/**
	 * The sizes are the size in terms of state pointers that 
	 * must fit in
	 */
	engine(unsigned int in_ringbuffer_size, unsigned int out_ringbuffer_size) :
		in_ringbuffer(0),
		out_ringbuffer(0),
		the_state(0) 
	{
		the_state = new state;
		
		in_ringbuffer = jack_ringbuffer_create(in_ringbuffer_size * sizeof(state *));
		out_ringbuffer = jack_ringbuffer_create(out_ringbuffer_size * sizeof(state *));
	}
};

#endif
