#ifndef FUNCTIONS_H_GUARD_3498urewjfdc
#define FUNCTIONS_H_GUARD_3498urewjfdc

#include "../classes/Status.h"
#include "../classes/Filename.h"
#include <string>

namespace fs {
    
struct PathAndName {
    Filename path;
    Filename filename;
};

Status createDirectory(Filename const & path);

// returns the path w/o the filename
Filename extractPath(Filename const & path);

// returns the filename w/o the path and extensions
Filename extractFilename(Filename const & path);

// returns both
PathAndName extractPathAndName(Filename const & path);

template<typename T>
std::basic_string<T> extractPath(std::basic_string<T> const & path);

template<typename T>
std::basic_string<T> extractFilename(std::basic_string<T> const & path);

template<typename T>
struct basic_PathAndName {
    std::basic_string<T> path;
    std::basic_string<T> filename;
};

template<typename T>
basic_PathAndName<T> extractPathAndName(std::basic_string<T> const & path);

}

#include "extractPath.hpp"
#include "extractFilename.hpp"
#include "extractPathAndName.hpp"

#endif
