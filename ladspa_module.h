#ifndef NQMS_LADSPA_HH
#define NQMS_LADSPA_HH

#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>
#include <ladspa.h>
#include <vector>
#include <dlfcn.h>
#include <utility>

#include <module.h>

struct ladspa_module;

typedef boost::shared_ptr<ladspa_module> ladspa_module_ptr;

struct ladspa_module : module 
{
	const LADSPA_Descriptor *descriptor;
	std::vector<LADSPA_Handle> instances;
	std::vector<LADSPA_Data> defaults;

	ladspa_module
	(
		std::string library, 
		std::string label, 
		unsigned int samplerate, 
		unsigned int polyphony = 1
	) 
	{
		instances.resize(polyphony);
		
		void *dl = dlopen(library.c_str(), RTLD_NOW);
		
		LADSPA_Descriptor_Function ladspa_descriptor_fun;
		ladspa_descriptor_fun = (LADSPA_Descriptor_Function)dlsym(dl, "ladspa_descriptor");
		
		int index = 0;
		while(true) 
		{
			descriptor = ladspa_descriptor_fun(index);
			if (0 == descriptor) 
			{
				throw std::runtime_error("Plugin not found with label: " + label);
			}
			
			if (label == descriptor->Label) 
			{
				break;
			}
			++index;
		}
		// std::cout << descriptor->Label << std::endl;

	}
	
	~ladspa_module() 
	{
		
	}
	
	static std::pair<std::string, std::string> find_plugin(std::string label_regex) {
		return std::make_pair("", "");
	}
};


#endif


