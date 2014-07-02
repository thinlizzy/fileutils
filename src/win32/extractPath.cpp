#include "../functions/functions.h"

namespace fs {

die::NativeString extractPath(die::NativeString const & path)
{
    return extractPath<wchar_t>(path.wstr);
}

}

