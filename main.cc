#include <boost/program_options.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

#include <engine.h>
#include <assign.h>

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
		("polyphony,p", po::value<int>()->default_value(1), "Set an initial polyphony for the patch")
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
		engine e;
		
		state_ptr new_state(new state(vm["polyphony"].as<int>()));		
		e.set_state(new_state);
		
		ifstream input("/dev/stdin");
		
		while(input.good()) {
			string line;
			getline(input, line);
			cout << line << endl;
		}
	} 
	
	catch (runtime_error e) {
		cerr << e.what() << endl;
		cerr << "Exiting..." << endl;
		return (EXIT_FAILURE);
	}
	
}

