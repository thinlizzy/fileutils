#ifndef FUNCTIONS_H_GUARD_3498urewjfdc
#define FUNCTIONS_H_GUARD_3498urewjfdc

#include "../classes/Status.h"
#include "../classes/NativeString.h"
#include <string>

namespace fs {

Status createDirectory(NativeString const & path);

// returns the filename w/o the path and extensions
NativeString extractFilename(NativeString const & path);

template<typename T>
std::basic_string<T> extractFilename(std::basic_string<T> const & path);

}

#include "extractFilename.hpp"

#endif
