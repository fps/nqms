#ifndef NQMS_STATE_HH
#define NQMS_STATE_HH

#include <vector>
#include <boost/shared_ptr.hpp>

#include <module.h>

struct state 
{
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
};


typedef boost::shared_ptr<state> state_ptr;

#endif
