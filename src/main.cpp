#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>

#include "options.hpp"

int main(int argc, char **argv)
{
	Options options;
	
	options.Parse(argc, argv);
	return 0;
}
