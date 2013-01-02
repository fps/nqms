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
#include <ladspa_plugin.h>
#include <ladspa_library.h>


struct ladspa_module;

typedef boost::shared_ptr<ladspa_module> ladspa_module_ptr;

struct ladspa_module : module
{
	ladspapp::ladspa_plugin_ptr plugin;
	
	unsigned int samplerate;

	std::vector<LADSPA_Handle> instances;
	std::vector<LADSPA_Data> defaults;

	ladspa_module
	(
		ladspapp::ladspa_plugin_ptr plugin,
		unsigned int samplerate, 
		unsigned int polyphony
	) 
	:
		plugin(plugin),
		samplerate(samplerate)
	{
		instances.resize(polyphony);
		
#if 0
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
		std::cerr << descriptor->Label << std::endl;
		
		for (unsigned int index = 0; index < descriptor->PortCount; ++index) {
			if (LADSPA_IS_PORT_INPUT(descriptor->PortDescriptors[index])) {
				in_port_buffers.push_back(0);
				in_port_descriptions.push_back("");
				in_port_names.push_back(descriptor->PortNames[index]);
				defaults.push_back(get_port_default(index));
			} else {
				out_port_buffers.push_back(0);
				out_port_descriptions.push_back("");
				out_port_names.push_back(descriptor->PortNames[index]);
				defaults.push_back(0);
			}
		}
#endif
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
	
	LADSPA_Data get_port_default(unsigned int port_index) 
	{
#if 0
		LADSPA_PortRangeHintDescriptor x = descriptor->PortRangeHints[port_index].HintDescriptor;
		float def = 0.0f;
		if (LADSPA_IS_HINT_BOUNDED_BELOW(x)) { }
		if (LADSPA_IS_HINT_BOUNDED_ABOVE(x)) { }
		if (LADSPA_IS_HINT_TOGGLED(x)) { }
		if (LADSPA_IS_HINT_LOGARITHMIC(x)) { }
		if (LADSPA_IS_HINT_INTEGER(x)) { } 

		if (LADSPA_IS_HINT_DEFAULT_440(x)) {
			return 440.0f;
		}
		if (LADSPA_IS_HINT_DEFAULT_100(x)) {
			return 100.0f;
		}
		if (LADSPA_IS_HINT_DEFAULT_1(x)) {
			return  1.0f;
		}
		if (LADSPA_IS_HINT_DEFAULT_0(x)) {
			return  0.0f;
		}
		
		if (LADSPA_IS_HINT_SAMPLE_RATE(x)) 
		{ 
			if (LADSPA_IS_HINT_DEFAULT_MINIMUM(x)) {
				def =  descriptor->PortRangeHints[port_index].LowerBound;
			}
											
			if (LADSPA_IS_HINT_DEFAULT_LOW(x)) { 
				def =  (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}   
											
			if (LADSPA_IS_HINT_DEFAULT_MIDDLE(x)) { 
				def = (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}
												
			if (LADSPA_IS_HINT_DEFAULT_HIGH(x)) {
				def =  (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}   
											
			if (LADSPA_IS_HINT_DEFAULT_MAXIMUM(x)) { 
				def =  descriptor->PortRangeHints[port_index].UpperBound;
			}
			return samplerate * def; 
		} 
		else 
		{
			if (LADSPA_IS_HINT_DEFAULT_MINIMUM(x)) 
			{
				def =  descriptor->PortRangeHints[port_index].LowerBound;
			}
											
			if (LADSPA_IS_HINT_DEFAULT_LOW(x)) 
			{ 
				def =  (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}   
											
			if (LADSPA_IS_HINT_DEFAULT_MIDDLE(x)) 
			{ 
				def = (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}
												
			if (LADSPA_IS_HINT_DEFAULT_HIGH(x)) 
			{
				def =  (descriptor->PortRangeHints[port_index].UpperBound + descriptor->PortRangeHints[port_index].LowerBound) / 2;
			}   
											
			if (LADSPA_IS_HINT_DEFAULT_MAXIMUM(x)) 
			{ 
				def =  descriptor->PortRangeHints[port_index].UpperBound;
			}
			
		}
		return def;
#endif
		return 0;
	}
};

#endif


