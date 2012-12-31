#ifndef NQMS_ENGINE_HH
#define NQMS_ENGINE_HH

#include <vector>
#include <boost/function.hpp>

#include <state.h>
#include <ringbuffer.h>

struct engine 
{
	ringbuffer<boost::function<void()> > in_ringbuffer;
	
	ringbuffer<boost::function<void()> > out_ringbuffer;
	
	state_ptr the_state;
	
	engine(unsigned int in_ringbuffer_size, unsigned int out_ringbuffer_size) :
		in_ringbuffer(in_ringbuffer_size),
		out_ringbuffer(out_ringbuffer_size),
		the_state(new state) 
	{
		
	}
};

#endif
