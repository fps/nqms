#ifndef LADSPA_PLUGIN_HH
#define LADSPA_PLUGIN_HH

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include <iostream>
#include <library.h>

namespace ladspapp 
{
	struct ladspa_plugin
	:
		boost::noncopyable
	{
		library_ptr the_library;
		const LADSPA_Descriptor *descriptor;
		
		ladspa_plugin(library_ptr the_library, const LADSPA_Descriptor *descriptor)
		throw 
		(
			std::runtime_error
		)
		:
			the_library(the_library),
			descriptor(descriptor)
		{
			std::cerr << uid() << "\t" << label() << "\t" << name() << " " << maker() << std::endl;
		}
		
		std::string label() 
		{
			return descriptor->Label;
		}
		
		std::string name()
		{
			return descriptor->Name;
		}
		
		std::string maker()
		{
			return descriptor->Maker;
		}
		
		unsigned long uid()
		{
			return descriptor->UniqueID;
		}
	};
	
	typedef boost::shared_ptr<ladspa_plugin> ladspa_plugin_ptr;
} // namespace

#endif
