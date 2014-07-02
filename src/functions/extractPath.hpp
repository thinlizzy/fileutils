#include "../classes/Path.h"
#include <algorithm>

namespace fs {

template<typename T>
std::basic_string<T> extractPath(std::basic_string<T> const & path)
{
	if( path.empty() ) return path;

    auto rit = std::find_if(path.rbegin(),path.rend(),[](T c) { return Path::isDelim(c); });
    if( rit == path.rend() ) return std::basic_string<T>();
    
    return std::basic_string<T>(path.begin(),rit.base());
}

}