#include "../classes/FileStreamWrapper.h"

#ifdef __MINGW32__

#include <ext/stdio_filebuf.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace {
    
void addAccess(int & result, std::ios_base::openmode mode, std::ios_base::openmode modeCheck, int flag)
{
    if( (mode & modeCheck) == modeCheck ) {
        result |= flag;
    }    
}
    
int wOpenMode(std::ios_base::openmode mode)
{
    int result = 0;
    if( (mode & (std::ios_base::in | std::ios_base::out)) == (std::ios_base::in | std::ios_base::out) ) {
        result = _O_RDWR;
    } else if( (mode & std::ios_base::in) == std::ios_base::in ) {
        result = _O_RDONLY;
    } else if( (mode & std::ios_base::out) == std::ios_base::out ) {
        result = _O_WRONLY;
    }
    
    addAccess(result,mode,std::ios_base::out,_O_CREAT);
    addAccess(result,mode,std::ios_base::binary,_O_BINARY);
    addAccess(result,mode,std::ios_base::app,_O_APPEND);
    addAccess(result,mode,std::ios_base::trunc,_O_TRUNC);
    
    return result;
}
    
int wOpenFlags(std::ios_base::openmode mode)
{
    int result = 0;
    if( (mode & (std::ios_base::in | std::ios_base::out)) == (std::ios_base::in | std::ios_base::out) ) {
        result = _S_IREAD | _S_IWRITE;
    } else if( (mode & std::ios_base::in) == std::ios_base::in ) {
        result = _S_IREAD;
    } else if( (mode & std::ios_base::out) == std::ios_base::out ) {
        result = _S_IWRITE;
    }
    
    return result;
}

}

#endif

#include <iostream>

namespace fs {
    
// MINGW does not implement the fucking wchar_t * fstream constructor overload, so I have to manually create a __gnu_cxx::stdio_filebuf

// TODO something is wrong here. filebuf is doing seg faults and other awful things
// #define MITIGATION_FIX
    
int checkFd(int fd) 
{
    if( fd == -1 ) {
        std::cerr << "error " << errno << std::endl;
        fd = 0;
    }
    return fd;
}        
    
class FileStreamWrapperImpl {
public:
    __gnu_cxx::stdio_filebuf<char> fb;
    
    FileStreamWrapperImpl(wchar_t const * filename, std::ios_base::openmode mode):
        fb(checkFd(_wopen(filename,wOpenMode(mode),wOpenFlags(mode))),mode)
    {
    }
};

#ifdef MITIGATION_FIX

// TODO mitigation to the __gnu_cxx::stdio_filebuf problem. it won't work with non-ascii names

FileStreamWrapper::FileStreamWrapper(Filename const & filename, std::ios_base::openmode mode):
    std::fstream(filename.toUTF8(),mode)
{
}

FileStreamWrapper::FileStreamWrapper(FileStreamWrapper && other)
{
    std::ios::rdbuf(other.rdbuf());
    other.std::ios::rdbuf(0);
}

void FileStreamWrapper::open(Filename const & filename, std::ios_base::openmode mode)
{
    open(filename.toUTF8(),mode);
}

#else 

FileStreamWrapper::FileStreamWrapper(Filename const & filename, std::ios_base::openmode mode):
    impl(new FileStreamWrapperImpl(filename.wstr.c_str(),mode))
{
    std::ios::rdbuf(&impl->fb);
}

FileStreamWrapper::FileStreamWrapper(FileStreamWrapper && other):
    impl(std::move(other.impl))
{
    std::ios::rdbuf(&impl->fb);
}

void FileStreamWrapper::open(Filename const & filename, std::ios_base::openmode mode)
{
    impl.reset();
    impl.reset(new FileStreamWrapperImpl(filename.wstr.c_str(),mode));
    basic_ios<char>::rdbuf(&impl->fb);
}

#endif
    
FileStreamWrapper::~FileStreamWrapper()
{
}

}
