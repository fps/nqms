#ifndef NQMS_LADSPA_HH
#define NQMS_LADSPA_HH

#include <boost/shared_ptr.hpp>
#include <string>

#include <module.h>

struct ladspa_module;

typedef boost::shared_ptr<ladspa_module> ladspa_module_ptr;

struct ladspa_module : module 
{
	ladspa_module(std::string library_file, plugin_label) {
		
	}
};


#endif


