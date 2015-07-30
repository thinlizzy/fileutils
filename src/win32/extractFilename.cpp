#include "../functions/functions.h"

namespace fs {

Filename extractFilename(Filename const & path)
{
    return extractFilename<wchar_t>(path.wstr);
}

}
