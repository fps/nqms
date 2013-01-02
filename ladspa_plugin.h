#ifndef LADSPA_PLUGIN_HH
#define LADSPA_PLUGIN_HH

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>

#include <library.h>

namespace ladspapp 
{
	/**
	* Create instances of this class using the
	* ladspa_library class. Note that you MUST 
	* not delete ladspa_library instance during the 
	* lifetime of the ladspa_plugin. 
	*/
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
			
		}
		
		std::string label() 
		{
			return descriptor->Label;
		}
		
		std::string name()
		{
			return descriptor->Name;
		}
		
		unsigned long uid()
		{
			return descriptor->UniqueID;
		}
	};
	
	typedef boost::shared_ptr<ladspa_plugin> ladspa_plugin_ptr;
} // namespace

#endif
