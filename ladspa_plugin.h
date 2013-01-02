#ifndef LADSPA_PLUGIN_HH
#define LADSPA_PLUGIN_HH

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include <ladspa_plugin_instance.h>

namespace ladspapp 
{
	/**
	* Create instances of this class using the
	* ladspa_library class. Note that you MUST 
	* not delete ladspa_library instance during the 
	* lifetime of the ladspa_plugin. 
	*/
	struct ladspa_plugin : boost::noncopyable 
	{
		const LADSPA_Descriptor *descriptor;
		LADSPA_Handle instance;
		
		ladspa_plugin(const LADSPA_Descriptor *descriptor) 
		:
			descriptor(descriptor)
		{
			
		}
		
		std::string label() {
			return descriptor->Label;
		}
		
		void instantiate() {
			
		}
	};
	
	typedef boost::shared_ptr<ladspa_plugin> ladspa_plugin_ptr;
} // namespace

#endif
