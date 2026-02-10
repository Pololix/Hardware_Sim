add_library(debug_utils STATIC
	include/debug_utils/logger.h
)

target_include_directories(debug_utils
	PUBLIC
		include
)