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
#include <disposable.h>

extern "C" {
	int process(jack_nframes_t nframes, void *arg);
}

struct engine 
{
	ringbuffer<boost::function<void()> > cmds;
	ringbuffer<int> acks;
	
	std::list<disposable_ptr> heap;
	
	std::list<module_ptr> modules;
	
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
		if(cmds.can_read()) {
			// std::cerr << "cmd" << std::endl;
			cmds.read()();
			acks.write(0);
		}
		
		return the_state->process(nframes);
	}
	
	void wait_for_ack() {
		while(false == acks.can_read()) {
			usleep(10000);
		}
		
		// std::cerr << "ack" << std::endl;
		acks.read();
	}
	
	void set_state(state_ptr new_state) {
		heap.push_back(new_state);
		write_cmd(assign_and_clear(the_state, new_state));
	}
	
	void write_cmd(boost::function<void()> f) {
		while(false == cmds.can_write()) {
			usleep(10000);
		}
		cmds.write(f);
		wait_for_ack();
	}
	
	/**
	 * TODO: call this regularly from a thread and 
	 * protect the way to add to it with a mutex
	 */
	void cleanup_heap() {
		for (
			std::list<disposable_ptr>::iterator it = heap.begin();
			it != heap.end();
		) {
			// std::cerr << "unique?" << std::endl;
			if ((*it).unique()) 
			{
				// std::cerr << "erasing" << std::endl;
				it = heap.erase(it);
			} 
			else 
			{
				++it;
			}
		}
	}
};


extern "C" {
	int process(jack_nframes_t nframes, void *arg) {
		return ((engine*)arg)->process(nframes);
	}
}

#endif
