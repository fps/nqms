#ifndef NQMS_MODULE_HH
#define NQMS_MODULE_HH

#include <boost/shared_ptr.hpp>
#include <jack/types.h>
#include <string>
#include <vector>

#include <disposable.h>

struct module : disposable
{
	typedef boost::shared_ptr<std::vector<float> > buffer_ptr;
	
	/**
	 * Subclasses must resize these to the
	 * correct sizes..
	 */
	std::vector<buffer_ptr> in_port_buffers;
	std::vector<buffer_ptr> out_port_buffers;
	
	/**
	 * Subclasses must fill these with
	 * the correct information
	 */
	std::vector<std::string> in_port_names;
	std::vector<std::string> out_port_names;

	virtual ~module() 
	{ 
		
	}
	
	/**
	 * Precondition: in_port_buffers and out_port_buffers have to point
	 * to valid locations..
	 * 
	 * No assumptions about nframes can be done by the module.
	 */
	virtual void process(jack_nframes_t nframes) = 0;
};

typedef boost::shared_ptr<module> module_ptr;

#endif
