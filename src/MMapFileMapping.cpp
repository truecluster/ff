/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

/////////////////////////////////////////////////////////////////////////////*/

#include "config.h"
#ifdef FF_USE_MMAP
#include "MMapFileMapping.hpp"
#include "FSInfo.hpp"
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_MMAN_H
// B.R. 1.10.2010
#if defined(__sun__) || defined(__sun) || defined(sun)
#define _POSIX_C_SOURCE 200112L
#endif
#include <sys/mman.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>
#endif
// D.A. #include <cstdlib>
//{ J.O. 16.9.2010 interpreting B.R.
#if defined(__sun__) || defined(__sun) || defined(sun)
#include <stdlib.h>
#else
#include <cstdlib>
#endif
//} J.O. 16.9.2010
#include <cstring>
#include <strings.h>
#include <sys/file.h>
#include "utk_file_allocate_fseek.hpp"
namespace ff {

#if 0
static msize_t getZeroPageSize()
{
  return MMapFileMapping::getPageSize();
}

static void* getZeroPage()
{
  static void* ptr = 0;
  if (!ptr) {
    ptr = (void*) malloc( getZeroPageSize() );
    bzero(ptr, getZeroPageSize());
  }
  return ptr;
}
#endif

MMapFileMapping::MMapFileMapping(const char* path, fsize_t size, bool readonly, bool autoflush
, bool createNew // Martijn Schuemie for zero row ff
)
 : _fd(-1)
 , _size(0)
 , _error(E_NO_ERROR)
 , _readonly(readonly)
 , _autoflush(autoflush)
 , _createNew(createNew)  // Martijn Schuemie for zero row ff
{
  // check path
  struct stat sb;
  int err;
  err = stat(path, &sb);
  if (!err) { // file already existing
    // check if regular file
    if (!(sb.st_mode & S_IFREG)) {
      _error = E_UNABLE_TO_OPEN;
      return;
    }
  }
  int flags = (_readonly) ? O_RDONLY : O_RDWR;
/*
  flags |= O_CREAT;
  if (size) flags |= O_TRUNC;
 */
  if (createNew)  // Martijn Schuemie for zero row ff
{
    int error = utk::file_allocate_fseek(path,size);
    if (error)
    {
      _error = E_WRITE_ERROR;;
      return;
    }
    _size = size;
  }
  _fd = open(path, flags, 0777);
  if (_fd == -1) {
    _error = E_UNABLE_TO_OPEN;
    return;
  }
/*
  err = ::flock(_fd, LOCK_EX|LOCK_NB);
  if (err) {
    close(_fd);
    _fd = -1;
    _error = E_UNABLE_TO_OPEN;
    return;
  }
*/
  if (_createNew) // Martijn Schuemie for zero row ff
{ 
#if 0
    // clamp size to page-size

    // size += getPageSize()-1;
    // size = size / getPageSize() * getPageSize();

    // check space on device

    FSInfo fsinfo;
    getFSInfo(path,fsinfo);
    if (fsinfo.free_space < size) {
      close(_fd);
      _fd = -1;
      _error = E_NO_DISKSPACE;
      return;
    }

    // write zero pages to file with given size

    fsize_t total = size;
    size_t zpsize = getZeroPageSize();
    void*  zpbuf  = getZeroPage();
    while (total > 0 ) {
      size_t wsize = ( total > zpsize ) ? zpsize : total;
      size_t written = write(_fd, zpbuf, wsize);
      total -= written;
    }
    _size = size;
#endif
  } else { // open existing file
    // get filesize
    struct stat sb;
    fstat(_fd, &sb);
    _size = sb.st_size;
  }
}

MMapFileMapping::~MMapFileMapping()
{
  if (_fd != -1) {
    close(_fd);
    // flock(_fd, LOCK_UN);
  }
}

MMapFileSection* MMapFileMapping::mapSection(foff_t offset, msize_t size, void* baseaddr)
{
  return new MMapFileSection(_fd,offset,size,baseaddr,_readonly,_autoflush
,true // Martijn Schuemie for zero row ff
);
}

void MMapFileMapping::remapSection(MMapFileSection& section, foff_t offset, msize_t size, void* addr)
{
  section.reset(offset,size,addr);
}

msize_t MMapFileMapping::getPageSize()
{
  static int _pagesize = -1;
  if (_pagesize == -1)
    _pagesize = getpagesize();
  return _pagesize;
}

MMapFileSection::MMapFileSection(int fd, foff_t offset, msize_t size, void* addr, bool readonly, bool autoflush
, bool createNew  // Martijn Schuemie for zero row ff
)
 : _fd(fd)
 , _readonly(readonly)
 , _autoflush(autoflush)
 , _createNew(createNew)  // Martijn Schuemie for zero row ff
 , _offset(0)
 , _end(0)
 , _size(0)
 , _addr(0)
{
  reset(offset,size,addr);
}

MMapFileSection::~MMapFileSection()
{
  flush();
}

void MMapFileSection::flush()
{
  if (_addr) {
    if (_autoflush) {
      msync(_addr, _size, MS_SYNC);
    }
    munmap(_addr, _size);
    _addr = 0;
    _size = 0;
  }
}

void MMapFileSection::reset(foff_t offset, msize_t size, void* addr)
{
  flush();

  if ( (_createNew)   // Martijn Schuemie for zero row ff
&& (_fd != -1) ) {
    int prot = PROT_READ | (( _readonly) ? 0 : PROT_WRITE );
    int flags = MAP_SHARED
//D.A. #if !defined(__sun__)
//J.O. 16.9.2010
#if !(defined(__sun__) || defined(__sun) || defined(sun))
     | MAP_FILE
#endif
    ;
    _addr = mmap(addr, size, prot,flags, _fd, offset);
    if (_addr) {
      _offset = offset;
      _size   = size;
    _end    = _offset + size;
    }
  }
}

}

#endif
