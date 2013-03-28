#include "functions.h"
#include "Path.h"

namespace fs {

std::string extractFilename(char const path[])
{
	return extractFilename(std::string(path));
}

std::string extractFilename(std::string const & path)
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

	return std::string(posPath,posPt);
}

}