#ifndef PATH_H_GUARD_dj2434324
#define PATH_H_GUARD_dj2434324

#include <deque>
#include <string>

namespace fs {

class Path {
	mutable std::deque<std::string> pathList;
public:
	Path() = default;
	Path(char const path[]);
	Path(std::string const & path);
	Path(std::string && path);
	Path append(char const subpath[]) const;
	Path append(std::string const & subpath) const;
	Path append(Path const & subpath) const;
	std::string getPath() const;
	operator std::string() const;

	static bool isDelim(char ch);
};

}

#endif
