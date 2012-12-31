#ifndef NQMS_MODULE_HH
#define NQMS_MODULE_HH

#include <boost/shared_ptr.hpp>

struct module 
{
	virtual ~module() 
	{ 
		
	}
};

typedef boost::shared_ptr<module> module_ptr;

#endif
