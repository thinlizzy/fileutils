#ifndef FILE_STREAM_WRAPPER_H_jfj454fdgfdgfd
#define FILE_STREAM_WRAPPER_H_jfj454fdgfdgfd

#include <fstream>
#include <memory>
#include <NativeString.h>

namespace fs {

class FileStreamWrapperImpl;
    
class FileStreamWrapper: public std::fstream {
    std::unique_ptr<FileStreamWrapperImpl> impl;
public:
    FileStreamWrapper(die::NativeString const & filename, std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);
    FileStreamWrapper(FileStreamWrapper && other);
    virtual ~FileStreamWrapper();
    void open(die::NativeString const & filename, std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);
};
    
}

#endif

