#ifndef NQMS_STATE_HH
#define NQMS_STATE_HH

#include <vector>
#include <map>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <jack/jack.h>

#include <module.h>
#include <disposable.h>

struct state : disposable
{
	unsigned int polyphony;
	
	std::map<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> > connections;
	
	state(unsigned int polyphony = 1) :
		polyphony(polyphony)
	{
		
	}
	
	std::vector<module_ptr> modules;
	
	void connect(
		unsigned int source_module_index, 
		unsigned int source_port_index, 
		unsigned int target_module_index,
		unsigned int target_port_index
	) {
		
	}
	
	void set_port_value(
		unsigned int module_index,
		unsigned int port_index,
		float value
	) {
		
	}
	
	int process(jack_nframes_t nframes) {
		return 0;
	}
};


typedef boost::shared_ptr<state> state_ptr;

#endif
