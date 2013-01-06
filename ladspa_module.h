#ifndef NQMS_LADSPA_HH
#define NQMS_LADSPA_HH

#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>
#include <ladspa.h>
#include <iostream>
#include <vector>
#include <utility>

#include <module.h>
#include <ladspamm-0/plugin_instance.h>


struct ladspa_module;

typedef boost::shared_ptr<ladspa_module> ladspa_module_ptr;

struct ladspa_module : module
{
	ladspamm::plugin_ptr plugin;
	
	unsigned int samplerate;

	std::vector<ladspamm::plugin_instance_ptr> instances;
	std::vector<LADSPA_Data> defaults;

	ladspa_module
	(
		ladspamm::plugin_ptr plugin,
		unsigned int samplerate, 
		unsigned int polyphony
	) 
	:
		plugin(plugin),
		samplerate(samplerate)
	{
		for (unsigned int index = 0; index < polyphony; ++index)
		{
			instances.push_back(ladspamm::plugin_instance_ptr(new ladspamm::plugin_instance(plugin, samplerate)));
		}

		for (unsigned int index = 0; index < plugin->port_count(); ++index) {
			if (plugin->port_is_input(index)) {
				in_port_buffers.push_back(0);
				in_port_names.push_back(plugin->port_name(index));
				defaults.push_back(instances[0]->port_default_guessed(index));
			} else {
				out_port_buffers.push_back(0);
				out_port_names.push_back(plugin->port_name(index));
				defaults.push_back(0);
			}
		}
	}
	
	~ladspa_module() 
	{
		
	}
	
	virtual void process(jack_nframes_t nframes)
	{
#if 0
		for (jack_nframes_t frame = 0; frame < nframes; ++frame) {
			unsigned int audio_in = 0;
			unsigned int audio_out = 0;
		
			for (unsigned int instance_index = 0; instance_index < instances.size(); ++instance_index)
			{
				for (unsigned int port_index = 0; port_index < descriptor->PortCount; ++port_index) 
				{
					if (LADSPA_IS_PORT_INPUT(descriptor->PortDescriptors[port_index])) 
					{
						descriptor->connect_port(instances[instance_index], port_index, in_port_buffers[audio_in++] + frame);
					} 
					else 
					{
						descriptor->connect_port(instances[instance_index], port_index, out_port_buffers[audio_out++] + frame);
					}
				}
				descriptor->run(instances[instance_index], 1);
			}
		}
#endif
	}
	
	static std::pair<std::string, std::string> find_plugin(std::string label_regex) 
	{
		return std::make_pair("", "");
	}
};

#endif


