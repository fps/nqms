#include <boost/program_options.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>

#include <engine.h>
#include <assign.h>
#include <ladspa_world.h>
#include <ladspa_module.h>

int main(int argc, char *argv[]) 
{
	namespace po = boost::program_options;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::ifstream;
	using std::getline;
	using std::string;
	using std::runtime_error;
	using std::exception;
	
	po::options_description desc;
	
	desc.add_options()
		("help,h", "Display help output")
		("polyphony,p", po::value<int>()->default_value(1), "Polyphony for the patch")
		;
		
	po::variables_map vm;
	
	try 
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		
		if (vm.count("help")) {
			cout << desc << endl;
			return(EXIT_SUCCESS);
		}
	
		po::notify(vm);
	} 
	
	catch (po::error e) 
	{
		cerr << e.what() << endl;
		cerr << "Exiting..." << endl;
		return (EXIT_FAILURE);
	}
	
	try 
	{
		unsigned int polyphony = vm["polyphony"].as<int>();
		
		engine e(polyphony);
		
		std::vector<ladspapp::ladspa_library_ptr> ladspa_libaries = ladspapp::ladspa_world_scan(true);
		
#if 0
		//! TEST
		{
			state_ptr new_state1(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state1);
			state_ptr new_state2(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state2);
			state_ptr new_state3(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state3);
			state_ptr new_state4(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state4);
			state_ptr new_state5(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state5);
			state_ptr new_state6(new state(vm["polyphony"].as<int>()));
			e.set_state(new_state6);
		}
#endif

		{
			//ladspa_module_ptr module(new ladspa_module("/usr/lib/ladspa/cmt.so", "syndrum", e.samplerate(), polyphony));
			//e.add_module(module);
		}

		ifstream input("/dev/stdin");
		
		while(input.good()) {
			string line;
			getline(input, line);
			cout << line << endl;
			
			e.cleanup_heap();
		}
	}
	
	catch (runtime_error e) {
		cerr << e.what() << endl;
		cerr << "Exiting..." << endl;
		return (EXIT_FAILURE);
	}
	
}

