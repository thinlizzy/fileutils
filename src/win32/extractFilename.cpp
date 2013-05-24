#include "../functions/functions.h"

namespace fs {

die::NativeString extractFilename(die::NativeString const & path)
{
    return extractFilename<wchar_t>(path.wstr);
}

}
