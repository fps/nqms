#ifndef NQMS_LADSPA_HH
#define NQMS_LADSPA_HH

#include <boost/shared_ptr.hpp>

#include <module.h>

struct ladspa_module : module 
{
	
};

typedef boost::shared_ptr<ladspa_module> ladspa_module_ptr;

#endif


