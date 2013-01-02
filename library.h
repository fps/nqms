#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <dlfcn.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

/**
 * A utility type just to get a reference counted
 * dlopen() handle..
 */
struct library : boost::noncopyable {
	void *dl;
	
	library(std::string filename, int flags = RTLD_NOW)
	throw 
	(
		std::runtime_error
	)
	{
		/**
		 * Reset possible leftover errors.
		 */
		dlerror();
		
		dl = dlopen(filename.c_str(), flags);
		
		if (NULL == dl)
		{
			throw std::runtime_error("Failed to dlopen " + filename + " Reason: " + dlerror());
		}
	}
	
	~library() 
	{
		dlclose(dl);
	}
};

typedef boost::shared_ptr<library> library_ptr;
	
#endif