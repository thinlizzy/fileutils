#include "../functions/functions.h"

namespace fs {

NativeString extractFilename(NativeString const & path)
{
    return extractFilename<wchar_t>(path.wstr);
}

}
