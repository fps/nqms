#ifndef NQMS_MODULE_HH
#define NQMS_MODULE_HH

#include <boost/shared_ptr.hpp>
#include <jack/types.h>

#include <string>

struct module 
{
	virtual ~module() 
	{ 
		
	}
	
	virtual void process(jack_nframes_t nframes) = 0;
	
	virtual unsigned int number_of_output_ports() = 0;
	virtual unsigned int number_of_input_ports() = 0;
	
	virtual std::string get_input_port_name(unsigned int index) = 0;
	virtual std::string get_output_port_name(unsigned int index) = 0;

	virtual std::string get_input_port_description(unsigned int index) = 0;
	virtual std::string get_output_port_description(unsigned int index) = 0;

	virtual std::string get_input_port_jack_name(unsigned int index) = 0;
	virtual std::string get_output_port_jack_name(unsigned int index) = 0;
	
	virtual void set_port_value(unsigned int index, float value) = 0;
};

typedef boost::shared_ptr<module> module_ptr;

#endif
