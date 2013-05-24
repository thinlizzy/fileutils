#ifndef FUNCTIONS_H_GUARD_3498urewjfdc
#define FUNCTIONS_H_GUARD_3498urewjfdc

#include "../classes/Status.h"
#include <NativeString.h>
#include <string>

namespace fs {

Status createDirectory(die::NativeString const & path);

// returns the filename w/o the path and extensions
die::NativeString extractFilename(die::NativeString const & path);

template<typename T>
std::basic_string<T> extractFilename(std::basic_string<T> const & path);

}

#include "extractFilename.hpp"

#endif
