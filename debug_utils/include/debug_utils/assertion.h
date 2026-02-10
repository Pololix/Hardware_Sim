#pragma once

#include <iostream>

#ifdef _DEBUG
	#define DEBUG_ASSERT(cond, msg)\
		do {\
			if(!(cond))\
			{\
				// TODO: defer logging to avoid io in header file
				std::cout << __func__ << " failed at " << __FILE__ << " line " << __LINE__ << '\n';\
				std::cout << "Log: " << msg << '\n';\
				std::abort();\
			}\
		} while(0);\
#else
	#define DEBUG_ASSERT(cond, msg) (void(0))
#endif