#ifndef LADSPAPP_LADSPA_WORLD_HH
#define LADSPAPP_LADSPA_WORLD_HH

#include <string>
#include <vector>
#include <boost/regex.hpp>

#include <ladspapp.h>
#include <ladspa_plugin.h>

namespace ladspapp 
{
	struct ladspa_world
	{
		const std::vector<ladspapp::ladspa_library_ptr> ladspa_libraries;
		
		ladspa_world(std::string ladspa_path = get_ladspa_path_from_environment())
		:
			ladspa_libraries(ladspapp::ladspa_world_scan(ladspa_path))
		{
			
		}
		
		std::vector<ladspa_plugin_ptr> find_plugins_by_name(std::string name_regex)
		{
			return std::vector<ladspa_plugin_ptr>();
		}
		
		std::vector<ladspa_plugin_ptr> find_plugins_by_label(std::string label_regex)
		{
			return std::vector<ladspa_plugin_ptr>();
		}
		
		ladspa_plugin_ptr find_plugin_by_uid(unsigned long uid)
		{
			for (unsigned int library_index = 0; library_index < ladspa_libraries.size(); ++library_index)
			{
				for (unsigned int plugin_index = 0; plugin_index < ladspa_libraries[library_index]->ladspa_plugins.size(); ++plugin_index)
				{
					if (ladspa_libraries[library_index]->ladspa_plugins[plugin_index]->uid() == uid)
					{
						return ladspa_libraries[library_index]->ladspa_plugins[plugin_index];
					}
				}
			}
			return ladspa_plugin_ptr();
		}
	};
} // namespace

#endif
