#ifndef LADSPAPP_LADSPA_LIBRARY_HH
#define LADSPAPP_LADSPA_LIBRARY_HH

#include <string>
#include <vector>
#include <dlfcn.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

#include <ladspa_plugin.h>

namespace ladspapp 
{
	/**
	* A simple wrapper class around a LADSPA library file
	* to make some reoccuring work easier..
	*/
	struct ladspa_library : boost::noncopyable {
		std::string library;
		
		std::vector<const LADSPA_Descriptor *> descriptors;
		
		LADSPA_Descriptor_Function ladspa_descriptor_fun;
		
		void *dl;
		
		/**
		* Opens and loads a LADSPA library file..
		* 
		* Might throw std::runtime_error in case something went wrong..
		*/
		ladspa_library(std::string library, bool load_library = false) :
			library(library),
			dl(NULL)
		{
			std::cerr << "LADSPA library: " << library << std::endl;

			if (true == load_library) 
			{
				load();
			}
		}
		
		/**
		* Closes the library handle if nessecary..
		*/
		~ladspa_library() 
		{
			if (NULL != dl) 
			{
				/**
				 * Destructors MUST NOT throw exceptions.
				 */
				try 
				{
					unload();
				}
				catch (std::runtime_error e)
				{
					std::cerr << "Warning: Library unloading failed. Maybe it was already unloaded?" << std::endl;
				}
			}
		}
		
		void load() 
		{
			if (NULL != dl)
			{
				throw std::runtime_error("Library already loaded: " + library);
			}
			
			dlerror();
			
			dl = dlopen(library.c_str(), RTLD_NOW);
			
			if (NULL == dl) 
			{
				throw std::runtime_error("Failed to open library: " + library + ". dlerror: " + dlerror());
			}
			
			ladspa_descriptor_fun = (LADSPA_Descriptor_Function)dlsym(dl, "ladspa_descriptor");
			
			char *error = dlerror();
			if (NULL != error) {
				dlclose(dl);
				throw std::runtime_error("Failed to lookup ladspa_descriptor. dlerror: " + std::string(error));
			}
			
			int index = 0;
			while(true) 
			{
				const LADSPA_Descriptor *descriptor;
				descriptor = ladspa_descriptor_fun(index);
				if (0 == descriptor) 
				{
					break;
				}
				
				std::cerr << "Plugin: " << descriptor->Label << std::endl;
				
				descriptors.push_back(descriptor);
				++index;
			}
		}
		
		void unload() 
		{
			if (NULL == dl)
			{
				throw std::runtime_error("Library already unloaded");
			}
			
			dlclose(dl);
			dl = NULL;
		}
		
		std::vector<std::string> labels() 
		{
			std::vector<std::string> ret;
			for (unsigned int index = 0; index < descriptors.size(); ++index) {
				ret.push_back(descriptors[index]->Label);
			}
			
			return ret;
		}
		
		ladspa_plugin get_plugin(std::string label) {
			for (unsigned int index = 0; index < descriptors.size(); ++index) {
				if (descriptors[index]->Label == label) {
					return get_plugin(index);
				}
			}
		}
		
		ladspa_plugin get_plugin(unsigned int index) {
			ladspa_plugin plugin(descriptors[index]);
			
			return plugin;
		}
	};
	
	typedef boost::shared_ptr<ladspa_library> ladspa_library_ptr;
} // namespace

#endif
