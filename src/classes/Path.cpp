#include "Path.h"
#include "Status.h"
#include <algorithm>
#include <numeric>
#include <iterator>

namespace fs {

char const pathDelim = '\\';
char const otherPathDelim = '/';

Path::Path(char const path[])
{
	pathList.push_back(path);
}

Path::Path(std::string const & path)
{
	pathList.push_back(path);
}

Path::Path(std::string && path)
{
	pathList.push_back(std::move(path));
}


Path Path::append(char const subpath[]) const
{
	return append(std::string(subpath));
}

Path Path::append(std::string const & subpath) const
{
	Path result(*this);
	result.pathList.push_back(subpath);
	return result;
}

Path Path::append(Path const & subpath) const
{
	Path result(*this);
	std::copy(subpath.pathList.begin(),subpath.pathList.end(),std::back_inserter(result.pathList));
	return result;
}

Path::operator std::string() const
{
	return getPath();
}

void decode(std::string & path)
{
	std::for_each(path.begin(),path.end(),[](char & ch) {
		if( ch == otherPathDelim ) ch = pathDelim;
	});
}


std::string Path::getPath() const
{
    if( pathList.empty() ) return std::string();
            
	if( pathList.size() > 1 ) {
		std::string computed = std::accumulate(pathList.begin() + 1,pathList.end(),pathList.front(),
			[this](std::string const & path, std::string const & subpath) -> std::string {
				if( isDelim(path.back()) && isDelim(subpath.front()) ) return path.substr(0,path.size()-1) + subpath;
				if( ! isDelim(path.back()) && ! isDelim(subpath.front()) ) return path + pathDelim + subpath;
				return path + subpath;
			});
		decode(computed);
		pathList.clear();
		pathList.push_back(computed);
	}
	return pathList.front();
}

bool Path::isDelim(char ch)
{
	return ch == pathDelim || ch == otherPathDelim;
}

}