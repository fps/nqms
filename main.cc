#include <boost/program_options.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <ladspamm-0/world.h>
#include <ladspamm-0/plugin_instance.h>

#include <engine.h>
#include <assign.h>
#include <ladspa_module.h>

int main(int argc, char *argv[]) 
{
	namespace po = boost::program_options;
	
	po::options_description desc;
	
	desc.add_options()
		("help,h", "Display help output")
		("polyphony,p", po::value<int>()->default_value(1), "Polyphony for the patch")
		("audio-ports,a", po::value<int>()->default_value(2), "Number of audio ports (in and out)")
		;
		
	po::variables_map vm;
	
	try 
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		
		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return(EXIT_SUCCESS);
		}
	
		po::notify(vm);
	} 
	
	catch (po::error &e) 
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Exiting..." << std::endl;
		return (EXIT_FAILURE);
	}
	
	try 
	{
		unsigned int polyphony = vm["polyphony"].as<int>();
		unsigned int audio_ports = vm["audio-ports"].as<int>();

		engine e(polyphony, audio_ports);
		
		ladspamm::world the_ladspa_world;
		
		ladspa_module_ptr m(
			new ladspa_module(
				the_ladspa_world.libraries[1]->plugins[0], 
				e.samplerate(), 
				e.polyphony()
			)
		);
		
		e.add_module(m);
		
		char *line;
		while (NULL != (line = readline("> ")))
		{
			if (line != std::string())
			{
				add_history(line);
			}
			
			e.cleanup_heap();
		}
	}
	
	catch (std::runtime_error &e) 
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Exiting..." << std::endl;
		return (EXIT_FAILURE);
	}
	
}

