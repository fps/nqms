#ifndef LADSPAPP_LADSPA_PLUGIN_INSTANCE
#define LADSPAPP_LADSPA_PLUGIN_INSTANCE

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>

#include <library.h>

struct ladspa_plugin_instance : boost::noncopyable {
	library_ptr the_library;
	LADSPA_Descriptor *descriptor;
	
    ladspa_plugin_instance
    (
		library_ptr the_library,
		LADSPA_Descriptor *descriptor
	)
	throw 
	(
		std::runtime_error
	)
	:
		the_library(the_library),
		descriptor(descriptor)
	{
		
	}
};

typedef boost::shared_ptr<ladspa_plugin_instance> ladspa_plugin_instance_ptr;

#endif
