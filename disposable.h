#ifndef NQMS_DISPOSABLE_HH
#define NQMS_DISPOSABLE_HH

#include <boost/shared_ptr.hpp>

struct disposable {
	virtual ~disposable() { }
};

typedef boost::shared_ptr<disposable> disposable_ptr;

#endif
