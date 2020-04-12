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

#ifdef FF_USE_WIN32

#include "Win32FileMapping.hpp"
#include "FSInfo.hpp"
#include <cassert>
#include <iostream>
#include <float.h>
#include "utk_file_allocate_fseek.hpp"


namespace ff {

inline DWORD offset_hi(foff_t offset) { return (DWORD) (offset >> 32); }
inline DWORD offset_lo(foff_t offset) { return (DWORD) (offset & 0xFFFFFFFF); }

/* JO: seems to be no longer used, commented to avoid compiler warning
static size_t getZeroPageSize()
{
  return Win32FileMapping::getPageSize()*4;
}
*/

/*
static void* getZeroPage()
{
  static void* ptr = 0;
  if (!ptr) {
    ptr = (void*) malloc( getZeroPageSize() );
    ZeroMemory(ptr, getZeroPageSize() );
  }
  return ptr;
}
*/

bool isFileReadOnly(const char* path)
{
  WIN32_FILE_ATTRIBUTE_DATA data;
  GetFileAttributesExA(path, GetFileExInfoStandard, &data);
  return ( data.dwFileAttributes & FILE_ATTRIBUTE_READONLY ) ? true : false;
}

Win32FileMapping::Win32FileMapping(const char* path, fsize_t size, bool readonly, bool autoflush
, bool createNew  // Martijn Schuemie for zero row ff
)
: _fileHandle(INVALID_HANDLE_VALUE)
, _viewHandle(INVALID_HANDLE_VALUE)
, _size(0)
, _error(E_INVALID)
, _readonly(readonly)
, _autoflush(autoflush)
{
/*
 FIXME: temporarly disable test for Jens

  if ( (!readonly) && (size) )
  {
    if ( isFileReadOnly(path) ) {
      _error = E_FILE_IS_READONLY;
      return;
    }
  }
 */

  if (createNew)  // Martijn Schuemie for zero row ff
  {
    int err = utk::file_allocate_fseek(path, size);
    if (err)
    {
      _error = E_WRITE_ERROR;
      goto on_error;
    }
    _size = size;
  }

  _fileHandle = CreateFileA(
    path
  , GENERIC_READ | ( (readonly) ? 0 : GENERIC_WRITE )
  , FILE_SHARE_READ|FILE_SHARE_WRITE
  // , 0
  , NULL
  , /*(size==0) ?*/ OPEN_EXISTING /*: CREATE_ALWAYS*/
#ifdef FF_USE_BUFFERING
  , 0
#else
  , FILE_FLAG_NO_BUFFERING
#endif
  , NULL
  );

  if (_fileHandle == INVALID_HANDLE_VALUE) {
    // _error = (size) ? E_UNABLE_TO_OPEN : E_NOT_EXISTING;
    _error = E_UNABLE_TO_OPEN;
    return;
  }
  if (createNew)   // Martijn Schuemie for zero row ff
{
    // check free disk space
    FSInfo info;
    getFSInfo(path,info);
    if ( info.free_space < size ) {
      _error = E_NO_DISKSPACE;
      return;
    }
  }
  if (createNew)   // Martijn Schuemie for zero row ff
{

    // allocate file blocks that match array size and zero fill
/*
    fsize_t total = size;
    while (total > 0) {
      DWORD dwsize;
      if ( total > static_cast<fsize_t>( getZeroPageSize() ) ) {
        dwsize = (DWORD) getZeroPageSize();
      } else
        dwsize = (DWORD) total;
      DWORD written;
      BOOL b;
      b = WriteFile(_fileHandle, getZeroPage(), dwsize, &written, 0 );
      if (b == FALSE) {
        _error = E_WRITE_ERROR;
        goto on_error;
      }
      total -= written;
    }
*/

/*
    int err = utk::file_allocate_fseek(path, size);
    if (err)
    {
      _error = E_WRITE_ERROR;
      goto on_error;
    }

    _size = size;
*/
  } else {
    // open already existing file
    LARGE_INTEGER li;
    BOOL s = GetFileSizeEx(
      _fileHandle
    , &li
    );
    if (!s) {
      _error = E_UNABLE_TO_OPEN;
      goto on_error;
    }
    _size = (fsize_t) li.QuadPart;
#if 0
    DWORD high;
    li.LowPart = GetFileSize(_fileHandle, &high);
    _size = (fsize_t) li.QuadPart;
    if (li.LowPart == INVALID_FILE_SIZE) {
      if ( GetLastError() != NO_ERROR )
      {
        _error = E_UNABLE_TO_OPEN;
        goto on_error;
      }
    }
    li.HighPart = high;
#endif
  }

  _viewHandle = CreateFileMapping(
    _fileHandle
  , 0
  , (readonly) ? PAGE_READONLY : PAGE_READWRITE
  , 0
  , 0
  , 0);
  if (_viewHandle == INVALID_HANDLE_VALUE) {
    _error = E_UNABLE_TO_OPEN;
    goto on_error;
  }
  _error = E_NO_ERROR;
  return;
on_error:
  if (_fileHandle != INVALID_HANDLE_VALUE) {
    CloseHandle(_fileHandle);
    _fileHandle = INVALID_HANDLE_VALUE;
  }
}

Win32FileMapping::~Win32FileMapping()
{
  if (_viewHandle != INVALID_HANDLE_VALUE)
    CloseHandle(_viewHandle);
  if (_fileHandle != INVALID_HANDLE_VALUE)
    CloseHandle(_fileHandle);
}

Win32FileSection* Win32FileMapping::mapSection(foff_t offset, msize_t size, void* baseaddr)
{
  return new Win32FileSection(_viewHandle, offset, size,baseaddr,_readonly,_autoflush);
}

void Win32FileMapping::remapSection(Win32FileSection& section, foff_t offset, msize_t size, void* baseaddr)
{
  section.reset(offset, size, baseaddr);
}

Win32FileSection::Win32FileSection(HANDLE handle, foff_t offset, msize_t size, void* baseaddr, bool readonly, bool autoflush)
: _viewHandle(handle)
, _readonly(readonly)
, _autoflush(autoflush)
, _offset(0)
, _size(0)
, _addr(0)
{
  reset(offset,size,baseaddr);
}

void Win32FileSection::flush()
{
  if(_addr) {
    if (_autoflush)
      FlushViewOfFile(_addr,_size);
    UnmapViewOfFile(_addr);
    _addr = 0;
  }
}

Win32FileSection::~Win32FileSection()
{
  flush();
}

void Win32FileSection::reset(foff_t offset, msize_t size, void* baseaddr)
{
  flush();

  _addr = (double*) MapViewOfFileEx(
    _viewHandle
  , FILE_MAP_READ | ( (_readonly) ? 0 : FILE_MAP_WRITE )
  , offset_hi(offset)
  , offset_lo(offset)
  , size
  , baseaddr
  );
  _offset = offset;
  _size   = size;
  _end    = _offset + _size;
}

/* static */ msize_t Win32FileMapping::getPageSize()
{
  static msize_t _pagesize = 0;
  if (!_pagesize) {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    _pagesize = (msize_t) systemInfo.dwAllocationGranularity;
  }
  return _pagesize;
}

}

#endif
