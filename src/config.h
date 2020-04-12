//#ifndef FF_XTENSIONS_AVAILABLE
#define FF_XTENSIONS_AVAILABLE 1
//#endif

//#ifndef FF_SYMMXTENSIONS_AVAILABLE
#define FF_SYMMXTENSIONS_AVAILABLE 0
//#endif


#ifndef FF_CONFIG_H
#define FF_CONFIG_H

/** enable os buffering in file mapping */
#define FF_USE_BUFFERING

// Martijn Schuemie for zero row ff // #define FSIZE_RESERVED_FOR_OPENING 2147483647
// Martijn Schuemie for zero row ff #define FSIZE_RESERVED_FOR_OPENING 0
// Martijn Schuemie for zero row ff #define SIZE_OR_ZERO(size) ((size==FSIZE_RESERVED_FOR_OPENING) ? 0 : size)

//D.A. #if defined __WIN32 || defined _WIN32
//B.R. 1.2.20010 #if defined WIN32 || defined WIN64
//J.O. 16.9.2010: taking from utk_platform_macros.hpp
#if defined WIN32 || defined _WIN32 || defined __WIN32__ || defined WIN64 || defined _WIN64 || defined __WIN64__

#define FF_USE_WIN32

/** force minimum requirement Windows 2000 Professional
    as we need GetFileSizeEx instead of GetFileSize to determine
    correct file sizes.
 */

//B.R. 1.2.20010: moved to Win32FileMapping.hpp
//#define _WIN32_WINNT 0x0500

#ifndef FF_SECTION_SIZE
#define FF_SECTION_SIZE (64*1024)
#endif

#else /* on unix alike */

#include "ac_config.h"

#define FF_USE_MMAP
#define FF_USE_STATFS

#ifndef FF_SECTION_SIZE
#define FF_SECTION_SIZE (4*1024)
#endif

#endif

#endif /* FF_CONFIG_H */

