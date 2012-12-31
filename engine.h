#ifndef NQMS_ENGINE_HH
#define NQMS_ENGINE_HH

#include <vector>
#include <list>
#include <boost/function.hpp>
#include <stdexcept>
#include <jack/jack.h>
#include <iostream>
#include <unistd.h>

#include <state.h>
#include <ringbuffer.h>
#include <assign.h>

extern "C" {
	int process(jack_nframes_t nframes, void *arg);
}

struct engine 
{
	ringbuffer<boost::function<void()> > cmds;
	
	std::list<state_ptr> state_heap;
	
	state_ptr the_state;
	
	jack_client_t *jack_client;
	
	engine() :
		cmds(1024),
		the_state(new state) 
	{
		std::cerr << "Engine starting up..." << std::endl;
		jack_status_t status;
		jack_client = jack_client_open("nqms", JackNullOption, &status);
		
		if (NULL == jack_client) 
		{
			throw std::runtime_error("Failed to open jack client");
		}
		
		jack_set_process_callback(jack_client, ::process, (void*)this);
		jack_activate(jack_client);
	}
	
	~engine() {
		std::cerr << "Engine shutting down..." << std::endl;

		jack_deactivate(jack_client);
		jack_client_close(jack_client);
	}
	
	int process(jack_nframes_t nframes) {
		return the_state->process(nframes);
	}
	
	void set_state(state_ptr new_state) {
		state_heap.push_back(new_state);
		write_cmd(assign_and_clear(the_state, new_state));
	}
	
	void write_cmd(boost::function<void()> f) {
		while(false == cmds.can_write()) {
			usleep(10000);
		}
	}
};


extern "C" {
	int process(jack_nframes_t nframes, void *arg) {
		return ((engine*)arg)->process(nframes);
	}
}

#endif
