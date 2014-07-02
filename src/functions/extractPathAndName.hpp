#include "../classes/Path.h"
#include <algorithm>

namespace fs {

template<typename T>
basic_PathAndName<T> extractPathAndName(std::basic_string<T> const & path)
{
	if( path.empty() ) return {path,path};

    auto rit = std::find_if(path.rbegin(),path.rend(),[](T c) { return Path::isDelim(c); });
    if( rit == path.rend() ) return { std::basic_string<T>() , path };
    
    auto it_delim = rit.base();
    return { std::basic_string<T>(path.begin(),it_delim) , std::basic_string<T>(std::next(it_delim),path.end()) };
}

}