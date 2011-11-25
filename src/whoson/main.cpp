#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#if defined(HAVE_CSTDLIB)
# include <cstdlib>
#elif defined(HAVE_STDLIB_H)
# include <stdlib.h>
#endif

#include "options.hpp"

int main(int argc, char **argv)
{
	Options options;
	
	try {
		options.Parse(argc, argv);
	} catch(Options::ArgumentException exception) {
		// std::cerr << exception.msg << std::endl;
		exit(1);
	}
	
	return 0;
}
