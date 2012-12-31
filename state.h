#ifndef NQMS_STATE_HH
#define NQMS_STATE_HH

#include <vector>
#include <boost/shared_ptr.hpp>

#include <module.h>

struct state 
{
	std::vector<module_ptr> modules;
};

#endif
