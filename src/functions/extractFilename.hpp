#include "../classes/Path.h"

namespace fs {

template<typename T>
std::basic_string<T> extractFilename(std::basic_string<T> const & path)
{
	if( path.empty() ) return path;

	auto posPath = path.begin();
	auto posPt = path.end();
	for( auto p = path.begin(); p != path.end(); ++p ) {
		if( Path::isDelim(*p) ) {
			posPath = p;
			posPt = path.end();
		} else
		if( *p == '.' ) {
			if( posPt == path.end() ) {
				posPt = p;
			}
		}
	}
	if( Path::isDelim(*posPath) ) {
		++posPath;
	}

	return std::basic_string<T>(posPath,posPt);
}

}