#ifndef FUNCTIONS_H_GUARD_3498urewjfdc
#define FUNCTIONS_H_GUARD_3498urewjfdc

#include "common.h"
#include <string>

namespace fs {

Status createDirectory(char const path[]);
Status createDirectory(std::string const & path);

// returns the filename w/o the path and extensions
std::string extractFilename(char const path[]);
std::string extractFilename(std::string const & path);

}

#endif
