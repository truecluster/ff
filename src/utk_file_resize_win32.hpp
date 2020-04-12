///////////////////////////////////////////////////////////////////////////////
//
// universal tool kit (utk)
// file resize using win32 API (SetFilePointer/SetEndOfFile)
//
// Copyright (C) 2009 Daniel Adler <dadler@uni-goettingen.de>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include "utk_file_resize.hpp"
#include <windows.h>
namespace utk {

  int file_resize(const char* path, fsize_t newsize)
  {
    HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return -1;
    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = (LONGLONG) newsize;
    BOOL success;
    success = SetFilePointerEx(hFile, liDistanceToMove, NULL, FILE_BEGIN);
    if (success)
      success = SetEndOfFile(hFile);
    CloseHandle(hFile);
    return (success) ? 0 : -1;
  }

}
