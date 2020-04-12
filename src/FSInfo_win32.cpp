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
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

#include "FSInfo.hpp"
#include <cstdio>

namespace ff {

/* 1st version D.A.
void getFSInfo(const char* path, FSInfo& info)
{
  struct {
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;
  } data;

  GetDiskFreeSpaceExA(path, &data.freeBytesAvailable,0,0);
  info.free_space = (fsize_t) data.freeBytesAvailable.QuadPart;
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  info.block_size = systemInfo.dwPageSize;
  info.optimal_size = systemInfo.dwPageSize;
}
*/

// problem discovered and fixed thanks to B.R.: path must be a directory here, not a filepath
// further changes by J.O.: allow for network shares a la "\\machine/folder/file" by using MAX_PATH and making sure we have a trailing '\'
void getFSInfo(const char* path, FSInfo& info)
{
  ULARGE_INTEGER freeBytesAvailable;
  char dir[MAX_PATH], *p;
  strncpy(dir, path, 10); p = strchr(dir, '/');
  if (p){
    if (dir[0]=='\\')
	  *p++ = '\\';
	*p = '\0';
  }
  GetDiskFreeSpaceExA(dir, &freeBytesAvailable, NULL, NULL);
  info.free_space = (fsize_t) freeBytesAvailable.QuadPart;
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  info.block_size = systemInfo.dwPageSize;
  info.optimal_size = systemInfo.dwPageSize;
}



}

#endif
