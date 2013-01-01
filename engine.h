#ifndef NQMS_ENGINE_HH
#define NQMS_ENGINE_HH

#include <vector>
#include <list>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <jack/jack.h>
#include <iostream>
#include <unistd.h>
#include <map>

#include <ringbuffer.h>
#include <assign.h>
#include <disposable.h>
#include <module.h>

extern "C" {
	int process(jack_nframes_t nframes, void *arg);
}

struct engine 
{
	jack_client_t *jack_client;
	
	ringbuffer<boost::function<void()> > cmds;
	ringbuffer<int> acks;
	
	std::list<disposable_ptr> heap;
	
	boost::shared_ptr<std::list<module_ptr> > modules;
	std::map<module_ptr, std::vector<jack_port_t*> > module_jack_ports;
	
	unsigned int control_period;
	unsigned int elapsed_frames;
	
	engine(unsigned int control_period) 
	:
		cmds(1024),
		acks(1024),
		elapsed_frames(0)
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
	
	~engine() 
	{
		std::cerr << "Engine shutting down..." << std::endl;

		jack_deactivate(jack_client);
		jack_client_close(jack_client);
	}
	
	int process(jack_nframes_t nframes) 
	{
		if(cmds.can_read()) 
		{
			// std::cerr << "cmd" << std::endl;
			cmds.read()();
			acks.write(0);
		}
		
		for 
		(
			std::list<module_ptr>::iterator it = modules->begin();
			it != modules->end();
			++it
		)
		{
			(*it)->process(nframes);
		}
		
		return 0;
	}
	
	void wait_for_ack() 
	{
		while(false == acks.can_read()) {
			usleep(10000);
		}
		
		// std::cerr << "ack" << std::endl;
		acks.read();
	}
	
	void write_cmd(boost::function<void()> f) 
	{
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
	void cleanup_heap() 
	{
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
	
	void add_module(module_ptr module)
	{
		/**
		 * Create jack ports for module
		 */
		
		
		/**
		 * Create new modules list from old one
		 */
		
		
		/**
		 * Assign the new one
		 */
	}
	
	void remove_module(unsigned int index) 
	{
		/**
		 * Create new modules list
		 */
		
		
		/**
		 * Assign it
		 */
		
		/**
		 * Remove the module's jack ports
		 */
	}
};


extern "C" {
	int process(jack_nframes_t nframes, void *arg) 
	{
		return ((engine*)arg)->process(nframes);
	}
}

#endif
